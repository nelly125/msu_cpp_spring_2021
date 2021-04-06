//
// Created by nelly on 4/5/21.
//

#include "Matrix.hpp"

Matrix::Matrix(size_t new_row, size_t new_col) {
  rows = new_row;
  cols = new_col;
  if (new_row == 0 || new_col == 0)
    throw std::out_of_range("constructor error: incorrect value");

  matrix = new Proxy_Matrix[rows];
  for (size_t i = 0; i < rows; i++) {
    matrix[i].Add_row(cols);
  }
  Matrix_zeros();
}

Matrix::Matrix(const Matrix &matr) {
  *this = matr;
}

Matrix::~Matrix() {
  if (matrix != nullptr) {
    for (size_t i = 0; i < rows; i++) {
      matrix[i].Delete_row();
    }
    delete[] matrix;
  }
}

Matrix &Matrix::Matrix_zeros() {
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
      matrix[i][j] = 0;
  return *this;
}

Matrix &Matrix::Matrix_unit() {
  if (rows != cols)
    throw std::out_of_range("Matrix_unit error: matrix is not n*n");
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
      if (i == j)
        matrix[i][j] = 1;
      else
        matrix[i][j] = 0;
  return *this;
}

Proxy_Matrix &Matrix::operator[](size_t get_row) const {
  if (get_row > rows) {
    throw std::out_of_range("operator [] error: incorrect value");
  }
  return matrix[get_row];
}

Proxy_Matrix &Matrix::operator[](size_t get_row) {
  if (get_row > rows) {
    throw std::out_of_range("operator [] error: incorrect value");
  }
  return matrix[get_row];
}

Matrix &Matrix::operator=(const Matrix &new_mat) {
  if (this == &new_mat) return *this;
  if ((rows != new_mat.getRows()) || (cols != new_mat.getColumns())) {
    if (matrix != nullptr) {
      for (size_t i = 0; i < rows; i++) {
        matrix[i].Delete_row();
      }
      delete[] matrix;
    }
    rows = new_mat.getRows();
    cols = new_mat.getColumns();
    matrix = new Proxy_Matrix[rows];
    for (size_t i = 0; i < rows; i++) {
      matrix[i].Add_row(cols);
    }
  }
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
      matrix[i][j] = new_mat[i][j];
  return *this;
}

bool Matrix::operator==(const Matrix &new_mat) const {
  if (this == &new_mat) return true;
  if ((rows != new_mat.getRows()) || (cols != new_mat.getColumns()))
    return false;
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
      if (matrix[i][j] != new_mat[i][j])
        return false;
  return true;
}

bool Matrix::operator!=(const Matrix &new_mat) const {
//  if (this == &new_mat) return true;
  if ((rows != new_mat.getRows()) || (cols != new_mat.getColumns()))
    return true;
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++)
      if (matrix[i][j] != new_mat[i][j])
        return true;
  return false;
}

Matrix &Matrix::operator*=(const int32_t a) {
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < cols; j++) {
      matrix[i][j] *= a;
    }
  return *this;
}

Matrix Matrix::operator+(const Matrix &new_mat) const {
  if (rows != new_mat.getRows() || cols != new_mat.getColumns())
    throw std::out_of_range("operator +: incorrect value");
  Matrix create_matrix(rows, cols);
  for (size_t i = 0; i < cols; i++)
    for (size_t j = 0; j < rows; j++)
      create_matrix[i][j] = matrix[i][j] + new_mat[i][j];
  return create_matrix;
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
  for (size_t i = 0; i < matrix.getRows(); i++) {
    for (size_t j = 0; j < matrix.getColumns(); j++)
      out << std::setw(5) << matrix[i][j] << " ";
    out << "\n";
  }
  return out;
}


