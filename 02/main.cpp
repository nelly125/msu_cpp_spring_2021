#include <iostream>
#include "TokenParser.hpp"

int main() {
  std::string str = " a\t\t 1 b c\n d e h"; //тест провален исправить a не считает
  TokenParser text_parser;
  text_parser.Parser(str);
  return 0;
}
