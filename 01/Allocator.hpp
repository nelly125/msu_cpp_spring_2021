//
// Created by nelly on 3/20/21.
//
#pragma once

#include <iostream>
#include <cstddef>

class Allocator {
 private:
  char *begin;
  size_t memory_size;
  size_t current;

 public:
  Allocator();
  ~Allocator();
  void makeAllocator(size_t maxSize);
  char *alloc(size_t size);
  void reset();
  char *get_ptr(size_t size);
 private:
  void allocate_memory(size_t maxSize);
};