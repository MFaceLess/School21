#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

namespace s21 {
template <typename T>
class list {
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
        throw out_of_range("List index out of range.");
      }
      return *this;
    }

    ConstIterator operator--(int) {
      if (data != NULL && data->prev != NULL) {
        data = data->prev;
      } else {
        throw out_of_range("List index out of range.");
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
        throw out_of_range("List index out of range.");
      }
      return *this;
    }
    Iterator operator--(int) {
      if (data != NULL && data->prev != NULL) {
        data = data->prev;
      } else {
        throw out_of_range("List index out of range.");
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

  list() {}

  list(size_type n) {
    value_type nothing = (value_type)NULL;
    for (size_type i = 0; i < n; i++) {
      buffer.push_back(nothing);
    }
  }

  list(std::initializer_list<value_type> const& items) {
    const value_type* item = items.begin();
    for (std::initializer_list<int>::size_type i = 0; i < items.size(); i++) {
      buffer.push_back(*(item + i));
    }
  }

  list(const list& l) {
    for (size_type i = 0; i < l.size(); i++) {
      buffer.push_back(l.buffer.get(i)->data);
    }
  }

  list(list&& l) {
    if (this == &l) {
      throw std::invalid_argument("Error move!");
    }
    buffer = std::move(l.buffer);
  }

  ~list() { clear(); }

  list<value_type>& operator=(list&& l) {
    if (this == &l) {
      throw std::invalid_argument("Error move!");
    }
    buffer = std::move(l.buffer);
    return *this;
  }

  const_reference front() const { return buffer.get(0)->data; }

  const_reference back() const { return buffer.get(size() - 1)->data; }

  iterator begin() { return Iterator(buffer.get(0)); }
  iterator end() { return Iterator(buffer.get(size())); }

  bool empty() { return size() == 0; }

  size_type size() const { return (size_type)buffer.get_size(); }
  size_type max_size() { return (size_type)pow(2, (64 - sizeof(ListNode<T>))); }

  void clear() { buffer.clear(); }

  iterator insert(iterator pos, const_reference value) {
    ListNode<T>* node = buffer.insert_pointer(pos.data, value);
    return Iterator(node);
  }

  void erase(iterator pos) { buffer.delete_pointer(pos.data); }
  void push_back(const_reference value) { buffer.push_back(value); }
  void pop_back() { buffer.pop_back(); }
  void push_front(const_reference value) { buffer.push_front(value); }
  void pop_front() { buffer.pop_front(); }
  void swap(list& other) {
    LinkedList<T> buffer_buffer;
    buffer_buffer = std::move(buffer);
    buffer = std::move(other.buffer);
    other.buffer = std::move(buffer_buffer);
  }
  void merge(list& other) {
    while (other.size() != 0) {
      push_back(other.front());
      other.pop_front();
    }
    sort();
  }
  void splice(const_iterator pos, list& other) {
    iterator iter(pos.data);
    while (other.size() != 0) {
      insert(iter, other.front());
      iter++;
      other.pop_front();
    }
  }
  void reverse() {
    LinkedList<T> buffer_buffer;
    while (size() != 0) {
      buffer_buffer.push_front(front());
      pop_front();
    }
    buffer = std::move(buffer_buffer);
  }
  void unique() {
    LinkedList<T> buffer_buffer;
    while (size() != 0) {
      if (not buffer_buffer.has(front())) {
        buffer_buffer.push_back(front());
      }
      pop_front();
    }
    buffer = std::move(buffer_buffer);
  }
  iterator find_max() {
    iterator max_iter = begin();
    for (iterator iter = begin(); iter != end();) {
      if (*iter > *max_iter) {
        max_iter.data = iter.data;
      }
      iter++;
    }
    if (*end() > *max_iter) {
      max_iter.data = end().data;
    }
    return max_iter;
  }
  void sort() {
    LinkedList<T> buffer_buffer;
    size_type s = size();
    for (size_type i = 0; i < s - 1; i++) {
      iterator max_iter = find_max();
      buffer_buffer.push_back(*max_iter);
      erase(max_iter);
    }
    buffer_buffer.push_back(*begin());
    buffer.clear();
    buffer = std::move(buffer_buffer);
    reverse();
  }
  void print() {
    LinkedList<T> buffer_buffer;
    printf("\n%ld--\n", size());
    for (iterator pos = begin(); pos != end(); pos++) {
      printf("%d\n", *pos);
    }
    printf("%d\n", *end());
  }

 private:
  LinkedList<T> buffer;
};
}  // namespace s21