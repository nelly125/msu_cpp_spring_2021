#include "Serializer.hpp"

Error Serializer::create_str(uint64_t value) {
  out_ << value;
  return Error::NoError;
}

Error Serializer::create_str(bool value) {
  out_ << (value ? "true" : "false");
  return Error::NoError;
}

