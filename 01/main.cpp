#include <cassert>
#include "Allocator.hpp"

void test_zero_pointer() {
  Allocator allocator;
  char *test;
  allocator.makeAllocator(0);
  test = allocator.alloc(1);
  assert(test == nullptr);
  allocator.reset();
}

void alloc_without_make() {
  Allocator allocator3;
  char *test;
  test = allocator3.alloc(5);
  assert(test == nullptr);
}

void test_wrong_alloc() {
  Allocator allocator;
  char *test;

  /*** alloc out-of-bounds ***/
  allocator.makeAllocator(5);
  test = allocator.alloc(6);
  assert(test == nullptr);

  /*** alloc(0) ***/
  test = allocator.alloc(0);
  assert(test == nullptr);
}

void test_alloc() {
  Allocator allocator;
  char *test;
  allocator.makeAllocator(5);
  /*** alloc ***/
  test = allocator.alloc(4);
  assert(test != nullptr);

  /*** out-of-bounds: size > allocator size ***/
  test = allocator.alloc(5);
  assert(test == nullptr);
}

void test_realloc() {
  char *test;
  Allocator allocator;
  size_t MaxSize = 150;
  allocator.makeAllocator(MaxSize);
  test = allocator.alloc(10);

  for(size_t i = 0; i < MaxSize - 10; i += 10) {
    assert(test == allocator.get_ptr(i));
    test = allocator.alloc(10);
  }
  /*** re-allocation size_new < size_old ***/
  allocator.makeAllocator(70);
  test = allocator.alloc(15);
  assert(test != nullptr);

  /*** re-allocation size_new > size_old ***/
  allocator.makeAllocator(200);
  test = allocator.alloc(50);
  assert(test != nullptr);
}

void test_reset() {
  char *test;
  Allocator allocator;
  allocator.makeAllocator(10);
  allocator.alloc(10);
  allocator.reset();
  test = allocator.alloc(10);
  assert(test != nullptr);
}

int main() {
  test_zero_pointer();
  alloc_without_make();
  test_wrong_alloc();
  test_alloc();
  test_realloc();
  test_reset();
  std::cout << "All tests passed successfully!" << std::endl;
  return 0;
}
