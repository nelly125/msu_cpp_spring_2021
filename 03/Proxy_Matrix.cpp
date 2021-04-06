//
// Created by nelly on 4/5/21.
//

#include "Proxy_Matrix.hpp"

Proxy_Matrix::Proxy_Matrix() : proxy_row(0), proxy_matrix(nullptr) {}

Proxy_Matrix::Proxy_Matrix(size_t n) {
  proxy_row = n;
  proxy_matrix = new int32_t[proxy_row];
}

int32_t &Proxy_Matrix::operator[](size_t get_row) const {
  if (get_row >= proxy_row) {
    throw std::out_of_range("proxy operator [] error: incorrect value operator[] const");
  }
  return proxy_matrix[get_row];
}

int32_t &Proxy_Matrix::operator[](size_t get_row) {
  if (get_row >= proxy_row) {
    throw std::out_of_range("proxy operator [] error: incorrect value operator[]");
  }
  return proxy_matrix[get_row];
}

void Proxy_Matrix::Add_row(size_t row) {
  proxy_row = row;
  proxy_matrix = new int32_t[proxy_row];
}

void Proxy_Matrix::Delete_row() {
  if (proxy_matrix != nullptr)
    delete[] proxy_matrix;
}