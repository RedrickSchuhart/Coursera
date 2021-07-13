#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


struct Email {
  string from;
  string to;
  string body;
};


class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email)=0;
  virtual void Run() {
    // только первому worker-у в пайплайне нужно это имплементировать
    throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const {
        if(next_)
            next_->Process(move(email));
    }

public:
  void SetNext(unique_ptr<Worker> next) {
      next_ = move(next);
  }
private:
  unique_ptr<Worker> next_;
};


class Reader : public Worker {
public:
    Reader(istream& is) : is(is){
    }

    virtual void Run() {
        string from, to, object;
        while(getline(is, from)) {
            if(getline(is, to)) {
                if(getline(is, object)) {
                    auto ptr = unique_ptr<Email>(new Email{from, to, object});
                    //auto ptr = make_unique<Email>(from, to, object);
                    Process(move(ptr));
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }
    virtual void Process(unique_ptr<Email> email) {
        PassOn(move(email));
    }
private:
    istream& is;
};


class Filter : public Worker {
public:
    using Function = function<bool(const Email&)>;
    Filter(Function func_) : func(func_){}

    virtual void Process(unique_ptr<Email> email){
        if(func(*email)) {
            PassOn(move(email));
        }
    }

public:
    Function func;
  // реализуйте класс
};


class Copier : public Worker {
public:
    Copier(string to_) : to(to_) {}
    virtual void Process(unique_ptr<Email> email){
        string from = email->from;
        string to_ = email->to;
        string body = email->body;
        PassOn(move(email));
        if(to_!=to) {
            auto ptr = unique_ptr<Email>(new Email{from, to, body});
            //auto ptr = make_unique<Email>(email->from, to, email->body);
            PassOn(move(ptr));
        }
    }

private:
    string to;
};


class Sender : public Worker {
public:
    Sender(ostream& out_) : out(out_) {}
    virtual void Process(unique_ptr<Email> email){
        out << email->from << endl << email->to << endl << email->body << endl;
        PassOn(move(email));
    }

private:
    ostream& out;
};


// реализуйте класс
class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream& in) {
        first = make_unique<Reader>(in);
        last = first.get();

    }

    // добавляет новый обработчик Filter
    PipelineBuilder& FilterBy(Filter::Function filter) {
        auto ptr = make_unique<Filter>(filter);
        Filter* last_ = ptr.get();
        last->SetNext(move(ptr));
        last = last_;
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder& CopyTo(string recipient) {
        auto ptr = make_unique<Copier>(recipient);
        Copier* last_ = ptr.get();
        last->SetNext(move(ptr));
        last = last_;
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder& Send(ostream& out) {
        auto ptr = make_unique<Sender>(out);
        Sender* last_ = ptr.get();
        last->SetNext(move(ptr));
        last = last_;
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build() {
        return move(first);
    }
private:
    unique_ptr<Reader> first;
    Worker* last;
};


void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;

  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
    return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();

  pipeline->Run();

  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"

    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"

    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
