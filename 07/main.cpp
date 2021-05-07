#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include "vector.hpp"

void init_test() {
  {
    Vector<int> my_vector;
    assert(my_vector.size() == 0 && my_vector.capacity() == 0);
    try {
      std::cout << my_vector[0];
    }
    catch (const std::out_of_range &) {};
  }

  {
    Vector<int> my_vector(10, 10);
    assert(my_vector.size() == 10 && my_vector.capacity() == 10);
    for (auto &value : my_vector)
      assert(value == 10);
  }

  {
    Vector<std::string> my_vector{"it", "is", "my", "vector"};
    std::vector<std::string> test_vector{"it", "is", "my", "vector"};
    assert(test_vector == my_vector);
  }

}

void push_back_test() {
  {
    Vector<int> my_vector;
    my_vector.push_back(1);
    assert(my_vector.size() == 1);
    assert(my_vector.capacity() == 1);
    my_vector.push_back(2);
    assert(my_vector.size() == 2);
    assert(my_vector.capacity() == 2);
    my_vector.push_back(3);
    assert(my_vector.size() == 3);
    assert(my_vector.capacity() == 4);

    my_vector.pop_back();
    assert(my_vector.size() == 2);
    assert(my_vector.capacity() == 4);

    try {
      std::cout << my_vector[2];
    }
    catch (const std::out_of_range &) {};
  }

  {
    std::ostringstream std_vector_result;
    std::ostringstream my_vector_result;

    Vector<std::string> my_vector;
    std::vector<std::string> std_vector;

    std_vector.push_back("a");
    std_vector.push_back("b");

    my_vector.push_back("a");
    my_vector.push_back("b");

    for (auto &c :std_vector)
      std_vector_result << c << ' ';

    for (auto &c :my_vector)
      my_vector_result << c << ' ';

    assert(std_vector_result.str() == my_vector_result.str());
  }

}

void iterator_test() {
  {
    Vector<int> my_vector = {0, 1, 2, 3, 4, 5};
    Vector<int> my_vector_inverse = {5, 4, 3, 2, 1, 0};
    auto i = my_vector.begin();
    auto j = my_vector_inverse.rbegin();
    for (; i != my_vector.end() && j != my_vector_inverse.rend(); ++i, ++j) {
      assert(*i == *j);
    }
  }
}

void emplace_test() {
  {
    Vector<int> my_vector = {0, 1, 2, 3, 4, 5};
    std::vector<int> std_vector = {0, 1, 2, 3, 4, 5};

    my_vector.emplace_back(5);
    std_vector.emplace_back(5);

    assert(std_vector == my_vector);
  }
  struct Item {
    int a, b, c;
    Item(int a, int b, int c) : a(a), b(b), c(c) {}
  };

  Vector<Item> my_vector;
  my_vector.emplace_back(1, 2, 3);
}

void operator_brackets_test() {
  Vector<int> my_vector = {0, 1, 2, 3, 4, 5};
  std::vector<int> std_vector = {0, 1, 2, 3, 4, 5};

  for (size_t i = 0; i < my_vector.size(); i++)
    assert(my_vector[i] == std_vector[i]);
}

void operator_equality_test() {
  Vector<int> my_vector = {0, 1, 2, 3, 4, 5};
  Vector<int> my_vector_copy;

  std::vector<int> std_vector = {0, 1, 2, 3, 4, 5};
  std::vector<int> std_vector_copy;

  assert(std_vector == my_vector);

  my_vector_copy = my_vector;
  std_vector_copy = std_vector;

  assert(std_vector_copy == my_vector_copy);

  my_vector_copy = std::move(my_vector);
  std_vector_copy = std::move(std_vector);
  assert(std_vector_copy == my_vector_copy);

}

void constructors_test() {

  Vector<std::string> my_words1{"the", "frogurt", "is", "also", "cursed"};
  std::vector<std::string> std_words1{"the", "frogurt", "is", "also", "cursed"};
  assert(std_words1 == my_words1);


  // words2 == words1
  Vector<std::string> my_words2(my_words1);
  std::vector<std::string> std_words2(std_words1);
  assert(std_words2 == my_words2);

//  // words3 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
  Vector<std::string> my_words3(5, "Mo");
  std::vector<std::string> std_words3(5, "Mo");
  assert(std_words3 == my_words3);

  Vector<std::string> my_words4(std::move(my_words1));
  assert(my_words4 == my_words2);
  assert(my_words1.empty());
}

void resize_reverse_test() {
  Vector<int> my_vector;
  std::vector<int> std_vector;

  my_vector.resize(5, 0);
  std_vector.resize(5, 0);

  assert(my_vector.size() == 5);
  assert(std_vector == my_vector);

  my_vector.resize(25);
  std_vector.resize(25);

  assert(my_vector.size() == 25);
  assert(my_vector.capacity() == 25);
  assert(std_vector == my_vector);

  my_vector.reserve(30);
  std_vector.reserve(30);

  assert(my_vector.capacity() == 30);
  assert(my_vector.size() == 25);
  assert(std_vector == my_vector);
}

void empty_test() {
  Vector<int> my_vector;
  assert(my_vector.empty() == true);

  my_vector.push_back(1);
  assert(my_vector.empty() == false);

  my_vector.clear();
  assert(my_vector.empty() == true);
}

void ostream_test() {
  Vector<int> my_vector = {1, 2, 3};
  assert(my_vector.size() == 3 && my_vector.capacity() == 3);

  std::stringstream ss;
  ss << my_vector;
  assert(ss.str() == "1 2 3");
}

int main() {
  init_test();
  push_back_test();
  iterator_test();
  emplace_test();
  operator_brackets_test();
  operator_equality_test();
  constructors_test();
  resize_reverse_test();
  empty_test();
  ostream_test();

  return 0;
}
