#pragma once
#include <iostream>
#include <utility>

enum class Error {
  NoError,
  CorruptedArchive
};

class Serializer {
  static constexpr char Separator = ' ';
 private:
  std::ostream &out_;
  bool flag = false;

  template<class T>
  Error process(T &&arg) { return create_str(arg); }

  template<class T, class... ArgsT>
  Error process(T &&object, ArgsT &&... args) {
    Error err = create_str(object);
    if (err != Error::NoError) {
      return err;
    }
    out_ << Separator;
    return process(std::forward<ArgsT>(args)...);
  }

  Error create_str(uint64_t value);
  Error create_str(bool value);

  template<class T>
  Error create_str(T) { return Error::CorruptedArchive; }

 public:
  explicit Serializer(std::ostream &out) : out_(out) {}

  template<class T>
  Error save(T &object) { return object.serialize(*this); }

  template<class... ArgsT>
  Error operator()(ArgsT &&... args) {
    if (flag) {
      return Error::CorruptedArchive;
    } else {
      flag = true;
      return process(args...);
    }
  }
};


