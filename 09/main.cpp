#include <iostream>
#include <cassert>
#include "Sort_files.hpp"

void create_file(const size_t number, const std::string &fn) {
  std::ofstream out(fn, std::ios::binary);
  for (size_t i = 0; i < number; ++i) {
    uint64_t num = rand();
    out.write(reinterpret_cast<char *>(&num), sizeof(uint64_t));
  }
  out.close();
}

void simple_sort() {
  size_t size = 100;
  std::ofstream out("input.txt", std::ios::binary);
  for (uint64_t i = 0; i < size; ++i) {
    uint64_t num = i;
    out.write(reinterpret_cast<char *>(&num), sizeof(uint64_t));
  }
  out.close();

  Sort_file("input.txt");

  std::ifstream output("output.txt");
  uint64_t current, previous = 0;
  for (uint64_t i = 0; i < size; ++i) {
    output.read(reinterpret_cast<char *>(&current), sizeof(uint64_t));
    assert(previous <= current);
  }
  output.close();

  std::cout << "TEST_1 RESULT: SIMPLE SORT TEST IS COMPLETED" << std::endl;
}

void big_sort_test() {
  size_t size = 1000*1000;
  std::ofstream out("input.txt", std::ios::binary);
  for (size_t i = 0; i < size; ++i) {
    uint64_t num = rand();
    out.write(reinterpret_cast<char *>(&num), sizeof(uint64_t));
  }
  out.close();

  Sort_file("input.txt");

  uint64_t *temp = new uint64_t[size];
  std::ifstream output("output.txt", std::ios::binary);
  if (!output)
    throw std::runtime_error("Can't open file output.txt");
  output.read(reinterpret_cast<char *>(temp), size*sizeof(uint64_t));
  uint64_t current, previous = 0;
  for (uint64_t i = 0; i < size; ++i) {
    output.read(reinterpret_cast<char *>(&current), sizeof(uint64_t));
    assert(previous <= current);
  }
  assert(std::is_sorted(temp, temp + size));
  delete[] temp;
  output.close();

  std::cout << "TEST_2 RESULT: BIG SORT TEST IS COMPLETED" << std::endl;
}

void big2_sort_test() {
  size_t size = 10000000;
  std::ofstream out("input.txt", std::ios::binary);
  for (size_t i = 0; i < size; ++i) {
    uint64_t num = rand();
    out.write(reinterpret_cast<char *>(&num), sizeof(uint64_t));
  }
  out.close();

  Sort_file("input.txt");

  uint64_t *temp = new uint64_t[size];
  std::ifstream output("output.txt", std::ios::binary);
  if (!output)
    throw std::runtime_error("Can't open file output.txt");
  output.read(reinterpret_cast<char *>(temp), size*sizeof(uint64_t));
  uint64_t current, previous = 0;
  for (uint64_t i = 0; i < size; ++i) {
    output.read(reinterpret_cast<char *>(&current), sizeof(uint64_t));
    assert(previous <= current);
  }
  assert(std::is_sorted(temp, temp + size));
  delete[] temp;
  output.close();
//  std::remove("input.txt");
//  std::remove("output.txt");

  std::cout << "TEST_3 RESULT: BIG SORT TEST IS COMPLETED" << std::endl;
}

void file_not_found_test() {
  try {
    Sort_file("input_0.txt");
  } catch (std::runtime_error &err) {
    std::string catch_error("Can't open file input_0.txt");
    assert(err.what() == catch_error);
  }

  std::cout << "TEST_4 RESULT: FILE NOT FOUND TEST IS COMPLETED" << std::endl;
}



int main() {
  simple_sort();
  big_sort_test();
  big2_sort_test();
  file_not_found_test();

  return 0;
}
