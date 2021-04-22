#include "Deserializer.hpp"

Error Deserializer::get_arg(uint64_t &value) {
  if (in_.peek() == '-') {
    return Error::CorruptedArchive;
  }
  in_ >> value;
  return in_.fail() ? Error::CorruptedArchive : Error::NoError;
}

Error Deserializer::get_arg(bool &value) {
  std::string text;
  in_ >> text;
  if (text == "true") {
    value = true;
  } else if (text == "false") {
    value = false;
  } else {
    return Error::CorruptedArchive;
  }
  return in_.fail() ? Error::CorruptedArchive : Error::NoError;
}