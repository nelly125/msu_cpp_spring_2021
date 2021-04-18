#include "tests.hpp"

void delete_initial_zeros(std::string &str) {
  std::string temp_str = str.substr(1);
  temp_str.erase(0, temp_str.find_first_not_of('0'));
  if (str[0] == '-')
    str = '-' + temp_str;
  else
    str = temp_str;
}

void test_input() {
  std::string s1 = "-012345678912345671";
  std::string s2 = s1;
  BigInt big_int_1(s1);
  std::string check_s1 = big_int_1.number_to_str();
  delete_initial_zeros(s2);
  assert(check_s1 == s2);

  s1 = "012345678912345671";
  s2 = s1;
  delete_initial_zeros(s2);
  BigInt big_int_2(s1);
  std::string check_s2 = big_int_2.number_to_str();
  assert(check_s2 == s2);

  s1 = "";
  try {
    BigInt big_int_3(s1);
  }
  catch (const std::invalid_argument &err) {
    std::cout << "Exception: " << err.what() << std::endl;
  }

  s1 = "0ghj12345678912345671";
  try {
    BigInt big_int_3(s1);
  }
  catch (const std::invalid_argument &err) {
    std::cout << "Exception: " << err.what() << std::endl;
  }

  s1 = "--123";
  try {
    BigInt big_int_3(s1);
  }
  catch (const std::invalid_argument &err) {
    std::cout << "Exception: " << err.what() << std::endl;
  }
  try {
    BigInt big_int_3(1234567);
  }
  catch (const std::invalid_argument &err) {
    std::cout << "Exception: " << err.what() << std::endl;
  }

  BigInt a1("100");
  BigInt a2 = std::move(a1);
  assert(a1.is_empty() == true);
  assert(a2 == 100);

  BigInt big_int_4("100000000000000000000000000000000000000000000000000000000000000000000000000");
  assert(big_int_4.number_to_str() == "100000000000000000000000000000000000000000000000000000000000000000000000000");

  std::cout << "TEST_1 RESULT: INPUT TEST IS COMPLETED" << std::endl;
}

void test_equality() {
  std::string s1 = "-012345678912345671";
  BigInt big_int_1(s1);
  BigInt big_int_2(-1234567);
  BigInt big_int_3(big_int_2);
  bool res;
  res = big_int_2 == big_int_3;
  assert(res == true);
  res = (-big_int_2) == big_int_3;
  assert(res == false);
  res = big_int_1 == big_int_3;
  assert(res == false);
  BigInt big_int_4;
  res = big_int_1 == big_int_4;
  assert(res == false);

  std::cout << "TEST_2 RESULT: EQUALITY TEST IS COMPLETED" << std::endl;
}

void test_compare() {
  /* < */

  bool res;
  //negative < positive
  std::string s1 = "-123456789";
  BigInt big_int_1(s1);
  BigInt big_int_2(123456);
  res = big_int_1 < big_int_2;
  assert(res == true);
  //0 < negative
  std::string s3 = "0";
  std::string s4 = "-123456789";
  BigInt big_int_3(s3);
  BigInt big_int_4(s4);
  res = big_int_3 < big_int_4;
  assert(res == false);
  //equal < equal
  std::string s5 = "123456789123456789";
  std::string s6 = "123456789123456789";
  BigInt big_int_5(s5);
  BigInt big_int_6(s6);
  res = big_int_5 < big_int_6;
  assert(res == false);
  //positive < positive
  std::string s7 = "12345";
  std::string s8 = "123456";
  BigInt big_int_7(s7);
  BigInt big_int_8(s8);
  res = big_int_7 < big_int_8;
  assert(res == true);
  //negative < negative
  res = -(big_int_7) < -(big_int_8);
  assert(res == false);

  /* > */

  //negative > positive
  res = big_int_1 > big_int_2;
  assert(res == false);
  //0 > negative
  res = big_int_3 > big_int_4;
  assert(res == true);
  //equal > equal
  res = big_int_5 > big_int_6;
  assert(res == false);
  //positive > positive
  res = big_int_7 > big_int_8;
  assert(res == false);
  //negative > negative
  res = -(big_int_7) > -(big_int_8);
  assert(res == true);

  /* <= */

  //negative >= positive
  res = big_int_1 <= big_int_2;
  assert(res == true);
  //0 <= negative
  res = big_int_3 <= big_int_4;
  assert(res == false);
  //equal <= equal
  res = big_int_5 <= big_int_6;
  assert(res == true);
  //positive <= positive
  res = big_int_7 <= big_int_8;
  assert(res == true);
  //negative <= negative
  res = -(big_int_7) <= -(big_int_8);
  assert(res == false);

  /* >= */

  //negative >= positive
  res = big_int_1 >= big_int_2;
  assert(res == false);
  //0 >= negative
  res = big_int_3 >= big_int_4;
  assert(res == true);
  //equal >= equal
  res = big_int_5 >= big_int_6;
  assert(res == true);
  //positive >= positive
  res = big_int_7 >= big_int_8;
  assert(res == false);
  //negative >= negative
  res = -(big_int_7) >= -(big_int_8);
  assert(res == true);

  std::cout << "TEST_3 RESULT: COMPARE TEST IS COMPLETED" << std::endl;
}

void operator_equal() {
  std::string s1 = "-123456789";
  BigInt big_int_1(s1);
  BigInt big_int_2(123456);
  BigInt big_int_3;
  big_int_3 = big_int_1;
  std::string check_s1 = big_int_1.number_to_str();
  std::string check_s2 = big_int_1.number_to_str();
  assert(check_s1 == check_s2);

  std::string s2 = "123456789123456789";
  BigInt big_int_4(s2);
  big_int_3 = big_int_1;
  check_s1 = big_int_1.number_to_str();
  check_s2 = big_int_1.number_to_str();
  assert(check_s1 == check_s2);

  std::cout << "TEST_4 RESULT: OPERATOR EQUALITY TEST IS COMPLETED" << std::endl;

}

void test_addition() {
  BigInt big_int_1("11111111111111111111111111"); //pos + pos
  BigInt big_int_2("99999999999999999999999999");
  BigInt big_int_3;
  big_int_3 = big_int_1 + big_int_2;
  assert(big_int_3.number_to_str() == "111111111111111111111111110");

  {
    BigInt big_int_1("0");
    BigInt big_int_2("555555555555555555555");
    BigInt big_int_3;
    big_int_3 = big_int_1 + big_int_2;
    assert(big_int_3.number_to_str() == "555555555555555555555");
  }

  BigInt big_int_4("123456789123456789123456789");
  BigInt big_int_5("-123456789123456789123456789");
  BigInt big_int_6;
  big_int_6 = big_int_4 + big_int_5;
  assert(big_int_6 == 0);

  BigInt big_int_7("100000000000000000000");
  BigInt big_int_8("-1");
  BigInt big_int_9;
  big_int_9 = big_int_7 + big_int_8;
  assert(big_int_9.number_to_str() == "99999999999999999999");

  BigInt big_int_10("100000000000000000000000000000"); //pos + pos
  BigInt big_int_11("999999999999999999999999999999");
  BigInt big_int_12;
  big_int_12 = big_int_10 + big_int_11;
  assert(big_int_12.number_to_str() == "1099999999999999999999999999999");

  BigInt big_int_13("111111111111111111111");
  int x = 1;
  BigInt big_int_14 = big_int_13 + x;
  assert(big_int_14.number_to_str() == "111111111111111111112");

  std::cout << "TEST_5 RESULT: ADDITION TEST IS COMPLETED" << std::endl;
}

void test_subtraction() {
  BigInt big_int_1("11111111111111111111111111"); // pos - pos
  BigInt big_int_2("111111");
  BigInt big_int_3;
  big_int_3 = big_int_1 - big_int_2;
  assert(big_int_3.number_to_str() == "11111111111111111111000000");

  BigInt big_int_4("11111111111111111111111111"); //pos - neg
  BigInt big_int_5("-111111");
  BigInt big_int_6;
  big_int_6 = big_int_4 - big_int_5;
  assert(big_int_6.number_to_str() == "11111111111111111111222222");

  BigInt big_int_7("-500000000000000"); //neg - neg
  BigInt big_int_8("-1");
  BigInt big_int_9;
  big_int_9 = big_int_7 - big_int_8;
  assert(big_int_9.number_to_str() == "-499999999999999");

  BigInt big_int_10("-100000000000000000000000"); //neg - pos
  BigInt big_int_11("1");
  BigInt big_int_12;
  big_int_12 = big_int_10 - big_int_11;
  assert(big_int_12.number_to_str() == "-100000000000000000000001");

  BigInt big_int_13("111111111111111111111");
  int x = 1;
  BigInt big_int_14 = big_int_13 - x;
  assert(big_int_14.number_to_str() == "111111111111111111110");

  std::cout << "TEST_6 RESULT: SUBTRACTION TEST IS COMPLETED" << std::endl;

}

void test_multiplication() {
  BigInt big_int_1("-10000000000000001");
  BigInt big_int_2("22222222222222222222222");
  BigInt big_int_3;
  big_int_3 = big_int_1*big_int_2;
  assert(big_int_3.number_to_str() == "-222222222222244444442222222222222222");

  BigInt big_int_4("0");
  BigInt big_int_5("5");
  BigInt big_int_6 = big_int_4*big_int_5;
  assert(big_int_6 == 0);

  for (size_t i = 12345678; i < 10000000*10; i += 500000) {
    for (size_t j = 12345678; j < 10000000*10; j += 500000) {
      BigInt big_int_7(i);
      BigInt big_int_8(j);
      assert((big_int_7*big_int_8).number_to_str() == std::to_string(i*j));
    }
  }

  std::cout << "TEST_7 RESULT: MULTIPLICATION TEST IS COMPLETED" << std::endl;
}
