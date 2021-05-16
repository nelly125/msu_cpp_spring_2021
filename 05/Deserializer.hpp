#pragma once
#include <iostream>
#include "Serializer.hpp"

class Deserializer {
  std::istream &in_;
 private:

  template<class T>
  Error process(T &&arg) {
    return get_arg(arg);
  }

  template<class T, class... ArgsT>
  Error process(T &&value, ArgsT &&... args) {
    Error err = get_arg(value);
    if (err == Error::CorruptedArchive) {
      return err;
    }
    return process(std::forward<ArgsT>(args)...);
  }

  Error get_arg(uint64_t &value);
  Error get_arg(bool &value);

  template<class T>
  Error get_arg(T) {
    return Error::CorruptedArchive;
  }

 public:
  explicit Deserializer(std::istream &in) : in_(in) {}

  template<class T>
  Error load(T &object) { return object.deserialize(*this); }

  template<class... ArgsT>
  Error operator()(ArgsT &&... args) { Error err =  process(args...); if (!in_.eof()) return Error::CorruptedArchive; return err; }

};



