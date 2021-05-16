#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

#include "Serializer.hpp"
#include "Deserializer.hpp"
#include "Different_structures_test.hpp"
//#include "Save_and_load_tests.hpp"

struct Data {
  uint64_t a;
  bool b;
  uint64_t c;

  template<class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a, b, c);
  }

  template<class Deserializer>
  Error deserialize(Deserializer &deserializer) {
    return deserializer(a, b, c);
  }
};


struct Data1 {
  uint64_t c;

  template<class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(c);
  }

  template<class Deserializer>
  Error deserialize(Deserializer &deserializer) {
    return deserializer(c);
  }
};

struct Data2 {
  bool c;

  template<class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(c);
  }

  template<class Deserializer>
  Error deserialize(Deserializer &deserializer) {
    return deserializer(c);
  }
};

struct Data3 {
  char c;

  template<class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(c);
  }

  template<class Deserializer>
  Error deserialize(Deserializer &deserializer) {
    return deserializer(c);
  }
};

void SaveTest() {
  Data x = {1, true, 2};

  std::stringstream stream;
  Serializer serializer(stream);

  assert(serializer.save(x) == Error::NoError);
  assert(stream.str() == "1 true 2");

  std::cout << "TEST_1 RESULT: SAVE TEST IS COMPLETED" << std::endl;
}

void LoadTest() {
  Data x;

  std::stringstream stream("1 true 2");
  Deserializer serializer(stream);

  assert(serializer.load(x) == Error::NoError);
  assert(x.a == 1);
  assert(x.b == true);
  assert(x.c == 2);

  std::cout << "TEST_2 RESULT: LOAD TEST IS COMPLETED" << std::endl;

}

void Save_Load_Tests() {
  Data x = {1, true, 2};
  Data y = {0, false, 0};

  std::stringstream stream;
  Serializer serializer(stream);

  Deserializer deserializer(stream);

  assert(serializer.save(x) == Error::NoError);
  assert(deserializer.load(y) == Error::NoError);
  assert(x.a == y.a);
  assert(x.b == y.b);
  assert(x.c == y.c);
  assert(x.a == 1);
  assert(x.b == true);
  assert(x.c == 2);

  std::cout << "TEST_3 RESULT: SAVE LOAD TEST IS COMPLETED" << std::endl;
}

void Incorrect_test() {
  {
    Data y;
    std::stringstream stream("-1 true 2");
    Deserializer serializer(stream);
    assert(serializer.load(y) == Error::CorruptedArchive);
  }
  {
    Data y;
    std::stringstream stream("");
    Deserializer serializer(stream);
    assert(serializer.load(y) == Error::CorruptedArchive);
  }

  {
    Data y;
    std::stringstream stream("1a");
    Deserializer serializer(stream);
    assert(serializer.load(y) == Error::CorruptedArchive);
  }

  {
    Data y;
    std::stringstream stream("1"); //недостаток аргуметов
    Deserializer serializer(stream);
    assert(serializer.load(y) == Error::CorruptedArchive);
  }

  {
    Data y;
    std::stringstream stream("1 true 3 4"); //переизбыток аргументов
    Deserializer serializer(stream);

    assert(serializer.load(y) == Error::CorruptedArchive);
  }


  {
    Data y;
    std::stringstream stream("1a true 3");
    Deserializer serializer(stream);
    assert(serializer.load(y) == Error::CorruptedArchive);
  }

  {
    Data y;
    std::stringstream stream("18446744073709551617 true 3"); //uint64 + 1
    Deserializer serializer(stream);
    assert(serializer.load(y) == Error::CorruptedArchive);
  }

  //type is not bool or uint64
  {
    Data3 x{'t'};

    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    assert(err1 == Error::CorruptedArchive);
    assert(x.c == 't');
  }

  {
    std::stringstream stream("a");
    Data3 y{'t'};
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::CorruptedArchive);

  }

  std::cout << "TEST_4 RESULT: INCORRECT TEST IS COMPLETED" << std::endl;
}

void unit_test() {
  {
    Data1 x{111};
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    Data1 y{555};
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::NoError);
    assert(x.c == y.c);
    assert(x.c == 111);
  }

  {
    Data2 x{true};
    std::stringstream stream;
    Serializer serializer(stream);
    const Error err1 = serializer.save(x);
    Data2 y{false};
    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err1 == Error::NoError);
    assert(err2 == Error::NoError);
    assert(x.c == y.c);
    assert(x.c == true);
  }

  {
    Data y;
    std::stringstream stream("18446744073709551615 true 3"); //uint64 -1
    Deserializer serializer(stream);
    assert(serializer.load(y) == Error::NoError);
  }

//double
  {
    Data1 y{555};
    std::stringstream stream("55.55");

    Deserializer deserializer(stream);
    const Error err2 = deserializer.load(y);
    assert(err2 == Error::CorruptedArchive);
    assert(y.c == 555);
  }
  std::cout << "TEST_5 RESULT: TEST WITH UNIT FIELD IS COMPLETED" << std::endl;

}

void Deserializer_without_serializer_test()
{
  Data x = {1, true, 2};

  std::stringstream stream;
  Deserializer deserializer(stream);

  assert(deserializer.load(x) == Error::CorruptedArchive);

  std::cout << "TEST_7 RESULT: TEST DESERIALIZER WITHOUT SERIALIZER IS COMPLETED" << std::endl;

}

void double_serializer_test()
{
  Data x = {1, true, 2};
  Data y = {0, false, 0};

  std::stringstream stream;
  Serializer serializer(stream);

  assert(serializer.save(x) == Error::NoError);
  assert(serializer.save(y) == Error::CorruptedArchive);

  std::cout << "TEST_8 RESULT: DOUBLE SERIALIZER TEST IS COMPLETED" << std::endl;

}


void double_deserializer_test()
{
  Data x = {1, true, 2};
  Data y = {0, false, 0};

  std::stringstream stream;
  Serializer serializer(stream);
  Deserializer deserializer(stream);


  assert(serializer.save(x) == Error::NoError);
  assert(deserializer.load(y) == Error::NoError);
  assert(deserializer.load(y) == Error::CorruptedArchive);


  std::cout << "TEST_9 RESULT: DOUBLE DESERIALIZER TEST IS COMPLETED" << std::endl;

}

int main() {

  SaveTest();
  LoadTest();
  Save_Load_Tests();
  Incorrect_test();
  unit_test();
  Different_structuresTest();
  Deserializer_without_serializer_test();
  double_serializer_test();
  double_deserializer_test();

//  test();

  return 0;
}
