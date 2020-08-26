#include <iostream>
#include <utility>
#include <vector>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
private:
  vector<T> left, right;
public:

  Deque() {
  }

  bool Empty() const {
      if((left.empty())&&(right.empty())) {
          return true;
      } else {
          return false;
      }
  }

  size_t Size() const{
      return left.size()+right.size();
  }

  T& operator[](size_t index) {
      if (index < left.size()) {
          return left[left.size()-1-index];
      } else {
          return right[index-left.size()];
      }
  }

  const T& operator[](size_t index) const {
      if (index < left.size()) {
          return left[left.size()-1-index];
      } else {
          return right[index-left.size()];
      }
  }

  T& At(size_t index) {
      if ((index<0)||(index < (left.size()+right.size()))) {
          if (index < left.size()) {
              return left[left.size()-1-index];
          } else {
              return right[index-left.size()];
          }
      } else {
          throw out_of_range{"Deque.At()"};
      }
  }

  const T& At(size_t index) const {
      if ((index<0)||(index < (left.size()+right.size()))) {
          if (index < left.size()) {
              return left[left.size()-1-index];
          } else {
              return right[index-left.size()];
          }
      } else {
          throw out_of_range{"Deque.At()"};
      }
  }

  T& Front() {
      if(left.empty()) {
          return *(right.begin());
      } else {
          return *(left.end()-1);
      }
  }

  const T& Front() const {
      if(left.empty()) {
          return *(right.begin());
      } else {
          return *(left.end()-1);
      }
  }

  T& Back() {
      if(right.empty()) {
          return *(left.begin());
      } else {
          return *(right.end()-1);
      }
  }

  const T& Back() const {
      if(right.empty()) {
          return *(left.begin());
      } else {
          return *(right.end()-1);
      }
  }

  void PushFront(const T& item){
      left.push_back(item);
  }

  void PushBack(const T& item){
      right.push_back(item);
  }
};

int main() {
    Deque<int> dq;
    dq.PushBack(3);
    dq.PushBack(4);
    cout << dq.Front() << " " << dq.Back() << endl;
    return 0;
}
