//
// Created by nelly on 3/29/21.
//

#include "tests.hpp"

uint64_t string_length = 0;
uint64_t sum = 0;
std::string token_string{};

void start() {
  std::cout << "Start parsing" << std::endl;
}

void end() {
  std::cout << "Finish parsing" << std::endl;
}

void sum_of_numbers(uint64_t number) {
  std::cout << "Digit was found: " << number << std::endl;
  sum += number;
}

void sum_of_string_tokens(const std::string &str) {
  std::cout << "String was found: " << str << std::endl;
  token_string += str + ' ';
  string_length += str.length();
}

/*** Test without callback functions. ***/

void test_1_without_callback_functions() {
  sum = 0;
  token_string = {};
  TokenParser p;
  p.Parser(std::string{""});
  p.Parser(std::string{"This is the test without initialization callback functions..."});
  assert(sum == 0 && token_string.length() == 0);
  std::cout << "TEST_1 RESULT: INIT TEST IS COMPLETED" << std::endl;
}

/*** The test containing string with letters and numbers.
 * The function "sum_of_string_tokens" concatenates all parsing words to one string
 * The function "sum" adds parsing values. ***/

void test_2_with_strings_and_numbers() {
  sum = 0;
  string_length = 0;
  token_string = {};
  TokenParser p;

  p.SetStartCallback(start);
  p.SetEndCallback(end);
  p.SetDigitTokenCallback(sum_of_numbers);
  p.SetStringTokenCallback(sum_of_string_tokens);

  p.Parser(std::string{"One two three four five 1 2 3 4 5"});
  assert(p.get_log_is_digit(0) == false);
  assert(p.get_log_str(0) == "One");
  assert(p.get_log_is_digit(1) == false);
  assert(p.get_log_str(1) == "two");
  assert(p.get_log_is_digit(2) == false);
  assert(p.get_log_str(2) == "three");
  assert(p.get_log_is_digit(3) == false);
  assert(p.get_log_str(3) == "four");
  assert(p.get_log_is_digit(4) == false);
  assert(p.get_log_str(4) == "five");
  assert(p.get_log_is_digit(5) == true);
  assert(p.get_log_str(5) == "1");
  assert(p.get_log_is_digit(6) == true);
  assert(p.get_log_str(6) == "2");
  assert(p.get_log_is_digit(7) == true);
  assert(p.get_log_str(7) == "3");
  assert(p.get_log_is_digit(8) == true);
  assert(p.get_log_str(8) == "4");
  assert(p.get_log_is_digit(9) == true);
  assert(p.get_log_str(9) == "5");

  assert(sum == 15 && string_length == 19);

  std::cout << "TEST_2 RESULT: TEST WITH CALLBACKS IS COMPLETED" << std::endl;

  //signed number is string?
  sum = 0;
  string_length = 0;
  token_string = {};

  p.Parser(std::string{"   -15 10"});
  assert(p.get_log_is_digit(0) == false);
  assert(p.get_log_str(0) == "-15");
  assert(p.get_log_is_digit(1) == true);
  assert(p.get_log_str(1) == "10");

  assert(sum == 10 && string_length == 3);

  std::cout << "TEST_2 RESULT: TEST WITH SIGNED NUMBER IS COMPLETED" << std::endl;
}

/*** MIXED STRING ***/

void test_3_mixed_string() {
  sum = 0;
  string_length = 0;
  token_string = {};
  TokenParser p;

  p.SetStartCallback(start);
  p.SetEndCallback(end);
  p.SetDigitTokenCallback(sum_of_numbers);
  p.SetStringTokenCallback(sum_of_string_tokens);

  p.Parser(std::string{"   \t\n one~two 1\nt^%$(%three 7.8 9) 2"});
  assert(p.get_log_is_digit(0) == false);
  assert(p.get_log_str(0) == "one~two");
  assert(p.get_log_is_digit(1) == true);
  assert(p.get_log_str(1) == "1");
  assert(p.get_log_is_digit(2) == false);
  assert(p.get_log_str(2) == "t^%$(%three");
  assert(p.get_log_is_digit(3) == false);
  assert(p.get_log_str(3) == "7.8");
  assert(p.get_log_is_digit(4) == false);
  assert(p.get_log_str(4) == "9)");
  assert(p.get_log_is_digit(5) == true);
  assert(p.get_log_str(5) == "2");

  assert(sum == 3);

  std::cout << "TEST_3 RESULT: TEST WITH MIXED STRING IS COMPLETED" << std::endl;
}

/*** String has only delimiters ***/
void test_4_with_delimiters() {
  TokenParser p;

  p.Parser(std::string{"\t\t\t   \n "});
  assert(p.get_count() == 0);

  //string_length != 0
  p.Parser(std::string{"\t\t\t   \n ."});
  assert(p.get_count() == 1);
  assert(p.get_log_is_digit(0) == false);
  assert(p.get_log_str(0) == ".");
  std::cout << "TEST_4 RESULT: TEST WITH STRING WITH DELIMITERS IS COMPLETED" << std::endl;
}

/*** Digit > uint64 ***/

void test_5_digit_more_than_uint64() {
  TokenParser p;

  p.Parser(std::string{"18446744073709551617"}); //2^64 + 1
  assert(p.get_log_is_digit(0) == false);
  assert(p.get_log_str(0) == "18446744073709551617");

  p.Parser(std::string{"00000000018446744073709551615"}); //2^64 - 1
  assert(p.get_log_is_digit(0) == true);
  assert(p.get_log_str(0) == "00000000018446744073709551615");

  std::cout << "TEST_5 RESULT: TEST WITH DIGIT > UINT64 IS COMPLETED" << std::endl;
}

void test_6_symbols() {
  TokenParser p;

  p.Parser(std::string{" "});
  assert(p.get_count() == 0);

  p.Parser(std::string{""});
  assert(p.get_count() == 0);

  p.Parser(std::string{"\t"});
  assert(p.get_count() == 0);

  p.Parser(std::string{"a"});
  assert(p.get_count() == 1);
  assert(p.get_log_is_digit(0) == false);
  assert(p.get_log_str(0) == "a");

  p.Parser(std::string{"1"});
  assert(p.get_count() == 1);
  assert(p.get_log_is_digit(0) == true);
  assert(p.get_log_str(0) == "1");

  std::cout << "TEST_6 RESULT: TEST WITH SYMBOLS IS COMPLETED" << std::endl;
}