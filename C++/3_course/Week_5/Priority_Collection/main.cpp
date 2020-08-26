#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <list>
#include <tuple>
#include <utility>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T1>
class Contain {
public:
    using It = set<int>::iterator;
    Contain() {}
    Contain(T1 object_, int prior_, It it_) {
        object=move(object_); prior=prior_; it_on_list=it_;
    }
T1 object;
int prior;
It it_on_list;
};

template <typename T>
class PriorityCollection {
public:
  using Id = int;
  using It = set<int>::iterator;
  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        int id = new_id++;
        collections[0].insert(id);
        auto node = collections[0].end();
        id_collections[id] = Contain<T>(move(object), 0, --node);
        return id;
    }

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
      int id;
      for(auto it = range_begin; it != range_end; it++) {
          id = new_id++;
          collections[0].insert(id);
          auto node = collections[0].end();
          id_collections[id] = Contain<T>(move(*it), 0, --node);
          (*ids_begin) = id;
          ids_begin++;
      }
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
      if(id_collections.find(id)!=id_collections.end()){
          return true;
      } else {
          return false;
      }
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
      auto it = id_collections.find(id);
      return (*it).second.object;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
      int prior = id_collections[id].prior;
      Erase(prior, id);
      //collections[prior].erase(id);
      collections[prior+1].insert(id);
      id_collections[id].prior++;
      auto it = collections[prior+1].end();
      id_collections[id].it_on_list = (--it);
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
      auto end_map = collections.end();
      auto end_list = (*(--end_map)).second.end();
      int id = (*(--end_list));
      auto it = id_collections.find(id);
      //const T& object = (*it).second.Return_Object();
      return {(*it).second.object, (*end_map).first};

  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
      auto end_map = collections.end();
      auto end_list = (*(--end_map)).second.end();
      int id = (*(--end_list));
      Erase((*end_map).first, id);
      //collections[(*end_map).first].erase(end_list);
      pair<T, int> result = {move(id_collections[id].object), (*end_map).first};
      id_collections.erase(id);
      return result;
  }

  void Erase(int prior, Id id) {
      collections[prior].erase(id);
      if(collections[prior].empty())
          collections.erase(prior);
  }

private:
  int new_id=0;
  map<int, set<Id>> collections;
  map<Id, Contain<T>> id_collections;
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.GetMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
}

int main() {
    list<int>::iterator d;
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
