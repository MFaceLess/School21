#ifndef MULTISETTREE_H
#define MULTISETTREE_H

#include "s21_multiset.h"

template <typename Key>
class mulsetTree {
 private:
  struct Node {
    Node(Key k) : key(k), parent(nullptr), left(nullptr), right(nullptr) {}
    Key key;
    Node* parent = nullptr;
    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;
  };

 public:
  class iterator {
   public:
    iterator(Node* n = nullptr) : curr(n) {}

    bool operator==(const iterator& other) const { return curr == other.curr; }
    bool operator!=(const iterator& other) const { return curr != other.curr; }
    iterator& operator++() {
      if (curr->right) {
        curr = curr->right.get();
        while (curr->left) {
          curr = curr->left.get();
        }
      } else {
        Node* parent = curr->parent;
        while (parent && curr == parent->right.get()) {
          curr = parent;
          parent = parent->parent;
        }
        curr = parent;
      }
      return *this;
    }
    Key& operator*() const { return std::ref(curr->key); }

   public:
    Node* curr;
  };
  class const_iterator {
   public:
    const_iterator(Node* n = nullptr) : curr(n) {}

    bool operator==(const const_iterator& other) const {
      return curr == other.curr;
    }
    bool operator!=(const const_iterator& other) const {
      return curr != other.curr;
    }

    const_iterator& operator++() {
      if (curr->right) {
        curr = curr->right.get();
        while (curr->left) {
          curr = curr->left.get();
        }
      } else {
        Node* parent = curr->parent;
        while (parent && curr == parent->right.get()) {
          curr = parent;
          parent = parent->parent;
        }
        curr = parent;
      }
      return *this;
    }

    const Key& operator*() const { return curr->key; }
    Node* curr;
  };
  mulsetTree() : root(nullptr), sz(0) {}
  ~mulsetTree() { clear(); }
  mulsetTree(const mulsetTree& other) : mulsetTree() {
    for (const auto& p : other) {
      insert(p);
    }
  }
  mulsetTree(mulsetTree&& other) : mulsetTree() { swap(other); }
  mulsetTree& operator=(mulsetTree other) {
    swap(other);
    return *this;
  }
  iterator begin() {
    if (!root) {
      return end();
    }
    Node* n = root.get();
    while (n->left) {
      n = n->left.get();
    }
    return iterator(n);
  }
  iterator end() { return iterator(nullptr); }
  const_iterator begin() const {
    if (!root) {
      return end();
    }
    Node* n = root.get();
    while (n->left) {
      n = n->left.get();
    }
    return const_iterator(n);
  }
  const_iterator end() const { return const_iterator(nullptr); }
  std::pair<iterator, bool> insert(Key k) {
    if (!root) {
      root = std::make_unique<Node>(k);
      ++sz;
      return std::make_pair(iterator(root.get()), true);
    }
    Node* curr = root.get();
    while (true) {
      if (k < curr->key) {
        if (!curr->left) {
          curr->left = std::make_unique<Node>(k);
          curr->left->parent = curr;
          ++sz;
          return std::make_pair(iterator(curr->left.get()), true);
        }
        curr = curr->left.get();
      } else if (curr->key < k || curr->key == k) {
        if (!curr->right) {
          curr->right = std::make_unique<Node>(k);
          curr->right->parent = curr;
          ++sz;
          return std::make_pair(iterator(curr->right.get()), true);
        }
        curr = curr->right.get();
      } else {
        return std::make_pair(iterator(curr), false);
      }
    }
  }
  iterator find(const Key& k) {
    Node* curr = root.get();
    while (curr) {
      if (k < curr->key) {
        curr = curr->left.get();
      } else if (curr->key < k) {
        curr = curr->right.get();
      } else {
        return iterator(curr);
      }
    }
    return end();
  }
  const_iterator find(const Key& k) const {
    Node* curr = root.get();
    while (curr) {
      if (k < curr->key) {
        curr = curr->left.get();
      } else if (curr->key < k) {
        curr = curr->right.get();
      } else {
        return const_iterator(curr);
      }
    }
    return end();
  }
  size_t size() const { return sz; }

  void clear() {
    root = nullptr;
    sz = 0;
  }

  void swap(mulsetTree& other) {
    std::swap(root, other.root);
    std::swap(sz, other.sz);
  }

  bool empty() const { return root == nullptr; }

  void erase(const Key& k) {
    auto it = find(k);
    if (it != end()) {
      erase(it);
    }
  }

  void erase(iterator it) {
    Node* curr = it.curr;
    if (curr->left && curr->right) {
      auto successor = ++it;
      std::swap(curr->key, successor.curr->key);
      curr = successor.curr;
    }
    Node* child = nullptr;
    if (curr->left) {
      curr->left->parent = curr->parent;
      child = curr->left.release();
    } else if (curr->right) {
      curr->right->parent = curr->parent;
      child = curr->right.release();
    }
    if (curr->parent) {
      if (curr->parent->left.get() == curr) {
        curr->parent->left.reset(child);
      } else {
        curr->parent->right.reset(child);
      }
    } else {
      root.reset(child);
    }
    --sz;
  }

  size_t max_size() const { return std::numeric_limits<size_t>::max(); }

  size_t count(const Key& key) {
    if (find(key) == nullptr) {
      throw std::out_of_range("Element not found in multiset");
    }
    size_t result = 0;
    for (auto it = begin(); it != end(); ++it) {
      if ((*it) == key) {
        result++;
      }
    }
    return result;
  }

  iterator lower_bound(const Key& key) {
    if (find(key) == nullptr) {
      throw std::out_of_range("Element not found in multiset");
    }
    return find(key);
  }

  iterator upper_bound(const Key& key) {
    auto it = begin();
    for (; it != end(); ++it) {
      if ((*it) > key) {
        break;
      }
    }
    return it;
  }

  iterator last_equal(const Key& key) {
    if (find(key) == nullptr) {
      throw std::out_of_range("Element not found in multiset");
    }
    auto it = find(key);
    size_t check = count(key);
    while (--check > 0) {
      ++it;
    }
    return it;
  }

 public:
  std::unique_ptr<Node> root;
  size_t sz;
};

#endif
