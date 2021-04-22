#include <iostream>
#include "Serializer.hpp"
#include "Deserializer.hpp"
#include <cassert>
#include <string>
#include <sstream>

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

void SaveTest() {
  Data x = {1, true, 2};

  std::stringstream stream;
  Serializer serializer(stream);
  Error status = serializer.save(x);
  assert(status == Error::NoError);
  assert(stream.str() == "1 true 2");

  std::cout << "TEST_1 RESULT: SAVE TEST IS COMPLETED" << std::endl;
}

void LoadTest() {
  Data x;

  std::stringstream stream("1 true 2");
  Deserializer serializer(stream);
  Error status = serializer.load(x);
  assert(status == Error::NoError);
  assert(x.a == 1);
  assert(x.b == true);
  assert(x.c == 2);

  std::cout << "TEST_2 RESULT: LOAD TEST IS COMPLETED" << std::endl;

}

void Save_Load_Tests() {
  Data x = {1, true, 2};
  std::stringstream stream;
  Serializer serializer(stream);
  serializer.save(x);

  Data y = {0, false, 0};
  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);

  assert(err == Error::NoError);
  assert(x.a == y.a);
  assert(x.b == y.b);
  assert(x.c == y.c);

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
    std::stringstream stream("1a true 3");
    Deserializer serializer(stream);
    assert(serializer.load(y) == Error::CorruptedArchive);
  }

  {
    Data y;
    std::stringstream stream("18446744073709551616 true 3"); //ulong + 1
    Deserializer serializer(stream);
    assert(serializer.load(y) == Error::CorruptedArchive);
  }
  std::cout << "TEST_4 RESULT: INCORRECT TEST IS COMPLETED" << std::endl;
}

int main() {

  SaveTest();
  LoadTest();
  Save_Load_Tests();
  Incorrect_test();

  return 0;
}
