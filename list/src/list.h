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
      
      bool operator==(Node* other) {
        return data == other.data;
      }
      
      bool operator!=(Node* other) {
        return data != other.data;
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
          //iterator i = *this;
          ptr = ptr->next;
          return *this;
        }

        iterator operator++(int junk) {
          ptr = ptr->next;
          return *this;
        }

        reference operator*() const {
          return *ptr;
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

        reference operator*() const {
          return *ptr;
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

        bool operator==(iterator other) const {
          return ptr == other.ptr;
        }

        bool operator!=(iterator other) const {
          return ptr != other.ptr;
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
    }

    list(list&& other) {
      if (!this->empty())
        this->clear();

      Node* temp = other.head;
      while (temp != NULL) {
        this->push_back(temp->data);
      }
    }

    /*bool operator==(const std::list<T>& other) {
      Node* temp = begin();
      Node* tempOther = other.begin();

      if (elemCnt != other.elemCnt)
        return false;

      while (temp != NULL) {
        if (temp->data != tempOther->data)
          return false;
        temp = temp->next;
        tempOther = tempOther->next;
      }
      return true;
    }*/

    list& operator!=(const list& other) {
      return !(this == other);
    }

    list& operator=(const list& other) {
      //if (*this == other)
      //  return *this;

      if (!this->empty())
        this->clear();

      head = other.head;
      tail = other.tail;
      elemCnt = other.elemCnt;
    }

    list& operator=(list&& other) {
      //if (*this == other)
      //  return *this;

      if (!this->empty())
        this->clear();

      head = other.head;
      tail = other.tail;
      elemCnt = other.elemCnt;
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
      return iterator(tail);
    }

    const_iterator cbegin() const {
      return const_iterator(head);
    }

    const_iterator cend() const {
      return const_iterator(tail);
    }

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;


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
      while(head != NULL) {
        Node* temp = head;
        head = head->next;
      }
      elemCnt = 0;
      head = NULL;
      tail = NULL;
    }

    void insertBefore(Node* node, T value) {
      Node* newNode = new Node(value, NULL, NULL);
      Node* temp = node->prev;
      node->prev = newNode;
      newNode->next = node;
      temp->next = newNode;
      newNode->prev = temp;
    }

    iterator insert(const_iterator pos, const T& value) {
      insertBefore(pos, value);
    }

    iterator insert(const_iterator pos, T&& value) {
      insertBefore(pos.ptr, value);
    }

    iterator insert(const_iterator pos, size_t count, const T& value);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);


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
        head = temp;
        temp->prev = head;
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
        head = temp;
        temp->prev = head;
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
    void sort();

    // Your code goes here?..
    Node* head;
    Node* tail;
    size_t elemCnt;

};

// Your template function definitions may go here...

}  // namespace task
