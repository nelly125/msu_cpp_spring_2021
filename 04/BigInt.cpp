#include "BigInt.hpp"

BigInt::BigInt() : number(nullptr), is_negative(false), size(0) {}

BigInt::~BigInt() {
  delete[] number;
}

BigInt::BigInt(const BigInt &temp) {
  BigInt new_number;
  size = temp.size;
  is_negative = temp.is_negative;
  number = new int[size];
  for (int i = size - 1; i >= 0; i--) {
    number[i] = temp.number[i];
  }
}

BigInt::BigInt(BigInt &&temp) {
  number = temp.number;
  is_negative = temp.is_negative;
  size = temp.size;
  temp.number = nullptr;
  temp.is_negative = false;
  temp.size = 0;
}

bool BigInt::is_number(const std::string &str) {
  if (str.empty() || (str.size() == 1 && str[0] == '-'))
    return false;
  int count = 0;
  for (char i : str) {
    if (count == 0 && !isdigit(i) && i != '-')
      return false;
    if (!isdigit(i) && count > 0)
      return false;
    count++;
  }
  return true;
}

BigInt::BigInt(const std::string &str) {
  std::string temp_str = str;
  if (!is_number(temp_str))
    throw std::invalid_argument("Bad value. Not a number");
  is_negative = false;
  if (temp_str[0] == '-') {
    temp_str = temp_str.substr(1);
    is_negative = true;
  }
  delete_initial_zeros(temp_str);

  if (temp_str.length()%(BASE) == 0)
    size = int(temp_str.length()/(BASE));
  else
    size = int(temp_str.length()/(BASE)) + 1;

  number = new int32_t[size];
  if (str[0] == 0 && temp_str.length() == 0)
    number[0] = 0;
  for (long long i = temp_str.length(), j = 0; i > 0; i -= BASE, j++) {
    if (i >= BASE) {
      number[j] = atoi(temp_str.substr(i - BASE, BASE).c_str());
    } else {
      std::string tmp = temp_str.substr(0, i);
      number[j] = atoi(tmp.c_str());
    }
  }
}

BigInt::BigInt(int num) {
  is_negative = false;
  if (num < 0) {
    is_negative = true;
    num = std::abs(num);
  }
  size = num/den + 1;
  number = new int[size];
  for (int i = 0; i < size; i++) {
    number[i] = num%den;
    num /= den;
  }
}

void BigInt::delete_initial_zeros(std::string &str) {
  str.erase(0, str.find_first_not_of('0'));
}

std::string BigInt::add_zeros(int temp) const {
  int count = 6 - std::to_string(temp).size();
  std::string s;
  for (int i = 0; i < count; i++)
    s += "0";
  s += std::to_string(temp);
  return s;
}

std::ostream &operator<<(std::ostream &out, const BigInt &x) {
  std::string temp;

  if (x.is_negative)
    out << "-";
  for (int i = x.size - 1; i >= 0; i--) {
    if (i != x.size - 1) {
      temp = x.add_zeros(x.number[i]);
      out << temp << ".";
    } else {
      out << x.number[i] << ".";
    }
  }
  out << std::endl;
  return out;
}

BigInt BigInt::operator+(/*const*/ BigInt &right) {
  if (right.is_negative && is_negative) { //-a + -b = - (a + b)
    BigInt temp_left(-*this);
    BigInt temp_right(-right);
    return -(temp_left + temp_right);
  } else if (!is_negative && right.is_negative) { //a + -b = a - b
    BigInt temp_right(-right);
    return *this - temp_right;
  } else if (is_negative && !right.is_negative) { //-a + b = b - a
    BigInt temp_left(-*this);
    return right - temp_left;
  }
  int shift = 0;
  int temp_size = std::max(size, right.size) + 1;
  int *temp = new int[temp_size];
  for (int i = 0; i < temp_size; i++)
    temp[i] = 0;
  int res;
  int i = 0;
  while (i < temp_size) {
    if (i >= size && i >= right.size)
      temp[i] = 0 + shift;
    else if (i >= size)
      temp[i] = right.number[i];
    else if (i >= right.size)
      temp[i] = number[i];
    else {
      res = number[i] + right.number[i] + shift;
      if (den <= res) {
        temp[i] = res - den;
        shift = 1;
      } else {
        temp[i] = res;
        shift = 0;
      }
    }
    i++;
  }

  for (int i = temp_size - 1; i >= 0 && temp_size != 1; i--) {
    if (temp[i] == 0)
      temp_size--;
    else
      break;
  }

  BigInt result;
  result.size = temp_size;
  result.number = new int[result.size];
  for (i = 0; i < result.size; i++)
    result.number[i] = temp[i];
  delete[] temp;
  return result;
}

BigInt BigInt::operator-(BigInt &right) {
  if (right.is_negative && is_negative) { //-a - -b = - (a - b) -5 - -7 = -5 + 7 =  - (-7 +  - 5)
    BigInt temp_left(-*this);
    BigInt temp_right(-right);
    return -(temp_left - temp_right);
  } else if (!is_negative && right.is_negative) { //a - -b = a + b
    BigInt temp(-right);
    return *this + temp;
  } else if (is_negative && !right.is_negative) { //-a - b = - ( a+ b)
    BigInt temp(-*this);
    return -(temp + right);
  }

  bool sgn = false;
  if ((*this).abs() < right.abs()) {
    return -(right - *this);
  }

  int shift = 0;
  int temp_size = std::max(size, right.size);
  int *temp = new int[temp_size];
  for (int i = 0; i < temp_size; i++)
    temp[i] = 0;
  int res;
  int i = 0;
  while (i < temp_size) {
    if (i >= right.size) {
      res = shift;
      if (number[i] < res) {
        temp[i] = den + number[i] - res;
        shift = 1;
      } else {
        temp[i] = number[i] - res;
        shift = 0;
      }
    } else {
      res = right.number[i] + shift;
      if (number[i] < res) {
        temp[i] = den + number[i] - res;
        shift = 1;
      } else {
        temp[i] = number[i] - res;
        shift = 0;
      }
    }
    i++;
  }
  for (int i = temp_size - 1; i >= 0 && temp_size != 1; i--) {
    if (temp[i] == 0)
      temp_size--;
    else
      break;
  }

  BigInt result;
  result.size = temp_size;
  result.number = new int[result.size];
  result.is_negative = false;
  if (sgn)
    result.is_negative = true;
  for (int i = 0; i < result.size; i++)
    result.number[i] = temp[i];
  delete[] temp;
  return result;
}

BigInt BigInt::operator*(const BigInt &right) {
  int shift;
  int temp_size = size + right.size;
  int *temp = new int[temp_size];
  for (int i = 0; i < temp_size; i++)
    temp[i] = 0;
  long long int res;
  for (int i = 0; i < size; i++) {
    shift = 0;
    for (int j = 0; j < right.size; j++) {
      res = temp[i + j] + number[i]*1LL*(j < right.size ? right.number[j] : 0) + shift;
      temp[i + j] = static_cast<int>(res%den);
      shift = static_cast<int>(res/den);
    }
  }
  for (int i = temp_size - 1; i >= 0 && temp_size != 1; i--) {
    if (temp[i] == 0)
      temp_size--;
    else
      break;
  }

  BigInt result;
  result.size = temp_size;
  result.number = new int[result.size];
  for (int i = 0; i < result.size; i++)
    result.number[i] = temp[i];
  result.is_negative = false;

  if (is_negative && right.is_negative)
    result.is_negative = false;
  else if (is_negative || right.is_negative)
    result.is_negative = true;
  delete[] temp;
  return result;
}

BigInt BigInt::operator-() const {
  BigInt result(*this);
  if (result.is_negative)
    result.is_negative = false;
  else
    result.is_negative = true;
  return result;
}

BigInt BigInt::operator+(int int_right) {
  BigInt right(int_right);
  return *this + right;
}
BigInt BigInt::operator-(int int_right) {
  BigInt right(int_right);
  return *this - right;

}
BigInt BigInt::operator*(int int_right) {
  BigInt right(int_right);
  return (*this)*right;
}

BigInt BigInt::operator=(const BigInt &temp_number) {
  if (this == &temp_number)
    return *this;
  if (number != nullptr)
    delete[] number;
  is_negative = temp_number.is_negative;
  size = temp_number.size;
  number = new int[size];
  for (int i = 0; i < size; i++)
    number[i] = temp_number.number[i];
  return *this;
}

BigInt BigInt::abs() {
  if (is_negative)
    is_negative = false;
  return *this;
}

std::string BigInt::number_to_str() {
  std::string s;
  std::string temp;

  if (is_negative)
    s += '-';
  for (int i = size - 1; i >= 0; i--) {
    if (i != size - 1) {
      temp = add_zeros(number[i]);
      s += temp;
    } else {
      s += std::to_string(number[i]);
    }
  }
  return s;
}

bool BigInt::operator==(const BigInt &temp_number) {
  if (this->size != temp_number.size)
    return false;
  if (this->is_negative != temp_number.is_negative)
    return false;
  for (int i = 0; i < size; i++)
    if (number[i] != temp_number.number[i])
      return false;
  return true;
}

bool BigInt::operator!=(const BigInt &temp_number) {
  if (this->size != temp_number.size)
    return true;
  if (this->is_negative != temp_number.is_negative)
    return true;
  for (int i = 0; i < size; i++)
    if (number[i] == temp_number.number[i])
      return false;
  return true;
}

bool BigInt::operator<(const BigInt &temp_number) {
  if (*this == temp_number)
    return false;
  if (this->is_negative && !temp_number.is_negative)
    return true;
  else if (!this->is_negative && temp_number.is_negative)
    return false;
  if (this->size > temp_number.size)
    return false;
  if (!this->is_negative && !temp_number.is_negative) {
    for (int i = size - 1; i >= 0; i--)
      if (number[i] >= temp_number.number[i]) {
        return false;
      }
  } else {
    for (int i = size - 1; i >= 0; i--)
      if (number[i] <= temp_number.number[i]) {
        return false;
      }
  }
  return true;
}

bool BigInt::operator>(const BigInt &temp_number) {
  bool flag = -(*this) < -temp_number;
  return flag;
}

bool BigInt::operator<=(const BigInt &temp_number) {
  if (*this == temp_number)
    return true;
  if (this->is_negative && !temp_number.is_negative)
    return true;
  else if (!this->is_negative && temp_number.is_negative)
    return false;
  if (this->size > temp_number.size)
    return false;
  if (!this->is_negative && !temp_number.is_negative) {
    for (int i = size - 1; i >= 0; i--)
      if (number[i] > temp_number.number[i]) {
        return false;
      }
  } else {
    for (int i = size - 1; i >= 0; i--)
      if (number[i] < temp_number.number[i]) {
        return false;
      }
  }
  return true;
}

bool BigInt::operator>=(const BigInt &temp_number) {
  bool flag = -(*this) <= -temp_number;
  return flag;
}