#pragma once
#include <vector>
#include <sstream>
#include <string>
#include <iostream>

class format_exc: public std::out_of_range{
private:
    std::string error;
public:
    explicit format_exc(const std::string& message) :
    std::out_of_range(message), error(message) {}

    const char* what() const noexcept override {
        return error.c_str();
    }
};

class inv_arg_exc: public std::invalid_argument{
private:
    std::string error;
public:
    explicit inv_arg_exc(const std::string& message) :
            std::invalid_argument(message), error(message) {}

    const char* what() const noexcept override {
        return error.c_str();
    }
};

template<class T>
std::string args_to_string(const T& temp) {
    std::stringstream in;
    in << temp;
    return in.str();
}

bool try_digit(std::string str) {
    for (uint64_t i = 0; i < str.size(); i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

template <class... Args>
std::string format(const std::string& str, const Args& ...args) {
    std::string result = "";
    std::vector<std::string> vect_args = {args_to_string(args)...};
    size_t len_str = str.size();
    size_t begin = std::string::npos;
    size_t current = 0;
    size_t end = std::string::npos;
    size_t number;
    std::string temp;

    std::stringstream new_str_format;

    while (current < len_str) {
        begin = str.find_first_of("{", current);
        end = str.find_first_of("}", current);
        if (begin > end) {
            throw format_exc("expected { before }");
        }
        if (end == std::string::npos && begin != std::string::npos) {
            throw format_exc("expected } after {");
        }
        if (begin  == std::string::npos && end == std::string::npos) {
            result += str;
            return result;
        }
        result += std::string(str.begin() + current, str.begin() + begin);
        temp = std::string(str.begin() + begin + 1, str.begin() + end);
      if (try_digit(temp) && temp != "")
        number = std::stoi(temp);
      else {
        throw inv_arg_exc("incorrect input");
      }
        if (number >= vect_args.size()) {
            throw inv_arg_exc("out of range args");
        }
        result += vect_args[number];
        current  = end + 1;
    }
    return result;
}
