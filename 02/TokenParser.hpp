//
// Created by nelly on 3/27/21.
//

#pragma once

#include <functional>
#include <vector>
#include <cstring>

class TokenParser {
 private:
  std::vector<std::string> log_str;
  std::vector<bool> log_is_digit;
  size_t count = 0;
 public:
  TokenParser();
  ~TokenParser();

  // Set callback-function before parsing.
  void SetStartCallback(const std::function<void()> &);

  // Set callback-function after parsing.
  void SetEndCallback(const std::function<void()> &);

  // Set callback-function for number processing.
  void SetDigitTokenCallback(const std::function<void(const uint64_t)> &);

  // Set callback-function for string processing.
  void SetStringTokenCallback(const std::function<void(const std::string &)> &);

  void Parser(const std::string &str);

  std::string get_log_str(const size_t i) { return log_str[i]; }
  bool get_log_is_digit(const size_t i) { return log_is_digit[i]; }
  size_t get_count() { return count; }

 private:
  std::function<void()> StartCallback;
  std::function<void()> FinishCallback;
  std::function<void(uint64_t)> DigitTokenCallback;
  std::function<void(const std::string &)> StringTokenCallback;

  bool IsDigit(const std::string &str);
  uint64_t StrToInt(const std::string &str);
  void Type_of_token(const std::string &str);

};







