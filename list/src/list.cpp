#include "list.h"
#include <iostream>

namespace task {
  
  template<class T, class Alloc>
  list<T, Alloc>::list() {
    std::cout << "hello" << std::endl;
    head = NULL;
    tail = NULL;
  }
  
  template<class T, class Alloc>
  list<T, Alloc>::~list() {
    
  }
   
  /*explicit task::list::list(const Alloc& alloc) {
    list l = alloc.allocate(1);
    alloc.construct(l);
  }*/
}