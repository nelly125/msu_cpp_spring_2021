//
// Created by nelly on 5/3/21.
//
template<typename T, class Alloc_T>
Vector<T, Alloc_T>::Vector(const Vector &temp){
  size_ = temp.size_;
  capacity_ = temp.capacity_;
  data_ = allocator_.allocate(temp.capacity_);
  std::cout << temp.size_ << std::endl;
  for (size_t i = 0; i < temp.size_; i++) {
    allocator_.construct(data_+ i, temp[i]);
  }
}

template<typename T, class Alloc_T>
Vector<T, Alloc_T>::Vector(Vector &&temp) noexcept {
  size_ = temp.size_;
  capacity_ = temp.capacity_;
  data_ = temp.data_;
  temp.size_ = 0;
  temp.capacity_ = 0;
  temp.data_ = nullptr;
}

template<typename T, class Alloc_T>
Vector<T, Alloc_T>::Vector(std::initializer_list<T> &&list, const Alloc_T &alloc) :
    size_(list.size()),
    capacity_(list.size()),
    allocator_(alloc) {
  data_ = allocator_.allocate(capacity_);
//  std::cout << capacity_ << std::endl;
  size_t i = 0;
  for (auto value: list) {
    allocator_.construct(data_ + i++, std::move(value));
  }
}

template<typename T, class Alloc_T>
Vector<T, Alloc_T>::Vector(size_t size, const Alloc_T &alloc) :
    size_(0),
    capacity_(size),
    allocator_(alloc) {
  data_ = allocator_.allocate(capacity_);
  fill(data_, data_ + size);
}

template<typename T, class Alloc_T>
Vector<T, Alloc_T>::Vector(size_t size, const T &value, const Alloc_T &alloc) :
    size_(size),
    capacity_(size),
    allocator_(alloc) {
  data_ = allocator_.allocate(capacity_);

  for (size_t i = 0; i < size_; i++) {
    allocator_.construct(data_+ i, value);
  }
}

template<typename T, class Alloc_T>
Vector<T, Alloc_T> &Vector<T, Alloc_T>::operator=(const Vector &temp) {
  if (temp.size_ <= capacity_) {
    std::copy(temp.data_, temp.data_ + temp.size_, data_);
    size_ = temp.size_;
  } else {
    Vector tmp(temp);
    std::swap(tmp.data_, data_);
    std::swap(tmp.capacity_, capacity_);
    std::swap(tmp.size_, size_);
  }
  return *this;
}

template<typename T, class Alloc_T>
Vector<T, Alloc_T> &Vector<T, Alloc_T>::operator=(const Vector &&temp) noexcept {
  if (temp.size_ <= capacity_) {
    std::copy(temp.data_, temp.data_ + temp.size_, data_);
    size_ = temp.size_;
  } else {
    Vector tmp(temp);
    std::swap(tmp.data_, data_);
    std::swap(tmp.capacity_, capacity_);
    std::swap(tmp.size_, size_);
  }
  return *this;
}

template<typename T, class Alloc_T>
T &Vector<T, Alloc_T>::operator[](size_t i) {
  if (i < size_)
    return data_[i];
  else
    throw std::out_of_range("out of range");
}

template<typename T, class Alloc_T>
const T &Vector<T, Alloc_T>::operator[](size_t i) const {
  if (i < size_)
    return data_[i];
  else
    throw std::out_of_range("out of range");
}

template<typename T, class Alloc_T>
void Vector<T, Alloc_T>::push_back(const T &temp) {
  if (size_ == capacity_)
    reserve(capacity_ ? capacity_*2 : 1);
  allocator_.construct(data_ + size_, std::move(temp));
  size_++;
}
template<typename T, class Alloc_T>
void Vector<T, Alloc_T>::push_back(T &&temp) {
  if (size_ == capacity_)
    reserve(capacity_ ? capacity_*2 : 1);
  allocator_.construct(data_ + size_, std::move(temp));
  size_++;
}

template<typename T, class Alloc_T>
void Vector<T, Alloc_T>::pop_back() {
  if (size_ > 0) {
    allocator_.destroy(data_ + size_);
    size_--;
  }
}
template<typename T, class Alloc_T>
template<class... Args>
T& Vector<T, Alloc_T>::emplace_back(Args &&... args) {
  if (size_ == capacity_)
    reserve(capacity_ ? capacity_ * 2 : 1);
//  allocator_.destroy(data_ + size_);
//  allocator_.construct(data_ + size_, T(std::forward<Args>(args)...));
//  size_++;
//  return *data_;

  auto elem = new (data_ + size_) T(std::move(args)...);
  ++size_;
  return *elem;
}
template<typename T, class Alloc_T>
bool Vector<T, Alloc_T>::empty() {
  return (size_ == 0);
}

template<typename T, class Alloc_T>
size_t Vector<T, Alloc_T>::capacity() {
  return capacity_;
}

template<typename T, class Alloc_T>
size_t Vector<T, Alloc_T>::size() const {
  return size_;
}

template<typename T, class Alloc_T>
void Vector<T, Alloc_T>::resize(size_t new_size, const T &value) {
/*  if (new_size > size_) {
    if (new_size > capacity_)
      allocator_.reserve(new_size);
    for (T *i = size_ + 1; i < new_size; i++)
      allocator_.construct(std::move(i));
  }
  if (new_size < size_) {
    for (T *i = data_ + size_; i > data_ + new_size; i--)
      allocator_.destroy(i);
  }
  size_ = new_size;*/
  if (capacity_ < new_size) {
    reserve(new_size);
    fill(data_ + size_, data_ + size_, value);
//    std::cout  << value;
  }
  size_ = new_size;
/*  if (size_ < new_size)
    size_ = new_size;
  else {
    size_t old_size_ = size_;

    if (new_size > capacity_) {
      capacity_ = capacity_ ? 2 * new_size : 1;
      Vector<T, Alloc_T> new_vector(capacity_);
      std::move(begin(), end(), new_vector.begin());
      this -> ~ Vector();
      *this = std::move(new_vector);
    }
    size_ = new_size;
    std::fill(begin() + old_size_, begin() + size_, value);
  }*/

}

template<typename T, class Alloc_T>
void Vector<T, Alloc_T>::reserve(size_t capacity) {
  if (capacity > capacity_) {
    T *new_dat = allocator_.allocate(capacity);
    for (size_t i = 0; i < size_; i++) {
      allocator_.construct(new_dat + i, std::move(data_[i]));
      allocator_.destroy(data_ + i);
    }
    allocator_.deallocate(data_);
    data_ = new_dat;
    capacity_ = capacity;
  }

}

template<typename T, class Alloc_T>
void Vector<T, Alloc_T>::clear() {
  for (size_t i = 0; i < size_; i++)
    allocator_.destroy(data_ + i);
  size_ = 0;
}

template<typename T, class Alloc_T>
typename Vector<T, Alloc_T>::iterator Vector<T, Alloc_T>::begin() noexcept {
  return iterator(data_);
}

template<typename T, class Alloc_T>
typename Vector<T, Alloc_T>::const_iterator Vector<T, Alloc_T>::begin() const noexcept {
  return iterator(data_);
}

template<typename T, class Alloc_T>
typename Vector<T, Alloc_T>::iterator Vector<T, Alloc_T>::end() noexcept {
  return iterator(data_ + size_);
}

template<typename T, class Alloc_T>
typename Vector<T, Alloc_T>::const_iterator Vector<T, Alloc_T>::end() const noexcept {
  return iterator(data_ + size_);
}

template<typename T, class Alloc_T>
typename Vector<T, Alloc_T>::reverse_iterator Vector<T, Alloc_T>::rbegin() noexcept {
  return reverse_iterator(end());
}

template<typename T, class Alloc_T>
typename Vector<T, Alloc_T>::reverse_iterator Vector<T, Alloc_T>::rend() noexcept {
  return reverse_iterator(begin());
}

template<typename T, class Alloc_T>
constexpr bool Vector<T, Alloc_T>::operator==(const Vector<T, Alloc_T> & right) {
  if (size_ != right.size_)
    return false;
  for (size_t i = 0; i < size_; i++) {
    if (data_[i] != right.data_[i])
      return false;
  }
  return true;
}

template<typename T>
bool operator==(const std::vector<T> &left, const Vector<T> &right) {
  if (left.size() != right.size()) {
    return false;
  }
  for (size_t i = 0; i < left.size(); ++i) {
    if (left[i] != right[i]) {
      return false;
    }
  }
  return true;
}



