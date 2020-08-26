#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector(){
      size_ = 0;
      capacity_ = 0;
      data = new T[0];
  }
  explicit SimpleVector(size_t size){
      size_=size;
      capacity_=1;
      while(size_>capacity_)
          capacity_ = capacity_*2;
      data = new T[capacity_];
  }
  ~SimpleVector(){
      delete [] data;
  }

  T& operator[](size_t index){
      return data[index];
  }

  T* begin(){
      return data;
  }
  T* end(){
      return data+size_;
  }
  size_t Size() const{
      return size_;
  }
  size_t Capacity() const{
      return capacity_;
  }


  void PushBack(const T& value){
      if(capacity_==0)
          capacity_=1;
      if((size_+1)>capacity_) {
          while((size_+1)>capacity_)
              capacity_ = capacity_*2;
          T* new_data = new T[capacity_];
          for(size_t i=0; i<size_; i++){
              new_data[i] = data[i];
          }
          delete [] data;
          data = new_data;
          //delete [] new_data;
      }
      data[size_] = value;
      size_++;
  }

private:
  size_t size_, capacity_;
  T* data;
};
