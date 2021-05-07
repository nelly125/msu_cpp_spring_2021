#include "tests.hpp"

int main() {
  test_input();
  test_equality();
  test_compare();
  operator_equal();
  test_addition();
  test_subtraction();
  test_multiplication();
  test_move_operator();
  test_numbers_den();
  test_zero();

  return 0;
}

