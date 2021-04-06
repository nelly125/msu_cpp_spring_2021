//
// Created by nelly on 4/5/21.
//

#pragma once

#include <stdexcept>
#include <cstdint>
#include <cstddef>

class Proxy_Matrix {
 private:
  size_t proxy_row;
  int32_t *proxy_matrix;

 public:
  Proxy_Matrix();
  Proxy_Matrix(size_t n);
  void Add_row(size_t row);
  void Delete_row();
  int32_t &operator[](size_t get_row) const;
  int32_t &operator[](size_t get_row);
  ~Proxy_Matrix() {};

};
