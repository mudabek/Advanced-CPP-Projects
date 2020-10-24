#include <iostream>
#include <list>

using namespace std;

int MAX_CHUNK = 1024;

class Chunk {
public:

  Chunk() {
    chunk = new char[MAX_CHUNK];
    freeSpace = MAX_CHUNK;
  }
  
  int spaceLeft() {
    return freeSpace;
  }
  
  void takeSpace(int n) {
    freeSpace - n;
  }
  
  char* ending() {
    chunk + MAX_CHUNK - freeSpace;
  }
  
  private:
  char* chunk;
  int freeSpace;
};

template <typename T>
class Allocator {
public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  //using rebind = template< class U > struct rebind { typedef allocator<U> other; };
  
  Allocator() {
    list<Chunk> chunks;
    copyCnt = 1;
  }
  
  ~Allocator() {}
  
  Allocator(const Allocator& copy) {
    copyCnt = &copy.copyCnt;
    list<Chunk> chunks;
    chunks.assign(copy.chunks.begin(), copy.chunks.end());
  }
  
  Allocator operator=(const Allocator& a) {
    if (a == *this)
      return *this;
    
    copyCnt = &a.copyCnt;
    list<Chunk> chunks;
    chunks.assign(a.chunks.begin(), a.chunks.end());
    
    return *this;
  }
  
  T* allocHelper(const size_t n) {
    Chunk temp = Chunk();
    chunks.push_front(temp);
    auto it = chunks.begin();
    it->takeSpace(n * sizeof(T));
    return (T*)(&chunks.front());
  }
  
  T* allocate(const size_t n) {
    if(chunks.empty()) {
      allocHelper(n);
    } else {
      for (auto it = chunks.begin(); it != chunks.end(); ++it) {
        if (it->spaceLeft() >= n * sizeof(T)) {
          it->takeSpace(n * sizeof(T));
          return (T*)it->ending() - n * sizeof(T);
        }
      }
      allocHelper(n);
    }
  }
  
  void deallocate(T* p, const size_t n) {}
  
  template <typename ... Args>
  void construct(T* p, const Args&&... args) {
    new (p) T(args...);
  }
  
  void destroy(T* p) {
    if (copyCnt == 1) {
      p->~T();
    } else {
      copyCnt--;
    }
  }
  
  private:
    int copyCnt;
    list<Chunk> chunks;
};


class A {
public:
  A(int x, int y) { cout << x << y << endl; }
  ~A() { cout << "~" << endl; }
};

int main() {
  Allocator<A> alloc;
  auto p = alloc.allocate(1);
  alloc.construct(p, 1, 2);
  alloc.construct(p, 4, 5);
  alloc.destroy(p);
  alloc.deallocate(p, 1); 
  
  return 0;
}