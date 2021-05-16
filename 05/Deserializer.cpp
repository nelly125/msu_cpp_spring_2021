#include "Deserializer.hpp"
#include <cmath>

Error Deserializer::get_arg(uint64_t &value) {
  if (in_.peek() == '-') {
    return Error::CorruptedArchive;
  }
  std::string temp;
  in_ >> temp;

  if (temp == "") {
    return Error::CorruptedArchive;
  }

  for (size_t i = 0; i < temp.size(); i++)
    if (!std::isdigit(temp[i]))
      return Error::CorruptedArchive;

  try {
    value = std::stoull(temp);
  } catch (std::out_of_range &r) {
    return Error::CorruptedArchive;
  }

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