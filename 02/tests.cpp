//
// Created by nelly on 3/29/21.
//

#include "tests.hpp"

static uint64_t string_length = 0;
static uint64_t sum = 0;
static std::string token_string{};

void start() {
  std::cout << "Start parsing" << std::endl;
}

void end() {
  std::cout << "Finish parsing" << std::endl;
}

void sum_of_numbers (uint64_t number) {
  std::cout << "Digit was found: " << number << std::endl;
  sum += number;
}

void sum_of_string_tokens (const std::string& str){
  std::cout << "String was found: " << str << std::endl;
  token_string += str + ' ';
  string_length +=  str.length();
}

/*** Test without callback functions. ***/

void init_test_1() {
  sum = 0;
  token_string = {};
  TokenParser p;
  p.Parser(std::string{"This is the test without initialization callback functions..."});
  assert(sum == 0 && token_string.length() == 0);
  std::cout << "TEST_1 RESULT: INIT TEST IS COMPLETED" << std::endl;
}

/*** The test containing string with letters and numbers.
 * The function "sum_of_string_tokens" concatenates all parsing words to one string
 * The function "sum" adds parsing values. ***/

void test_2() {
  sum = 0;
  string_length = 0;
  token_string = {};
  TokenParser p;
  p.SetStartCallback(start);
  p.SetEndCallback(end);
  p.SetDigitTokenCallback(sum_of_numbers);
  p.SetStringTokenCallback(sum_of_string_tokens);
  p.Parser(std::string{"One two three four five 1 2 3 4 5"});
  assert(sum == 15 && string_length == 19);
  std::cout << "TEST_2 RESULT: TEST WITH CALLBACKS IS COMPLETED" << std::endl;

  //signed number is string?
  sum = 0;
  string_length = 0;
  token_string = {};
  p.Parser(std::string{"   -15 10"});
  assert(sum == 10 && string_length == 3);
  std::cout << "TEST_2 RESULT: TEST WITH SIGNED NUMBER IS COMPLETED" << std::endl;
}

/*** MIXED STRING ***/

void test3 () {
  sum = 0;
  string_length = 0;
  token_string = {};
  TokenParser p;
  p.SetStartCallback(start);
  p.SetEndCallback(end);
  p.SetDigitTokenCallback(sum_of_numbers);
  p.SetStringTokenCallback(sum_of_string_tokens);
  p.Parser(std::string{"   \t\n one~two 1\nt^%$(%three 9) 2"});
  assert(sum == 3);
  std::cout << "TEST_3 RESULT: TEST WITH MIXED STRING IS COMPLETED" << std::endl;
}