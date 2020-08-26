#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};



bool IsPalindrom(string s) {
    // Замечание: более правильным было бы использовать здесь тип size_t вместо int
    // О причинах Вы узнаете на Жёлтом поясе
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

void TestStand() {
    Assert(IsPalindrom(""), "empty");
    Assert(IsPalindrom("s"), "1 char");
    Assert(IsPalindrom(" "), "1 space");
    Assert(IsPalindrom("s  s"), "s  s");
     Assert(IsPalindrom(" aa "), " aa ");
    Assert(IsPalindrom("s a s"), "s a s");
    Assert(IsPalindrom("&33&"), "&33&");
    Assert(IsPalindrom("sdads"), "sdads");
    Assert(IsPalindrom("sdds"), "sdds");
    Assert(IsPalindrom("777777"), "777777");
    Assert(IsPalindrom("madam"), "madam");
    Assert(IsPalindrom("   madam   "), "   madam   ");
    Assert(IsPalindrom("   ma  am   "), "   ma  am   ");

    Assert(!IsPalindrom("ddds"), "ddds");
    Assert(!IsPalindrom("   ma  a  m   "), "   ma  a  m   ");
    Assert(!IsPalindrom("aaA"), "aaA");
    Assert(!IsPalindrom("ddads"), "ddads");
    Assert(!IsPalindrom("s a a"), "s a a");
    Assert(!IsPalindrom("s  a"), "s  a");
    Assert(!IsPalindrom("1/3&"), "1/3&");
    Assert(!IsPalindrom("dsds"), "dsds");
    Assert(!IsPalindrom("dsdds"), "dsdds");
    Assert(!IsPalindrom("dssds"), "dssds");
    Assert(!IsPalindrom("aaaaaaaaaadssdsaaaaaaaaaa"), "aaaaaaaaaadssdsaaaaaaaaaa");
    Assert(!IsPalindrom("aaaaaaaaaadssd  saaaaaaaaaa"), "aaaaaaaaaadssd  saaaaaaaaaa");
    Assert(!IsPalindrom("adama"), "adama");
    Assert(!IsPalindrom("baobab"), "baobab");
    Assert(!IsPalindrom("777778"), "777778");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestStand, "TestStand()");
  // добавьте сюда свои тесты
  return 0;
}
