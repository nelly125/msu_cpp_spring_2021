//
// Created by nelly on 3/27/21.
//

#pragma once

#include <functional>
#include <string>

class TokenParser
{
 public:
  TokenParser();
  ~TokenParser();
  // Устанавливаем callback-функцию перед стартом парсинга.
  void SetStartCallback(const std::function<void()> &);

  // Устанавливаем callback-функцию после окончания парсинга.
  void SetEndCallback(const std::function<void()> &);

  // Устанавливаем callback-функцию для обработки чисел.
  void SetDigitTokenCallback(const std::function<void(int64_t)> &);

  // Устанавливаем callback-функцию для обработки строк.
  void SetStringTokenCallback(const std::function<void(const std::string &)> &);

  void Parser(std::string& str);

 private:
  std::function<void()> StartCallback;
  std::function<void()> FinishCallback;
  std::function<void(uint64_t)> DigitTokenCallback;
  std::function<void(const std::string&)> StringTokenCallback;

  bool IsDigit(const std::string& str);
  uint64_t StrToInt(const std::string& str);
  void Type_of_token(const std::string& str);

};


