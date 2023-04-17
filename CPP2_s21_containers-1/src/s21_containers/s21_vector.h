#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>

#define CAP 32

namespace s21 {
template <class T>
class vector {
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
        throw out_of_range("vector index out of range.");
      }
      return *this;
    }

    ConstIterator operator--(int) {
      if (data != NULL) {
        data--;
      } else {
        throw out_of_range("vector index out of range.");
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
        throw out_of_range("vector index out of range.");
      }
      return *this;
    }

    Iterator operator--(int) {
      if (data != NULL) {
        data--;
      } else {
        throw out_of_range("vector index out of range.");
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
  vector() {
    m_size_ = 0;
    m_capacity_ = CAP;
    arr_ = new T[CAP];
  }

  vector(size_type n) {
    m_size_ = 0;
    m_capacity_ = n;
    arr_ = new T[n];
  }

  vector(std::initializer_list<value_type> const& items) {
    m_size_ = 0;
    m_capacity_ = CAP;
    arr_ = new T[CAP];
    const value_type* item = items.begin();
    for (std::initializer_list<int>::size_type i = 0; i < items.size(); i++) {
      push_back(*(item + i));
    }
  }

  vector(const vector& l) {
    m_size_ = 0;
    m_capacity_ = l.m_capacity_;
    arr_ = new T[m_capacity_];
    for (size_type i = 0; i < l.size(); i++) {
      push_back(l.arr_[i]);
    }
  }

  vector(vector&& l) {
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

  ~vector() { delete[] arr_; }
  //-----------------------------------------------------------
  void push_back(const_reference value) {
    m_size_++;
    if (m_capacity_ > m_size_) {
      arr_[m_size_ - 1] = value;
    } else {
      reserve(m_capacity_ * 2);
      arr_[m_size_ - 1] = value;
    }
  }

  iterator insert(iterator pos, const_reference value) {
    m_size_++;
    if (m_capacity_ <= m_size_) {
      reserve(m_capacity_ * 2);
    }
    T* buf = new T[m_capacity_];
    size_type j = 0;
    Iterator iter;

    for (size_type i = 0; i < m_size_; i++) {
      buf[j] = arr_[i];
      j++;
      if (pos == Iterator((arr_ + i))) {
        Iterator iter(arr_ + i + 1);
        buf[j] = value;
        j++;
      }
    }
    delete[] arr_;
    arr_ = buf;
    return iter;
  }

  void erase(iterator pos) {
    m_size_--;
    if (m_capacity_ <= m_size_) {
      reserve(m_capacity_ * 2);
    }
    T* buf = new T[m_capacity_];
    size_type j = 0;
    for (size_type i = 0; i < m_size_; i++) {
      if (pos != Iterator((arr_ + i))) {
        buf[j] = arr_[i];
        j++;
      }
    }
    delete[] arr_;
    arr_ = buf;
  }

  void pop_back() { erase(end()); }
  //--------------------------------------------------------------
  reference at(size_type pos) {
    if (pos > m_capacity_) {
      throw out_of_range("Index of element out of range");
    } else {
      return arr_[int(pos)];
    }
  }

  reference operator[](size_type pos) { return arr_[pos]; }

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
  void reserve(size_type size) {
    if (size < m_size_) {
      throw out_of_range("Allocation out of range");
    }
    T* buf = new T[int(size)];
    for (size_type i = 0; i < m_size_; i++) {
      buf[i] = arr_[i];
    }
    delete[] arr_;
    arr_ = buf;
    m_capacity_ = size;
  }

  void swap(vector& other) {
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

  vector<value_type>& operator=(vector&& other) {
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

  virtual size_type capacity() const noexcept { return m_capacity_; }

  void shrink_to_fit() { reserve(m_size_); }

  void print() {
    for (size_type i = 0; i < m_size_; i++) {
      cout << arr_[i] << endl;
    }
  }

 protected:
  T* arr_;
  size_t m_size_;
  size_t m_capacity_;
};
}  // namespace s21
