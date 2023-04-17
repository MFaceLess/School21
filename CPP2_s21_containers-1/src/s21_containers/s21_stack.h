#include <iostream>
#include <stdexcept>
using namespace std;

namespace s21 {
template <typename T>
class stack {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;

  class ConstIterator {
   public:
    ListNode<T>* data;
    ConstIterator() { this->data = nullptr; }
    ConstIterator(ListNode<T>* value) { this->data = value; }
    ConstIterator(const ConstIterator& other) : data(other.data) {}
    ~ConstIterator() {}

    ConstIterator operator++(int) {
      if (data != NULL && data->next != NULL) {
        data = data->next;
      } else {
        throw out_of_range("stack index out of range.");
      }
      return *this;
    }

    ConstIterator operator--(int) {
      if (data != NULL && data->prev != NULL) {
        data = data->prev;
      } else {
        throw out_of_range("stack index out of range.");
      }
      return *this;
    }

    const_reference operator*() const {
      if (data == NULL) {
        throw out_of_range("Empty iterator");
      }
      return data->data;
    }

    bool operator!=(const ConstIterator& other) const {
      return data != other.data;
    }

    bool operator==(const ConstIterator& other) const {
      return data == other.data;
    }
  };

  class Iterator : public ConstIterator {
   public:
    ListNode<T>* data;
    Iterator() { this->data = nullptr; }
    Iterator(ListNode<T>* value) { this->data = value; }
    Iterator(const Iterator& other) : ConstIterator(other), data(other.data) {}
    ~Iterator() {}
    Iterator operator++(int) {
      if (data != NULL && data->next != NULL) {
        data = data->next;
      } else {
        throw out_of_range("stack index out of range.");
      }
      return *this;
    }
    Iterator operator--(int) {
      if (data != NULL && data->prev != NULL) {
        data = data->prev;
      } else {
        throw out_of_range("stack index out of range.");
      }
      return *this;
    }
    reference operator*() const {
      if (data == NULL) {
        throw out_of_range("Empty iterator");
      }
      return data->data;
    }
    Iterator operator=(const Iterator& other) {
      data = other.data;
      return *this;
    }
    bool operator!=(const Iterator& other) const { return data != other.data; }
    bool operator==(const Iterator& other) const { return data == other.data; }
  };

  typedef Iterator iterator;
  typedef ConstIterator const_iterator;

  stack() {}

  stack(size_type n) {
    value_type nothing = (value_type)NULL;
    for (size_type i = 0; i < n; i++) {
      buffer.push_back(nothing);
    }
  }

  stack(std::initializer_list<value_type> const& items) {
    const value_type* item = items.begin();
    for (std::initializer_list<int>::size_type i = 0; i < items.size(); i++) {
      buffer.push_front(*(item + i));
    }
  }

  stack(const stack& l) {
    for (size_type i = 0; i < l.size(); i++) {
      buffer.push_front(l.buffer.get(l.size() - 1 - i)->data);
    }
  }

  stack(stack&& l) {
    if (this == &l) {
      throw std::invalid_argument("Error move!");
    }
    buffer = std::move(l.buffer);
  }

  ~stack() {}

  stack<value_type>& operator=(stack&& l) {
    if (this == &l) {
      throw std::invalid_argument("Error move!");
    }
    buffer = std::move(l.buffer);
    return *this;
  }

  const_reference top() const { return buffer.get(0)->data; }

  bool empty() { return size() == 0; }

  size_type size() const { return (size_type)buffer.get_size(); }

  void push(const_reference value) { buffer.push_front(value); }
  void pop() { buffer.pop_front(); }
  void swap(stack& other) {
    LinkedList<T> buffer_buffer;
    buffer_buffer = std::move(buffer);
    buffer = std::move(other.buffer);
    other.buffer = std::move(buffer_buffer);
  }
  void print() {
    LinkedList<T> buffer_buffer;
    printf("\n%ld--\n", size());
    for (iterator pos = begin_non_const(); pos != end_non_const(); pos++) {
      printf("%d\n", *pos);
    }
    printf("%d\n", *end_non_const());
  }

 private:
  iterator begin_non_const() { return Iterator(buffer.get(0)); }
  iterator end_non_const() { return Iterator(buffer.get(size())); }
  LinkedList<T> buffer;
};
}  // namespace s21