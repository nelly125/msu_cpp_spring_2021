//
// Created by nelly on 3/20/21.
//
#include <iostream>
#include <cstddef>

#pragma once

class Allocator {
 private:
  char *begin;
  size_t memory_size;
  size_t current;

 public:
  Allocator() : begin(nullptr), memory_size(0), current(0) {}

  void makeAllocator(size_t maxSize) {
    if (begin == nullptr) {
      allocate_memory(maxSize);
    }
    else{
      if(maxSize > memory_size){
        delete[] begin;
        allocate_memory(maxSize);
      }
      else{
        current = 0;
        memory_size = maxSize;
        }
      }
  }

  char *alloc(size_t size) {
    if ( size < 1 || current + size > memory_size){
      return nullptr;
    }
    else{
      char* new_current = begin + current;
      current += size;
      return new_current;
    }
  }

  void reset() {
    current = 0;
  }

  char* get_ptr(size_t size)
  {
    return begin + size;
  }

  ~Allocator(){
    delete[] begin;
  }
 private:
  void allocate_memory(size_t maxSize){
    try {
      begin = new char[maxSize];
      current = 0;
      memory_size = maxSize;
    } catch (std::bad_alloc &ba) {
      std::cerr << "bad_alloc caught " << ba.what() << "\n";
      begin = nullptr;
    }
  }
};