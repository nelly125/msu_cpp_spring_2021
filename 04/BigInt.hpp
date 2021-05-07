#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <cmath>

class BigInt {
 private:
  const int BASE = 6; // x10^6
  const int den = pow(10, BASE); //1000000;
  int32_t *number;
  bool is_negative;
  int size;

  bool is_number(const std::string &str);
  void delete_initial_zeros(std::string &str);
  std::string add_zeros(int temp) const;
  friend std::ostream &operator<<(std::ostream &out, const BigInt &x);

 public:
  BigInt();
  BigInt(const std::string &str);
  BigInt(int num);
  BigInt(const BigInt &temp);

  BigInt(BigInt &&temp);
  ~BigInt();
  BigInt operator-() const;

  BigInt operator+(const BigInt &right) const;
  BigInt operator-(const BigInt &right) const;
  BigInt operator*(const BigInt &right) const;
  BigInt operator=(const BigInt &right);
  BigInt operator=(BigInt &&right);
  BigInt operator+(const int int_right) const;
  BigInt operator-(const int int_right) const;
  BigInt operator*(const int int_right) const;

  bool operator==(const BigInt &temp_number) const;
  bool operator!=(const BigInt &temp_number) const;
  bool operator>(const BigInt &temp_number) const;
  bool operator<(const BigInt &temp_number) const;
  bool operator>=(const BigInt &temp_number) const;
  bool operator<=(const BigInt &temp_number) const;

  BigInt abs();
  std::string number_to_str();
  bool is_empty() const { return (number == nullptr && !is_negative && size == 0); }
};