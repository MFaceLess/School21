#ifndef S21MAP_H
#define S21MAP_H

#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>  // std::out_of_range
#include <utility>    // std::pair, std::make_pair и std::move

#include "s21_MapTree.h"

namespace s21 {
template <class Key, class T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<key_type, mapped_type>::iterator;
  using const_iterator =
      typename BinaryTree<key_type, mapped_type>::const_iterator;
  using size_type = size_t;

  // Constructors
  map() = default;
  map(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }
  map(map& m) {
    for (auto it = m.begin(); it != m.end(); ++it) {
      insert((*it).first, (*it).second);
    }
  }
  map(map&& m) : tree(std::move(m.tree)) {}

  // Operator Overloading
  map<Key, T>& operator=(map& m) {
    if (this != &m) {
      for (auto it = m.begin(); it != m.end(); ++it) {
        insert((*it).first, (*it).second);
      }
    }
    return *this;
  }
  map<Key, T>& operator=(map&& m) {
    if (this != &m) {
      tree = std::move(m.tree);
    }
    return *this;
  }
  // Destructor
  ~map() = default;

  // Element Access
  T& at(const Key& key) {
    auto it = tree.find(key);
    if (it == tree.end()) {
      throw std::out_of_range("map::at() key not found");
    }
    return (*it).second;
  }
  T& operator[](const Key& key) {
    auto it = tree.find(key);
    if (it == tree.end()) {
      throw std::out_of_range("map::operator[] key not found");
    }
    return (*it).second;
  }

  // Iterators
  iterator begin() { return tree.begin(); }
  iterator end() { return tree.end(); }

  // Capacity
  bool empty() const { return tree.empty(); }
  size_type size() const { return tree.size(); }
  size_type max_size() const { return tree.max_size(); }

  // Modifiers
  void clear() { tree.clear(); }
  std::pair<iterator, bool> insert(const value_type& value) {
    auto result = tree.insert(value);
    return std::make_pair(iterator(result.first), result.second);
  }
  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    auto result = tree.insert(std::make_pair(key, obj));
    return std::make_pair(iterator(result.first), result.second);
  }
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    auto result = tree.insert_or_assign(key, obj);
    return std::make_pair(typename map<Key, T>::iterator(result.first),
                          result.second);
  }
  void erase(iterator pos) {
    if (pos == tree.end()) {
      throw std::out_of_range("map::erase() invalid iterator");
    }
    tree.erase(pos);
  }
  void swap(map& other) { tree.swap(other.tree); }
  void merge(map& other) {
    for (auto&& item : other) {
      insert(std::move(item));
    }
    other.clear();
  }

  // Lookup
  bool contains(const Key& key) const { return tree.find(key) != tree.end(); }
  iterator find(const Key& key) { return tree.find(key); }
  const_iterator find(const Key& key) const { return tree.find(key); }

 private:
  BinaryTree<key_type, mapped_type> tree;
};
}  // namespace s21

#endif