#include <utility>
#include <iostream>
#include <memory>
#include <vector>


using namespace std;

int MAX_CHUNK = 1024;

class Block {
public:

  Block() {
    block = new char[MAX_CHUNK];
    freeSpace = MAX_CHUNK;
  }
  
  int spaceLeft() {
    return freeSpace;
  }
  
  void takeSpace(int n) {
    freeSpace - n;
  }
  
  char* ending() {
    block + MAX_CHUNK - freeSpace;
  }
  
  private:
  char* block;
  int freeSpace;
};

struct Node
{
    Block block;
    Node* next;
};

class LinkedList {
public:
  Node* head;
  
  LinkedList() : head(NULL) {};
  
  void deleteList() {
    Node* cur = head;
    Node* temp;
    
    while (cur != NULL) {
      temp = cur->next;
      free(cur);
      cur = temp;
    }
    
    head = NULL;
  }
  
  bool empty() {
    if (head == NULL)
      return true;
    return false;
  }
  
  void insert(Block block) {
    Node* temp = new Node;
    temp->block = block;
    temp->next = NULL;
    
    if (head == NULL) {
      head = temp;
    } else {
      temp->next = head;
      head = temp;
    }
  }
  
  void insert(Node* newNode) {
    if (head == NULL) {
      head = newNode;
    } else {
      newNode->next = head;
      head = newNode;
    }
  }
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
  template<typename U> struct rebind { typedef Allocator<U> other; };
  
  
  
  Allocator() {
    LinkedList chunks = LinkedList();
    int cnt = 1;
    copyCnt = &cnt;
  }
  
  ~Allocator() {
    if (*copyCnt == 1)
      chunks.deleteList();
    else 
      *copyCnt--;
  }
  
  Allocator(const Allocator& copy) {
    *copyCnt++;
    copyCnt = copy.copyCnt;
    LinkedList chunks;
    
    Node* cur = copy.chunks.head;
    while (cur != NULL) {
      chunks.insert(cur);
      cur = cur->next;
    }
  }
  
  Allocator operator=(const Allocator& a) {
    if (a == *this)
      return *this;
    
    *copyCnt++;
    copyCnt = a.copyCnt;
    chunks.deleteList();
    chunks = a.chunks;
    
    return *this;
  }
  
  pointer allocHelper(const size_type n) {
    Block tempBlock = Block();
    tempBlock.takeSpace(n * sizeof(value_type));
    chunks.insert(tempBlock);
    return (pointer)(&chunks.head);
  }
  
  pointer allocate(const size_type n) {
    if(chunks.empty()) {
      allocHelper(n);
    } else {
      Node* temp = chunks.head;
      while(temp != NULL) {
        if (temp->block.spaceLeft() >= n * sizeof(value_type)) {
          temp->block.takeSpace(n * sizeof(value_type));
          return (pointer)temp->block.ending() - n * sizeof(value_type);
        }
      }
      allocHelper(n);
    }
  }
  
  void deallocate(pointer p, const size_type n) {}
  
  template <typename ... Args>
  void construct(pointer p, const Args&&... args) {
    new (p) value_type(std::forward<const Args>(args)...);
  }
  
  void destroy(pointer p) {
    p->~value_type();
  }
  
  private:
    int* copyCnt;
    LinkedList chunks;
};

int main() {
  return 0;
}