//
// Created by nelly on 5/3/21.
//

#pragma once

#include "iterator.hpp"
#include "allocator.hpp"
#include <initializer_list>

template<typename T, class Alloc_T = Allocator<T>>
class Vector {
 public:
  using iterator = Iterator<T>;
  using reverse_iterator = class std::reverse_iterator<Iterator<T>>;
  using const_iterator = const Iterator<T>;

 private:
  size_t size_;
  size_t capacity_;
  Alloc_T allocator_;
  T *data_;

 public:
  Vector() : size_(0), capacity_(0), data_(allocator_.allocate(0)) {}
  ~Vector() {
    this->clear();
    size_ = 0;
    capacity_ = 0;
    allocator_.deallocate(data_);
  }
  Vector(std::initializer_list<T> &&list, const Alloc_T &alloc = Alloc_T());
  Vector(size_t size, const Alloc_T &alloc = Alloc_T());
  Vector(size_t size, const T &value, const Alloc_T &alloc = Alloc_T());

  Vector(const Vector &temp);
  Vector(Vector &&temp) noexcept;
  Vector &operator=(const Vector &temp);
  Vector &operator=(const Vector &&temp) noexcept;
  T &operator[](size_t i);
  const T &operator[](size_t i) const;

  void push_back(const T &temp);
  void push_back(T &&temp);
  void pop_back();

  template<class... Args>
  T &emplace_back(Args &&... args);

  bool empty();
  size_t capacity();
  size_t size() const;
  void reserve(size_t capacity);
  void resize(size_t new_size, const T &value = T());
  void clear();

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  reverse_iterator rbegin() noexcept;
  reverse_iterator rend() noexcept;

//  friend std::ostream& operator<< (std::ostream &out, const Vector<T, Alloc_T> &my_vector);
  template<typename... Args>
  void fill(typename Allocator<T>::pointer begin, typename Allocator<T>::pointer end, Args &&... args) {
    for (typename Allocator<T>::pointer cur = begin; cur != end; cur++) {
      allocator_.construct(cur, args...);
    }
  }

  constexpr bool operator==(const Vector<T, Alloc_T> &right);

};

template<typename T, class Alloc_T>
std::ostream &operator<<(std::ostream &out, const Vector<T, Alloc_T> &my_vector) {
  for (auto iter = my_vector.begin(); iter != my_vector.end(); ++iter)
    out << (iter == my_vector.begin() ? "" : " ") << *iter;
  return out;
}

#include "vector.tpp"
