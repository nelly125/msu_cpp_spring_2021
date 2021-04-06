#include <iostream>
#include <cassert>
#include "Matrix.hpp"
#include "Proxy_Matrix.hpp"

void initialization_test() {
  /*row = 0 || col = 0*/
  size_t n = 0, m = 0;
  try { Matrix matrix0(n, m); }
  catch (const std::out_of_range &oor) {
    std::cout << "Exception: " << oor.what() << std::endl;
  }

  /*getRows, getColumns*/
  n = 3, m = 5;
  Matrix matrix1(n, m);
  Matrix matrix2(n, n);
  assert(matrix1.getRows() == 3 && matrix1.getColumns() == 5);

  matrix1.Matrix_zeros();
  matrix2.Matrix_unit();

  /*Unit matrix*/
  try { matrix1.Matrix_unit(); }
  catch (const std::out_of_range &oor) {
    std::cout << "Exception: " << oor.what() << std::endl;
  }

  try { matrix1[10][10] = 5; }
  catch (const std::out_of_range &oor) {
    std::cout << "Exception: " << oor.what() << std::endl;
  }

  try { matrix1[1][10] = 5; }
  catch (const std::out_of_range &oor) {
    std::cout << "Exception: " << oor.what() << std::endl;
  }

  std::cout << "TEST_1 RESULT: INIT TEST IS COMPLETED" << std::endl;
}

void arithmetic_operations() {
  /*add element*/
  {
    size_t row = 10, col = 15;
    Matrix m(row, col);
    m[1][1] = 5;
    assert(m[1][1] == 5);
  }

  /*multiplication *= */
  {
    size_t row = 10, col = 10;
    Matrix matrix1(row, col);
    Matrix matrix2(row, col);
//    Matrix matrix3(matrix1);
//    std::cout << matrix3;
    matrix1.Matrix_unit();
    matrix1 *= 5;
    assert(matrix1[1][1] == 5 && matrix1[0][1] == 0);
  }
  /*equality, inequality*/
  {
    size_t row = 10, col = 10;
    Matrix matrix1(row, col);
    Matrix matrix2(row, col);
    assert(matrix1 == matrix1);
    assert(matrix1 == matrix2);
    Matrix matrix3(5, 10);
    assert(!(matrix1 == matrix3));
    assert(matrix1 != matrix3);
  }
  /* operator = */
  {
    size_t row = 10, col = 10;
    Matrix matrix1;
    Matrix matrix2(row, col);
    matrix2.Matrix_unit();
    matrix1 = matrix2;
    for (size_t i = 0; i < matrix1.getRows(); i++)
      for (size_t j = 0; j < matrix1.getColumns(); j++)
        assert(matrix1[i][j] == matrix2[i][j]);
  }

  /*addition*/
  {
    size_t row = 10, col = 10;
    Matrix matrix1(row, col);
    Matrix matrix2(row, col);
    Matrix matrix3(row, col);
    row = 5;
    Matrix matrix4(row, col);

    matrix1.Matrix_zeros();
    matrix2.Matrix_unit();
    matrix3 = matrix1 + matrix2;
    for (size_t i = 0; i < matrix1.getRows(); i++)
      for (size_t j = 0; j < matrix1.getColumns(); j++)
        assert(matrix3[i][j] == (matrix1[i][j] + matrix2[i][j]));

    try { matrix1 + matrix4; }
    catch (const std::out_of_range &oor) {
      std::cout << "Exception: " << oor.what() << std::endl;
    }
  }
  std::cout << "TEST_2 RESULT: ARITHMETIC OPERATIONS TEST IS COMPLETED" << std::endl;
}

void output() {
  size_t row = 10, col = 7;
  Matrix matrix(row, col);
  for (size_t i = 0; i < matrix.getRows(); i++)
    for (size_t j = 0; j < matrix.getColumns(); j++)
      matrix[i][j] = (i + 1)*(j + 1);
  std::cout << matrix << std::endl;
}

int main() {
  initialization_test();
  arithmetic_operations();
  output();
  return 0;
}