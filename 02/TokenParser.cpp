//
// Created by nelly on 3/27/21.
//

#include <iostream>
#include "TokenParser.hpp"

TokenParser::TokenParser():
	StartCallback(nullptr),
	FinishCallback(nullptr),
	DigitTokenCallback(nullptr),
	StringTokenCallback(nullptr){}

TokenParser::~TokenParser() = default;

void TokenParser::SetStartCallback(const std::function<void()> &start_callback){
  StartCallback = start_callback;
}

void TokenParser::SetEndCallback(const std::function<void()> &finish_callback){
  FinishCallback = finish_callback;
}

void TokenParser::SetDigitTokenCallback(const std::function<void (const uint64_t)> &digit_callback){
  DigitTokenCallback = digit_callback;
}

void TokenParser::SetStringTokenCallback(const std::function<void (const std::string &)> &string_callback){
  StringTokenCallback = string_callback;
}

bool TokenParser::IsDigit(const std::string& str){
  for (size_t i = 0; i < str.size(); i++){
	if (! isdigit(str[i]))
	  return false;
  }
  return true;
}

uint64_t TokenParser::StrToInt(const std::string& str){
  uint64_t a;
  char* end;
  a= strtoull( str.c_str(), &end,10 );
  return a;
}

void TokenParser::Type_of_token(const std::string& temp_token) {
  if (IsDigit(temp_token)) {
	uint64_t digit = StrToInt(temp_token);
	if (DigitTokenCallback != nullptr)
	  DigitTokenCallback(digit);
  }
  else {
	if (StringTokenCallback != nullptr)
	  StringTokenCallback(temp_token);
  };
}

void TokenParser::Parser(const std::string& str)
{
  if (StartCallback != nullptr)
	StartCallback();
  std::string token;
  std::string delimiter = " \t\n";

  size_t pos,  begin = 0;

  pos = str.find_first_of(delimiter);


  while (pos != std::string::npos) {
    if (begin == pos) {
	  begin = pos + 1;
//	  std::cout << "delete" << pos  << str << std::endl;
    }
    else {
	  token = str.substr(begin, pos - begin);
	  begin = pos + 1;
	  Type_of_token(token);
//	  std::cout << "find " << token << std::endl;
	}
	pos = str.find_first_of(delimiter, begin);
  }
  token = str.substr(begin, pos - begin);
//  std::cout << "find " << token << std::endl;

  Type_of_token(token);

  if (FinishCallback != nullptr)
    FinishCallback();
}


