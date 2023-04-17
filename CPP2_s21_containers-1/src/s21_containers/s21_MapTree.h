#ifndef MAPTREE_H
#define MAPTREE_H

#include "s21_map.h"

template <typename Key, typename T>
class BinaryTree {
 private:
  struct Node {
    Node(Key k, T v)
        : key(k), value(v), parent(nullptr), left(nullptr), right(nullptr) {}
    Key key;
    T value;
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
    std::pair<Key&, T&> operator*() const {
      return std::make_pair(std::ref(curr->key), std::ref(curr->value));
    }

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

    std::pair<const Key&, const T&> operator*() const {
      return std::make_pair(curr->key, curr->value);
    }
    Node* curr;
  };
  BinaryTree() : root(nullptr), sz(0) {}
  ~BinaryTree() { clear(); }
  BinaryTree(const BinaryTree& other) : BinaryTree() {
    for (const auto& p : other) {
      insert(p);
    }
  }
  BinaryTree(BinaryTree&& other) : BinaryTree() { swap(other); }
  BinaryTree& operator=(BinaryTree other) {
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
  std::pair<iterator, bool> insert(const std::pair<Key, T>& p) {
    return insert(p.first, p.second);
  }
  std::pair<iterator, bool> insert(Key k, T v) {
    if (!root) {
      root = std::make_unique<Node>(k, v);
      ++sz;
      return std::make_pair(iterator(root.get()), true);
    }
    Node* curr = root.get();
    while (true) {
      if (k < curr->key) {
        if (!curr->left) {
          curr->left = std::make_unique<Node>(k, v);
          curr->left->parent = curr;
          ++sz;
          return std::make_pair(iterator(curr->left.get()), true);
        }
        curr = curr->left.get();
      } else if (curr->key < k) {
        if (!curr->right) {
          curr->right = std::make_unique<Node>(k, v);
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

  void swap(BinaryTree& other) {
    std::swap(root, other.root);
    std::swap(sz, other.sz);
  }

  bool empty() const { return root == nullptr; }

  std::pair<iterator, bool> insert_or_assign(const Key& k, const T& v) {
    auto it = find(k);
    if (it != end()) {
      it.curr->value = v;
      return std::make_pair(it, false);
    } else {
      return insert(k, v);
    }
  }

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
      std::swap(curr->value, successor.curr->value);
      curr = successor.curr;
    }
    Node* child = curr->left ? curr->left.get() : curr->right.get();
    if (child) {
      child->parent = curr->parent;
    }
    if (curr->parent) {
      if (curr->parent->left.get() == curr) {
        curr->parent->left = std::move(child ? curr->left : curr->right);
      } else {
        curr->parent->right = std::move(child ? curr->left : curr->right);
      }
    } else {
      root = std::move(child ? curr->left : curr->right);
    }
    --sz;
  }

  size_t max_size() const { return std::numeric_limits<size_t>::max(); }

 public:
  std::unique_ptr<Node> root;
  size_t sz;
};

#endif
