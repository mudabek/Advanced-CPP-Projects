#pragma once


namespace task {
    
bool noShared = false;

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
class WeakPtr;

template <class T>
class SharedPtr {
public:
  T* ptr = nullptr;
  int *sharedCnt;
  int *weakCnt;
  
public:
    
  SharedPtr() : ptr(nullptr), sharedCnt(new int(1)), weakCnt(new int(0)) {}  

  SharedPtr(T* ptr_) : ptr(ptr_), sharedCnt(new int(1)), weakCnt(new int(0)) {}
  
  SharedPtr(WeakPtr<T> wPtr) : ptr(wPtr.shPtr.ptr), sharedCnt(new int(0)), weakCnt(new int(1)) {}
  
  ~SharedPtr() {
    if (sharedCnt != nullptr) {
      (*sharedCnt)--;
      if(*sharedCnt == 0 && *weakCnt == 0) {
        delete ptr;
        delete sharedCnt;
        delete weakCnt;
        noShared = true;
      }
    }  
  }
  
  SharedPtr(const SharedPtr<T>& other) : ptr(other.ptr), sharedCnt(other.sharedCnt), weakCnt(other.weakCnt) {
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
    std::swap(weakCnt, otherPtr.weakCnt);
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
public:
  SharedPtr<T> shPtr;
  
  WeakPtr(SharedPtr<T> shPtr_) {
    shPtr = shPtr_;
    if (shPtr.sharedCnt)
      (*shPtr.weakCnt)++;
  }
  
  WeakPtr(const WeakPtr<T>& other) : shPtr(other.shPtr) {
    (*shPtr.weakCnt)++;
    (*shPtr.sharedCnt)--;
  }
  
  WeakPtr(WeakPtr&& move) {
    std::cout << "here" << std::endl;
    move.swap(*this);
  }
  
  ~WeakPtr() {
    (*shPtr.weakCnt)--;
    if (*shPtr.sharedCnt == 0) {
      shPtr.~SharedPtr();
    }
  }
  
  WeakPtr& operator=(SharedPtr<T>& other) {
    noShared = false;
    WeakPtr(other).swap(*this);
    (*shPtr.sharedCnt)--;
    return *this;
  }
  
  WeakPtr& operator=(WeakPtr&& move) {
    shPtr = SharedPtr<T>();
    move.swap(*this);
    //(*shPtr.sharedCnt)--;
	return *this;
  }
  
  WeakPtr<T>& operator=(const WeakPtr<T>& other) {
    WeakPtr(std::move(other)).swap(*this);
    //(*shPtr.sharedCnt)--;
    return *this;
  }
  
  int use_count() {
    if (noShared)
      return 0;
    return shPtr.use_count();
  }
  
  bool expired() {
    return use_count() == 0;
  }
  
  SharedPtr<T> lock() {
    SharedPtr<T> ret = expired() ? SharedPtr<T>() : SharedPtr<T>(*this);
    return ret;
  }
  
  void swap(WeakPtr<T>& otherPtr) {
    std::swap(shPtr, otherPtr.shPtr);
  }
  
  void reset() {
    WeakPtr().swap(*this);
  }
};


}  // namespace task


#include "smart_pointers.tpp"