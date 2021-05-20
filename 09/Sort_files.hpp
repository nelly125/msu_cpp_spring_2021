#pragma once

#include <fstream>
#include <thread>
#include <vector>
#include <algorithm>

constexpr size_t MAX_MEMORY_SIZE = 7*128*1024;

void Merge_files(std::vector<std::string> temp_memory_files) {
  uint64_t *temp = new uint64_t[MAX_MEMORY_SIZE];
  uint64_t number;
  size_t right;
  for (size_t i = 1; i < temp_memory_files.size(); ++i) {
    std::ifstream input_right(temp_memory_files[i]);
    if (!input_right)
      throw std::runtime_error("Can't open file " + temp_memory_files[i]);
    input_right.read(reinterpret_cast<char *>(temp), MAX_MEMORY_SIZE/2*sizeof(uint64_t));
    size_t buffer_size = input_right.gcount()/sizeof(uint64_t);
    input_right.close();
    std::ifstream input_left(temp_memory_files[i - 1]);
    input_left.read(reinterpret_cast<char *>(&number), sizeof(uint64_t));
    right = 0;

    std::ofstream output("output.txt");
    while (!input_left.eof() && right < buffer_size) {
      if (number <= temp[right]) {
        output.write(reinterpret_cast<char *>(&number), sizeof(uint64_t));
        input_left.read(reinterpret_cast<char *>(&number), sizeof(uint64_t));
      } else {
        output.write(reinterpret_cast<char *>(&temp[right]), sizeof(uint64_t));
        right++;
      }
    }
    if (input_left.eof()) {
      output.write(reinterpret_cast<char *>(&temp[right]),
                   sizeof(uint64_t)*(MAX_MEMORY_SIZE/2 - right));
    }
    while (!input_left.eof()) {
      output.write(reinterpret_cast<char *>(&number), sizeof(uint64_t));
      input_left.read(reinterpret_cast<char *>(&number), sizeof(uint64_t));
    }
    input_left.close();
    output.close();
  }
  delete[] temp;
  for (size_t i = 0; i < temp_memory_files.size(); i++) {
    const char *filename = temp_memory_files[i].c_str();
    std::remove(filename);
  }
}

void Sort_file(const std::string filename) {
  std::ifstream input(filename);
  if (!input)
    throw std::runtime_error("Can't open file " + filename);

  std::vector<std::string> temp_memory_file;
  size_t buffer_size = input.gcount()/sizeof(uint64_t);

  uint64_t *temp = new uint64_t[MAX_MEMORY_SIZE];
  while (!input.eof()) {
    input.read(reinterpret_cast<char *>(temp), MAX_MEMORY_SIZE*sizeof(uint64_t));
    auto count = input.gcount()/sizeof(uint64_t);
    size_t temp_count = 0;
    if (count > 0) {
      temp_memory_file.push_back("temp " + std::to_string(temp_count));
      temp_count++;
      temp_memory_file.push_back("temp " + std::to_string(temp_count));
      temp_count++;
      std::thread left([temp, buffer_size]() {
        std::sort(temp, temp + buffer_size/2);
      });
      std::thread right([temp, buffer_size]() {
        std::sort(temp + buffer_size/2, temp + buffer_size);
      });
      left.join();
      right.join();

      std::ofstream temp_left(temp_memory_file[temp_count- 2]);
      for (size_t i = 0; i < buffer_size/2; ++i) {
        temp_left.write(reinterpret_cast<char *>(&temp[i]), sizeof(uint64_t));
      }
      temp_left.close();

      std::ofstream temp_right(temp_memory_file[temp_count - 1]);
      for (size_t i = buffer_size/2; i < buffer_size; ++i) {
        temp_right.write(reinterpret_cast<char *>(&temp[i]), sizeof(uint64_t));
      }
      temp_right.close();
    }
  }
  delete[] temp;
  Merge_files(temp_memory_file);
}
