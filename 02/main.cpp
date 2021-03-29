#include <iostream>
#include "TokenParser.hpp"
#include "tests.hpp"



void function_for_string(const std::string &s) {
  std::cout << "String was found: " << s << std::endl;
}

void function_for_digit(uint64_t num) {
  std::cout << "Digit was found: " << num << std::endl;
  std::cout << "The 2d power of digit is " << num * num << std::endl;
}

/*Тест 1, вызов callback и парсинг*/
void test_parsing_with_callback()
{
  //строка и число
  TokenParser p;
  p.SetStartCallback(start);
  p.SetEndCallback(end);
  p.SetDigitTokenCallback(function_for_digit);
  p.SetStringTokenCallback(function_for_string);
  p.Parser("Hello 7");

  //отрицательное число
  p.Parser("-10");
}





int main() {
//  std::string str = " a\t\t 1 b c\n d e h"; //тест провален исправить a не считает
//  TokenParser text_parser;
//  text_parser.Parser(str);

//  test_parsing_with_callback();
  init_test_1();
  test_2();
  test3();

  return 0;
}
