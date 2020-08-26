#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate(){
        if(dedicated.empty())
        {
            T* object = new T;
            released.insert(object);
            return object;
        } else {
            T* object = dedicated.front();
            released.insert(object);
            dedicated.pop();
            return object;
        }
    }
    T* TryAllocate(){
        if(dedicated.empty())
        {
            return nullptr;
        } else {
            T* object = dedicated.front();
            released.insert(object);
            dedicated.pop();
            return object;
        }
    }

    void Deallocate(T* object){
        auto it = released.find(object);
        if(it == released.end()) {
            throw invalid_argument("error");
        } else {
            dedicated.push(*it);
            released.erase(it);
        }
    }

    ~ObjectPool(){
        for(auto it : released) {
            delete it;
        }
        while(!dedicated.empty()) {
            delete dedicated.front();
            dedicated.pop();
        }
    }

private:
  queue<T*> dedicated;
  set<T*> released;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
