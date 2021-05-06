//
// Created by nelly on 5/3/21.
//

#pragma once

#include <iterator>

template<class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
 private:
  T *cur_pos;

 public:
  explicit Iterator(T *val) : cur_pos(val) {}
  bool operator==(const Iterator<T> &iter) const {
    return cur_pos == iter.cur_pos;
  };
  bool operator!=(const Iterator<T> &iter) const {
    return (cur_pos != iter.cur_pos);
  }
  bool operator>(const Iterator<T> &iter) const {
    return cur_pos > iter.cur_pos;
  }
  bool operator<(const Iterator<T> &iter) const {
    return cur_pos < iter.cur_pos;
  }
  bool operator>=(const Iterator<T> &iter) const {
    return cur_pos >= iter.cur_pos;
  }
  bool operator<=(const Iterator<T> &iter) const {
    return cur_pos <= iter.cur_pos;
  }
  Iterator &operator++() {
    cur_pos++;
    return *this;
  }
  Iterator &operator--() {
    cur_pos--;
    return *this;
  }

  Iterator &operator+(int shift) const {
    cur_pos += shift;
    return *this;
  }
  Iterator &operator-(int shift) const {
    cur_pos -= shift;
    return *this;
  }

  Iterator &operator+=(int shift) {
    cur_pos += shift;
    return *this;
  }
  Iterator &operator-=(int shift) {
    cur_pos -= shift;
    return *this;
  }
  T &operator*() {
    return *cur_pos;
  }
  const T &operator*() const {
    return *cur_pos;
  }
};



