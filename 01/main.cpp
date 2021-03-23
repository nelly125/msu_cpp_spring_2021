#include <cassert>
#include "Allocator.hpp"
#include <ctime>

int main() {
  Allocator allocator;
  char* test;
  allocator.makeAllocator(0);

  /*** test_1 Zero pointer ***/
  test = allocator.alloc(1);
  assert(test == nullptr);
  allocator.reset();

  /*** test_2 alloc out-of-bounds ***/
  allocator.makeAllocator(5);
  test = allocator.alloc(6);
  assert(test == nullptr);

  /*** test_3 alloc(0) ***/
  test = allocator.alloc(0);
  assert(test == nullptr);

  /*** test_4 alloc ***/
  test = allocator.alloc(4);
  assert(test != nullptr);

  /*** test_5 out-of-bounds ***/
  test = allocator.alloc(5);
  assert(test == nullptr);

  /*** test_6 new allocator ***/
  Allocator allocator2;
  size_t MaxSize = 150;
  allocator2.makeAllocator(MaxSize);
  test = allocator2.alloc(10);
  for (size_t i = 0; i < MaxSize-10; i += 10) {
    assert(test == allocator2.get_ptr(i));
    test = allocator2.alloc(10);
  }

  /*** test_7 re-allocation size_new < size_old ***/
  allocator2.makeAllocator(70);
  test = allocator2.alloc(15);
  assert(test != nullptr);

  /*** test_8 re-allocation size_new > size_old ***/
  allocator2.makeAllocator(200);
  test = allocator2.alloc(50);
  assert(test != nullptr);

/*** time test ***/
/*
  Allocator allocator3;
  allocator3.makeAllocator(100000000);
  clock_t start = clock();
  for (size_t i = 0; i < 100000000; i++)
  {
    test = allocator3.alloc(i);
  }
  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  std::cout << "The time of allocation of 100000000 elements is " << seconds << " seconds";
*/

  return 0;
}
