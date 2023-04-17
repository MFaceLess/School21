#ifndef S21MULTISET_H
#define S21MULTISET_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>  // std::out_of_range
#include <utility>    // std::pair, std::make_pair и std::move

#include "s21_MultisetTree.h"

namespace s21 {
template <class Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename mulsetTree<Key>::iterator;
  using const_iterator = typename mulsetTree<Key>::const_iterator;
  using size_type = size_t;

 public:
  multiset() = default;
  multiset(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }
  multiset(multiset& s) {
    for (auto it = s.begin(); it != s.end(); ++it) {
      insert(*it);
    }
  }
  multiset(multiset&& s) : tree(std::move(s.tree)) {}
  ~multiset() = default;
  multiset& operator=(multiset&& s) {
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
  void swap(multiset& other) { tree.swap(other.tree); }
  void merge(multiset& other) {
    for (auto&& item : other) {
      insert(std::move(item));
    }
    other.clear();
  }
  iterator find(const Key& key) { return tree.find(key); }
  bool contains(const Key& key) { return tree.find(key) != tree.end(); }
  size_type count(const Key& key) { return tree.count(key); }
  std::pair<iterator, iterator> equal_range(const Key& key) {
    return std::make_pair(tree.lower_bound(key), tree.last_equal(key));
  }
  iterator lower_bound(const Key& key) { return tree.lower_bound(key); }
  iterator upper_bound(const Key& key) { return tree.upper_bound(key); }

 private:
  mulsetTree<Key> tree;
};
}  // namespace s21

#endif