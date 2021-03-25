//
// Created by nelly on 3/25/21.
//

#include <iostream>
#include <cstddef>
#include "Allocator.hpp"

Allocator::Allocator() : begin(nullptr), memory_size(0), current(0) {}

Allocator::~Allocator() {
  if (begin != nullptr)
    delete[] begin;
}

void Allocator::makeAllocator(size_t maxSize) {
  if (begin == nullptr) {
    allocate_memory(maxSize);
  } else {
    if (maxSize > memory_size) {
      delete[] begin;
      allocate_memory(maxSize);
    } else {
      current = 0;
      memory_size = maxSize;
    }
  }
}

char *Allocator::alloc(size_t size) {
  if (begin == nullptr)
    return nullptr;
  if ((size < 1) || (current + size > memory_size)) {
    return nullptr;
  } else {
    char *new_current = begin + current;
    current += size;
    return new_current;
  }
}

void Allocator::reset() {
  current = 0;
}

char *Allocator::get_ptr(size_t size) {
  return begin + size;
}

void Allocator::allocate_memory(size_t maxSize) {
  try {
    begin = new char[maxSize];
    current = 0;
    memory_size = maxSize;
  } catch (std::bad_alloc &ba) {
    std::cerr << "bad_alloc caught " << ba.what() << "\n";
    begin = nullptr;
  }
}