#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace s21 {
template <class T, size_t SIZE>
class array {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

  class ConstIterator {
   public:
    T* data;
    ConstIterator() { this->data = nullptr; }
    ConstIterator(T* data) { this->data = data; }
    ConstIterator(const ConstIterator& other) : data(other.data) {}
    ~ConstIterator() {}

    ConstIterator operator++(int) {
      if (data != NULL) {
        data++;
      } else {
        throw out_of_range("array index out of range.");
      }
      return *this;
    }

    ConstIterator operator--(int) {
      if (data != NULL) {
        data--;
      } else {
        throw out_of_range("array index out of range.");
      }
      return *this;
    }

    const_reference operator*() const {
      if (data == NULL) {
        throw out_of_range("Empty iterator");
      }
      return *data;
    }

    bool operator!=(const ConstIterator& other) const {
      return data != other.data;
    }

    bool operator==(const ConstIterator& other) const {
      return data == other.data;
    }
  };
  class Iterator {
   public:
    T* data;
    Iterator() { this->data = nullptr; }
    Iterator(T* data) { this->data = data; }
    Iterator(const Iterator& other) : data(other.data) {}
    ~Iterator() {}

    Iterator operator++(int) {
      if (data != NULL) {
        data++;
      } else {
        throw out_of_range("array index out of range.");
      }
      return *this;
    }

    Iterator operator--(int) {
      if (data != NULL) {
        data--;
      } else {
        throw out_of_range("array index out of range.");
      }
      return *this;
    }

    const_reference operator*() const {
      if (data == NULL) {
        throw out_of_range("Empty iterator");
      }
      return *data;
    }

    bool operator!=(const Iterator& other) const { return data != other.data; }

    bool operator==(const Iterator& other) const { return data == other.data; }
  };
  typedef Iterator iterator;
  typedef ConstIterator const_iterator;

  //-------------------------------------------------------------------
  array() {
    m_size_ = SIZE;
    m_capacity_ = SIZE;
    arr_ = new T[SIZE];
  }

  array(std::initializer_list<value_type> const& items) {
    if (items.size() > SIZE) {
      throw out_of_range("array index out of range.");
    }
    m_size_ = SIZE;
    m_capacity_ = SIZE;
    arr_ = new T[SIZE];
    const value_type* item = items.begin();
    for (std::initializer_list<int>::size_type i = 0; i < items.size(); i++) {
      at(i) = (*(item + i));
    }
  }

  array(const array& l) {
    m_size_ = l.m_size_;
    m_capacity_ = l.m_capacity_;
    arr_ = new T[m_capacity_];
    for (size_type i = 0; i < l.size(); i++) {
      at(i) = (l.arr_[i]);
    }
  }

  array(array&& l) {
    if (this == &l) {
      throw std::invalid_argument("Error move!");
    }
    m_size_ = l.m_size_;
    m_capacity_ = l.m_capacity_;
    arr_ = l.arr_;
    l.arr_ = nullptr;
    l.m_capacity_ = 0;
    l.m_size_ = 0;
  }

  ~array() { delete[] arr_; }
  //--------------------------------------------------------------
  reference at(size_type pos) {
    if (pos > m_capacity_) {
      throw out_of_range("Index of element out of range");
    } else {
      return arr_[int(pos)];
    }
  }

  reference operator[](size_type pos) { return at(pos); }

  virtual const_reference front() { return (const_reference)arr_[0]; }

  virtual const_reference back() { return (const_reference)arr_[m_size_ - 1]; }

  T* data() { return arr_; }

  virtual iterator begin() {
    iterator iter(this->arr_);
    return iter;
  }

  virtual iterator end() {
    iterator iter(this->arr_ + this->m_size_);
    return iter;
  }
  //--------------------------------------------------------

  void swap(array& other) {
    size_type cbuff = m_capacity_;
    size_type sbuff = m_size_;

    T* buff = arr_;
    arr_ = other.arr_;
    m_capacity_ = other.m_capacity_;
    m_size_ = other.m_size_;

    other.arr_ = buff;
    other.m_capacity_ = cbuff;
    other.m_size_ = sbuff;
  }

  array<value_type, SIZE>& operator=(array&& other) {
    if (this == &other) {
      throw std::invalid_argument("Error move!");
    }
    arr_ = other.arr_;
    m_capacity_ = other.m_capacity_;
    m_size_ = other.m_size_;
    other.arr_ = nullptr;
    other.m_capacity_ = 0;
    other.m_size_ = 0;
    return *this;
  }

  virtual bool empty() const noexcept { return m_size_ == 0; }

  virtual size_type size() const noexcept { return m_size_; }

  virtual size_type max_size() const noexcept {
    return (size_type)pow(2, (64 - sizeof(T)));
  }

 protected:
  T* arr_;
  size_t m_size_;
  size_t m_capacity_;
};
}  // namespace s21
