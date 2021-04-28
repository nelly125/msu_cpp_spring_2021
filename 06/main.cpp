#include <iostream>
#include <cassert>
#include <chrono>

#include "format.h"


void incorrect_input_test() {
  try {
    auto text = format("{0}");
  } catch (const inv_arg_exc &) {}

  try {
    auto text = format("{1}+{1} = {0}", 2);
  } catch (const inv_arg_exc &err) {
    std::string catch_error("out of range args");
    assert(err.what() == catch_error);
  }

  try {
    auto text = format("{1}+{1}} = {0}", 2, "one");
  } catch (const format_exc &err) {
    std::string catch_error("expected { before }");
    assert(err.what() == catch_error);
  }

  try {
    auto text = format("{1}+{{1} = {0}", 2, "one");
  } catch (const inv_arg_exc &err) {
    std::string catch_error("incorrect input");
    assert(err.what() == catch_error);
  }

  try {
    auto text = format("{1}+{1}{ = {0}", 2, "one");
  } catch (const inv_arg_exc &err) {
    std::string catch_error("incorrect input");
    assert(err.what() == catch_error);
  }

  try {
    auto text = format("{{} = {0}", 2, "one");
  } catch (const inv_arg_exc &err) {
    std::string catch_error("incorrect input");
    assert(err.what() == catch_error);
  }

  try {
    auto text = format("{}[}{} = {0}", 2, "one");
  } catch (const inv_arg_exc &err) {
    std::string catch_error("incorrect input");
    assert(err.what() == catch_error);
  }

  try {
    auto text = format("{1}+{1.5}{ = {0}", 2, "one");
  } catch (const inv_arg_exc &err) {
    std::string catch_error("incorrect input");
    assert(err.what() == catch_error);
  }

  size_t k = 0, n = 0;
  try {
    auto text = format("{1}+{1} = {0aaa}", 2, 1);
  } catch (const inv_arg_exc &exc) {
    k++;
  }
  catch (const format_exc &exc) {
    n++;
  }
  assert(k == 1 && n == 0);
  std::cout << "TEST_1 RESULT: INCORRECT INPUT TEST IS COMPLETED" << std::endl;
}

void input_test() {
  auto text = format("{1}+{1} = {0}", 2, "one");
  assert(text == "one+one = 2");

  text = format("There is no need to format");
  assert(text == "There is no need to format");

  text = format("I have to {0} my {2} {1}", "do", "today", "homework");
  assert(text == "I have to do my homework today");

  //ostream
  auto time = std::chrono::system_clock::now();
  std::time_t time_now = std::chrono::system_clock::to_time_t(time);
  std::string a(std::ctime(&time_now));
  text = format("The time is {0}", a);
  std::cout << text << std::endl;

  std::cout << "TEST_2 RESULT: INPUT TEST IS COMPLETED" << std::endl;
}

int main() {
  incorrect_input_test();
  input_test();
  return 0;
}
