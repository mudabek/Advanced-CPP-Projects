#pragma once
#include <utility>
#include <iterator>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>

namespace task {


template<class T, class Alloc = std::allocator<T>>
class list {

public:
    struct Node {
      T data;
      Node* next;
      Node* prev;

      Node(T data_) : data(data_), next(NULL), prev(NULL) {}

      Node(T data_, Node* next_, Node* prev_) : data(std::move(data_)), next(next_), prev(prev_) {}
      
      Node(Node* prev_) : data(T()), prev(prev_), next(NULL) {}
      
      
      bool operator==(Node* other) {
        return data == other.data;
      }
      
      bool operator!=(Node* other) {
        return data != other.data;
      }
      
      bool same(Node* other) {
        if (data == other->data && prev == other->prev && next == other->next)
          return true;
        return false;
      }
    };

    class iterator {
      public:
        using difference_type = ptrdiff_t;
        using value_type = Node;
        using pointer = Node*;
        using reference = Node&;
        using iterator_category = std::bidirectional_iterator_tag;
        
        iterator(pointer ptr_) : ptr(ptr_) {}

        iterator(const iterator& other) : ptr(other.ptr) {}

        iterator& operator=(const iterator& other) {
          ptr = other.ptr;
        }

        iterator& operator++() {
          //if (ptr->next == NULL)
          //  return iterator(end_iter);
          //iterator i = *this;
          ptr = ptr->next;
          return *this;
        }

        iterator operator++(int junk) {
          ptr = ptr->next;
          return *this;
        }

        T operator*() const {
          return ptr->data;
        }

        T* operator->() const {
          return &ptr->data;
        }

        iterator& operator--() {
          //iterator i = *this;
          ptr = ptr->prev;
          return *this;
        }

        iterator operator--(int junk) {
          ptr = ptr->prev;
          return *this;
        }

        bool operator==(iterator other) const {
          return ptr == other.ptr;
        }

        bool operator!=(iterator other) const {
          return ptr != other.ptr;
        }
        
        pointer getNode() {
          return ptr;
        }

      public:
        pointer ptr;
    };

    class const_iterator {
      public:
        using difference_type = ptrdiff_t;
        using value_type = Node;
        using pointer = Node*;
        using reference = Node&;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator(pointer ptr_) : ptr(ptr_) {}

        const_iterator(const iterator& other) : ptr(other.ptr) {}

        const_iterator& operator=(const const_iterator& other) {
          ptr = other.ptr;
        }

        const_iterator& operator++() {
          //const_iterator i = *this;
          ptr = ptr->next;
          return *this;
        }

        const_iterator operator++(int junk) {
          ptr = ptr->next;
          return *this;
        }

        T operator*() const {
          return ptr->data;
        }

        T* operator->() const {
          return &ptr->data;
        }

        const_iterator& operator--() {
          //iterator i = *this;
          ptr = ptr->prev;
          return *this;
        }

        const_iterator operator--(int junk) {
          ptr = ptr->prev;
          return *this;
        }

        bool operator==(const_iterator other) const {
          return ptr == other.ptr;
        }

        bool operator!=(const_iterator other) const {
          return ptr != other.ptr;
        }
        
        pointer getNode() {
          return ptr;
        }

      public:
        pointer ptr;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /*Alloc alloc_helper(size_t allocSize) {
      Alloc<T> al;
      T* a = al.allocate(allocSize);
      return a;
    }*/

    list(){
      head = NULL;
      tail = NULL;
      elemCnt = 0;
    }

    explicit list(const Alloc& alloc) {
      Node* n = alloc.allocate(1);
      alloc.construct(n, list());
    }

    list(size_t count, const T& value, const Alloc& alloc = Alloc()) {
      head = NULL;
      tail = NULL;
      elemCnt = 0;
      while (elemCnt < count) {
        this->push_back(value);
      }
    }
    
    explicit list(size_t count, const Alloc& alloc = Alloc()) {
      head = NULL;
      tail = NULL;
      elemCnt = 0;
      while (elemCnt < count) {
        this->push_back(T());
      }
    }

    ~list() {
      
    }

    list(const list& other) {
      if (!this->empty())
        this->clear();

      Node* temp = other.head;
      while (temp != NULL) {
        this->push_back(temp->data);
      }
      elemCnt = other.elemCnt;
    }

    list(list&& other) {
      if (!this->empty())
        this->clear();

      Node* temp = other.head;
      while (temp != NULL) {
        this->push_back(temp->data);
      }
      elemCnt = other.elemCnt;
    }

    list& operator=(const list& other) {
      std::cout<< "here" << std::endl;
      list temp(other);
      std::swap(head, temp.head);
      
      return *this;
    }

    list& operator=(list&& other) {
      std::cout<< "here" << std::endl;
      std::swap(other.head, head);
      return *this;
    }

    Alloc get_allocator() const;


    T& front() {
      return head->data;
    }
    const T& front() const {
      return head->data;
    }

    T& back() {
      return tail->data;
    }
    const T& back() const {
      return tail->data;
    }

    iterator begin() {
      return iterator(head);
    }
    
    iterator end() {
      if (tail->next != NULL) {
        Node* temp = new Node(T());
        tail->next = temp;
        temp->prev = tail;
        return iterator(temp);
      }
      return tail->next;
    }

    const_iterator cbegin() const {
      return const_iterator(head);
    }

    const_iterator cend() const {
      return const_iterator(tail);
    }

    reverse_iterator rbegin() {
      return reverse_iterator(head);
    }
    
    reverse_iterator rend() {
      return reverse_iterator(tail);
    }

    const_reverse_iterator crbegin() const {
      return const_reverse_iterator(head);
    }
    
    const_reverse_iterator crend() const {
      const_reverse_iterator(tail);
    }


    bool empty() const {
      if (elemCnt > 0) {
        return false;
      }
      return true;
    }

    size_t size() const {
      return elemCnt;
    }

    size_t max_size() const;

    void clear() {
      while (head) {
        Node* next = head->next;
        head->~Node();
        delete head;
        head = next;
      }
      tail = NULL;
      elemCnt = 0;
    }

    void insertBefore(const_iterator pos, T value) {
      Node* node = pos.getNode();
      if (node == this->end().ptr) {
        this->push_back(value);
      } else if (node == head) {
        this->push_front(value);
      } else {
        Node* newNode = new Node(value, NULL, NULL);
        Node* temp = node->prev;
        node->prev = newNode;
        newNode->next = node;
        temp->next = newNode;
        newNode->prev = temp;
      }
    }

    iterator insert(const_iterator pos, const T& value) {
      insertBefore(pos, value);
    }

    iterator insert(const_iterator pos, T&& value) {
      insertBefore(pos, value);
    }

    iterator insert(const_iterator pos, size_t count, const T& value) {
      for (int i = 0; i < count; i++) {
        insertBefore(pos, value);
      }
    }
    
    iterator erase(const_iterator pos) {
      if (tail->next == NULL) {
        Node* temp = new Node(T());
        tail->next = temp;
        temp->prev = tail;
      }
      
      if (elemCnt == 0) {
        //skip
      }
      
      if (elemCnt == 1) {
        pop_back();
        return this->end();
      }
  
      Node* cur = pos.getNode();
      
      if (cur == head) {
        pop_front();
        return iterator(head);
      } else if (cur == tail) {
        pop_back();
        return this->end();
      } else {
        Node* ret = cur->next;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
        elemCnt--;
        return iterator(ret);
      }
    }
  
    iterator erase(const_iterator first, const_iterator last) {
      Node* cur = first.getNode();
      Node* last_elem = last.getNode();
      
      while (!cur->same(last_elem)) {
        Node* tmp = cur->next;
        erase(iterator(cur));
        cur = tmp;
      }
      
      return iterator(cur);
    }


    void push_back(const T& value) {
      Node* newNode = new Node(value, NULL, NULL);
      //newNode->data = std::move(value);
      //memcpy(&newNode->data, &value, sizeof(value));
      //newNode->prev = NULL;
      //newNode->next = NULL;
      if (this->empty()) {
        head = newNode;
        tail = newNode;
      } else {
        Node* temp = tail;
        tail->next = newNode;
        tail = newNode;
        tail->prev = temp;
      }
      elemCnt++;
    }

    void push_back(T&& value) {
      Node* newNode = new Node(value, NULL, NULL);
      //Node* newNode = malloc(sizeof(T*));// = new Node(value, NULL, NULL);
      //newNode->data = std::move(value);
      //memcpy(&newNode->data, &value, sizeof(value));
      //std::cout << "read" << std::endl;
      //newNode->prev = NULL;
      //newNode->next = NULL;
      if (this->empty()) {
        head = newNode;
        tail = newNode;
      } else {
        Node* temp = tail;
        tail->next = newNode;
        tail = newNode;
        tail->prev = temp;
      }
      elemCnt++;
    }

    void pop_back() {
      if (this->empty())
        return;
      Node* temp = tail;
      tail = tail->prev;
      delete temp;
      elemCnt--;
    }

    void push_front(const T& value) {
      Node* newNode = new Node(value, NULL, NULL);
      if (this->empty()) {
        tail = newNode;
        head = newNode;
      } else {
        Node* temp = head;
        newNode->next = head;
        head = newNode;
        temp->prev = newNode;
      }
      elemCnt++;
    }

    void push_front(T&& value) {
      Node* newNode = new Node(value, NULL, NULL);
      //newNode->data = std::move(value);
      //memcpy(&newNode->data, &value, sizeof(value));
      //newNode->prev = NULL;
      //newNode->next = NULL;
      if (this->empty()) {
        tail = newNode;
        head = newNode;
      } else {
        Node* temp = head;
        newNode->next = head;
        head = newNode;
        temp->prev = newNode;
      }
      elemCnt++;
    }

    void pop_front() {
      if (this->empty())
        return;
      Node* temp = head;
      head = head->next;
      delete temp;
      elemCnt--;
    }

    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
      Node* newNode = new Node(T(std::forward<Args>(args)...));
      Node* temp = pos.ptr->prev;
      pos.ptr->prev = newNode;
      newNode->next = pos.ptr;
      temp->next = newNode;
      newNode->prev = temp;
    }

    template <class... Args>
    void emplace_back(Args&&... args) {
      T temp = T(std::forward<Args>(args)...);
      //newNode->prev = tail;
      //tail->next = newNode;
      //tail = newNode;
      this->push_back(temp);
    }

    template <class... Args>
    void emplace_front(Args&&... args) {
      Node* newNode = new Node(T(std::forward<Args>(args)...));
      newNode->next = head;
      head->prev= newNode;
      head = newNode;
    }

    void resize(size_t count, T value = T()) {
      if (count > elemCnt) {
        while (elemCnt != count) {
          this->push_back(value);
        }
      } else {
        while (elemCnt != count) {
          this->pop_back();
        }
      }
    }
    
    void swap(list& other) {
      list temp = list(other);

      other.head = head;
      other.tail= tail;
      other.elemCnt = elemCnt;

      head = temp.head;
      tail = temp.tail;
      elemCnt = temp.elemCnt;

      other.clear();
    }


    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void remove(const T& value);
    void reverse();
    void unique();
    
    void sort() {
      int i;
      bool swapped = true;;
      Node* ptr;
      Node* lptr = NULL;
    
      if (elemCnt == 0) {
        return;
      }
    
      Node* start = head;
      while (swapped) {
        swapped = 0;
        ptr = start;
    
        while (ptr->next != lptr) {
          if (ptr->data > ptr->next->data) {
            std::swap(ptr->data, ptr->next->data);
            swapped = 1;
          }
          ptr = ptr->next;
        }
        lptr = ptr;
      }  
    }

    // Your code goes here?..
    Node* head;
    Node* tail;
    size_t elemCnt;
};

}  // namespace task
