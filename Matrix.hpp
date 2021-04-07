//
// Created by nelly on 4/5/21.
//

#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <iomanip>

#include "Proxy_Matrix.hpp"


class Matrix {
 private:
  size_t rows, cols;
  Proxy_Matrix *matrix;

 public:
  Matrix(): rows(0), cols(0), matrix(nullptr){};
  Matrix(size_t new_row, size_t new_col);
  Matrix(const Matrix& matr);
  Matrix& Matrix_zeros();
  Matrix& Matrix_unit();
  size_t getRows() const { return rows; };
  size_t getColumns() const { return cols; };
  Proxy_Matrix& operator[] (size_t get_row) const;
  Proxy_Matrix& operator[] (size_t get_row);
  Matrix& operator= (const Matrix& new_mat);
  bool operator== (const Matrix& new_mat) const;
  bool operator!= (const Matrix& new_mat) const;

  Matrix& operator*= (const int32_t a);
  Matrix operator+ (const Matrix& new_mat) const;
  ~Matrix();

  friend std::ostream& operator<< (std::ostream &out, const Matrix &matr);

};



