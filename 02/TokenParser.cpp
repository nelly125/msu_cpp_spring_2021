//
// Created by nelly on 3/27/21.
//

#include <iostream>
#include <sstream>
#include "TokenParser.hpp"

TokenParser::TokenParser() :
    StartCallback(nullptr),
    FinishCallback(nullptr),
    DigitTokenCallback(nullptr),
    StringTokenCallback(nullptr) {}

TokenParser::~TokenParser() = default;

void TokenParser::SetStartCallback(const std::function<void()> &start_callback) {
  StartCallback = start_callback;
}

void TokenParser::SetEndCallback(const std::function<void()> &finish_callback) {
  FinishCallback = finish_callback;
}

void TokenParser::SetDigitTokenCallback(const std::function<void(const uint64_t)>
                                        &digit_callback) {
  DigitTokenCallback = digit_callback;
}

void TokenParser::SetStringTokenCallback(const std::function<void(const std::string &)>
                                         &string_callback) {
  StringTokenCallback = string_callback;
}

bool TokenParser::IsDigit(const std::string &str) {
  for (char i : str) {
    if (!isdigit(i))
      return false;
  }
  return true;
}

uint64_t TokenParser::StrToInt(const std::string &str) {
  std::stringstream stream(str);
  uint64_t result;
  stream >> result;
  return result;
}

void TokenParser::Type_of_token(const std::string &temp_token) {
  bool flag = true; //digit
  uint64_t digit;
  if (!IsDigit(temp_token))
    flag = false;

  if (flag) {
    std::string token;
    size_t pos = 0;
    for (auto c: temp_token)
      if (c == '0')
        pos++;
      else
        break;
    token = temp_token.substr(pos, std::string::npos);
    digit = StrToInt(token);
    std::string asString = std::to_string(digit);
    if (asString != token)
      flag = false;
  }
  if (flag) {
    log_is_digit.push_back(true);
    if (DigitTokenCallback != nullptr)
      DigitTokenCallback(digit);
  }
  if (!flag) {
    log_is_digit.push_back(false);
    if (StringTokenCallback != nullptr)
      StringTokenCallback(temp_token);
  }
  log_str.push_back(temp_token);
  count++;
}

void TokenParser::Parser(const std::string &str) {
  count = 0;
  log_is_digit.clear();
  log_str.clear();

  if (StartCallback != nullptr)
    StartCallback();
  std::string token;
  std::string delimiter = " \t\n";

  size_t pos = 0, begin = 0;
  pos = str.find_first_of(delimiter);

  while (pos != std::string::npos) {
    if (begin == pos) {
      begin = pos + 1;
    } else {
      token = str.substr(begin, pos - begin);
      begin = pos + 1;
      Type_of_token(token);
    }
    pos = str.find_first_of(delimiter, begin);
  }
  token = str.substr(begin, pos - begin);
  if (!token.empty())
    Type_of_token(token);
  if (FinishCallback != nullptr)
    FinishCallback();
}

