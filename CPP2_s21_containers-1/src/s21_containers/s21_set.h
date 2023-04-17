#ifndef S21SET_H
#define S21SET_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>  // std::out_of_range
#include <utility>    // std::pair, std::make_pair и std::move

#include "s21_SetTree.h"

namespace s21 {
template <class Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Tree<Key>::iterator;
  using const_iterator = typename Tree<Key>::const_iterator;
  using size_type = size_t;

 public:
  set() = default;
  set(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }
  set(set& s) {
    for (auto it = s.begin(); it != s.end(); ++it) {
      insert(*it);
    }
  }
  set(set&& s) : tree(std::move(s.tree)) {}
  ~set() = default;
  set& operator=(set& s) {
    if (this != &s) {
      for (auto it = s.begin(); it != s.end(); ++it) {
        insert(*it);
      }
    }
    return *this;
  }
  set& operator=(set&& s) {
    if (this != &s) {
      tree = std::move(s.tree);
    }
    return *this;
  }

  iterator begin() { return tree.begin(); }
  iterator end() { return tree.end(); }

  bool empty() { return tree.empty(); }
  size_type size() { return tree.size(); }
  size_type max_size() { return tree.max_size(); }

  void clear() { tree.clear(); }
  std::pair<iterator, bool> insert(const value_type& value) {
    auto result = tree.insert(value);
    return std::make_pair(iterator(result.first), result.second);
  }
  void erase(iterator pos) {
    if (pos == tree.end()) {
      throw std::out_of_range("map::erase() invalid iterator");
    }
    tree.erase(pos);
  }
  void swap(set& other) { tree.swap(other.tree); }
  void merge(set& other) {
    for (auto&& item : other) {
      insert(std::move(item));
    }
    other.clear();
  }

  iterator find(const Key& key) { return tree.find(key); }
  bool contains(const Key& key) { return tree.find(key) != tree.end(); }

 private:
  Tree<Key> tree;
};
}  // namespace s21

#endif