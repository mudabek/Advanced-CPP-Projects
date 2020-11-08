#pragma once


namespace task {

template <class T>
class UniquePtr {
private:
  T* ptr = nullptr;

public:
  explicit UniquePtr(T* rawRes) noexcept : ptr(std::move(rawRes)) {}

  UniquePtr(UniquePtr&& move) {
    move.swap(*this);
  }
  UniquePtr() : ptr(nullptr) {}
  
  ~UniquePtr() {
    delete ptr;
  }
  
  UniquePtr(const UniquePtr<T>&) = delete;
  
  UniquePtr& operator=(const UniquePtr&) = delete;
  
  UniquePtr& operator=(UniquePtr&& move) {
    ptr = nullptr;
    move.swap(*this);
	return *this;
  }
  
  T& operator*() {
    return *this->ptr;
  }
  
  T* operator->() {
    return this->ptr;
  }
  
  T* get() {
    return ptr;  
  }
  
  T* release() {
    return std::exchange(ptr, nullptr);
  }
  
  void swap(UniquePtr<T>& otherPtr) {
    std::swap(ptr, otherPtr.ptr);
  }
  
  void reset(T* newPtr) {
    delete ptr;
    ptr = nullptr;
    std::swap(ptr, newPtr);
  }
};


template <class T>
class SharedPtr {
private:
  T* ptr = nullptr;
  int *sharedCnt;
  
public:
    
  SharedPtr() : ptr(nullptr), sharedCnt(new int(1)) {}  

  SharedPtr(T* ptr_) {
    ptr = ptr_;
    sharedCnt = new int(1);
  }
  
  ~SharedPtr() {
    if (sharedCnt != nullptr) {
      (*sharedCnt)--;
      if(*sharedCnt == 0) {
        delete ptr;
        delete sharedCnt;
      }
    }  
  }
  
  SharedPtr(const SharedPtr<T>& other) : ptr(other.ptr), sharedCnt(other.sharedCnt) {
    (*sharedCnt)++;
  }
  
  SharedPtr<T>& operator=(const SharedPtr<T>& other) {
    if (this != &other) {
      (*sharedCnt)--;
      
      if (*sharedCnt == 0) {
        delete ptr;
        delete sharedCnt;
      }
     
      ptr = other.ptr;
      sharedCnt = other.sharedCnt;
      (*sharedCnt)++;
    }
    return *this;
  }
  
  int use_count() const {
    if(sharedCnt != nullptr)
      return *sharedCnt;
    else
      return 0;
  }
  
  T& operator*() {
    return *this->ptr;
  }
  
  T* operator->() {
    return this->ptr;
  }
  
  T* get() {
    return ptr;  
  }
  
  void swap(SharedPtr<T>& otherPtr) {
    std::swap(ptr, otherPtr.ptr);
    std::swap(sharedCnt, otherPtr.sharedCnt);
  }
  
  void reset() {
    SharedPtr().swap(*this);
  }
  
  void reset(T* newPtr) {
    delete ptr;
    ptr = nullptr;
    //sharedCnt = nullptr;
    std::swap(ptr, newPtr);
  }
};

template <class T>
class WeakPtr {
    // Your code goes here...
};


// Your template function definitions may go here...

}  // namespace task


#include "smart_pointers.tpp"
