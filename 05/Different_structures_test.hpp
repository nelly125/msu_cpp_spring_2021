#pragma once

struct Data_diff_str_x
{
  bool a;
  bool b;
  uint64_t c;
  bool d;
  uint64_t e;

  template <class Serializer>
  Error serialize(Serializer& serializer)
  {
    return serializer(a, b, c, d, e);
  }

  template <class Deserializer>
  Error deserialize(Deserializer& deserializer)
  {
    return deserializer(a, b, c, d, e);
  }
};

struct Data_diff_str_y {
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

void Different_structuresTest()
{
  Data_diff_str_x x {false, true, 123, true, 90};
  Data_diff_str_y y = {0, false, 0};

  std::stringstream stream;
  Serializer serializer(stream);
  Deserializer deserializer(stream);

  assert(serializer.save(x)   == Error::NoError);
  assert(deserializer.load(y) == Error::CorruptedArchive);

  std::cout << "TEST_6 RESULT: DIFFERENT STRUCTURES TEST IS COMPLETED" << std::endl;

}
