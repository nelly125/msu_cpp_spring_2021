//
// Created by nelly on 5/3/21.
//

#pragma once

#include <memory>
#include <limits>
#include <iostream>

template<class T>
class Allocator : public std::allocator<T> {
 public:
  T *allocate(size_t size) {
    if (size > std::numeric_limits<size_t>::max()/sizeof(T))
      throw std::bad_alloc();
    if (auto p = static_cast<T *>(std::malloc(size*sizeof(T))))
      return p;
    throw std::bad_alloc();
  }

  void deallocate(T *pointer) noexcept {
    std::free(pointer);
  }

  template<typename... Args>
  void construct(T *cur, Args &&... args) {
    new(cur) T(std::forward<Args>(args)...);
  }
  void destroy(T *ptr) noexcept {
    ptr->~T();
  }
};



