#pragma once
#include <iterator>
#include <iostream>

namespace task {


template<class T, class Alloc = std::allocator<T>>
class list {

public:
    class iterator {
    public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator();
        iterator(const iterator&);
        iterator& operator=(const iterator&);

        iterator& operator++();
        iterator operator++(int);
        reference operator*() const;
        pointer operator->() const;
        iterator& operator--();
        iterator operator--(int);

        bool operator==(iterator other) const;
        bool operator!=(iterator other) const;

        // Your code goes here?..

    private:
        // Your code hoes here...
    };

    class const_iterator {
        // Your code goes here...
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    struct Node {
      T data;
      Node* next;
      Node* prev;
      
      Node(T data_, Node* next_, Node* prev_) : data(data_), next(next_), prev(prev_) {}
    };

    list(){
        head = NULL;
        tail = NULL;
        elemCnt = 0;
    }
    
    explicit list(const Alloc& alloc);
    list(size_t count, const T& value, const Alloc& alloc = Alloc());
    explicit list(size_t count, const Alloc& alloc = Alloc());

    ~list() {
        
    }

    list(const list& other);
    list(list&& other);
    list& operator=(const list& other);
    list& operator=(list&& other);

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


    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

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

    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, T&& value);
    iterator insert(const_iterator pos, size_t count, const T& value);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);


    void push_back(const T& value) {
      Node* newNode = new Node(value, NULL, NULL);
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
    iterator emplace(const_iterator pos, Args&&... args);

    template <class... Args>
    void emplace_back(Args&&... args);

    template <class... Args>
    void emplace_front(Args&&... args);

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
    void swap(list& other);


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
