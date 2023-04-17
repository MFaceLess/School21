#include <stdexcept>
using namespace std;

template <typename T>
struct ListNode {
 public:
  T data;
  ListNode *prev, *next;
  ListNode() {
    prev = nullptr;
    next = nullptr;
  }
  ListNode(T Data, ListNode *Prev, ListNode *Next) {
    data = Data;
    prev = Prev;
    next = Next;
  }
};

template <typename T>
class LinkedList {
 protected:
  unsigned long long arr_size;
  ListNode<T> *head, *tail;

 public:
  LinkedList<T>() {
    arr_size = 0;
    head = NULL;
    tail = NULL;
  }
  ~LinkedList<T>() {
    while (head != NULL) {
      pop_front();
    }
  }
  bool empty() const {
    if (head == NULL)
      return true;
    else
      return false;
  }
  void push_front(T data) {
    if (head != NULL) {
      head = new ListNode<T>(data, NULL, head);
      head->next->prev = head;
    } else {
      head = new ListNode<T>(data, NULL, NULL);
      tail = head;
    }
    arr_size++;
  }
  void push_back(T data) {
    if (tail != NULL) {
      tail = new ListNode<T>(data, tail, NULL);
      tail->prev->next = tail;
    } else {
      tail = new ListNode<T>(data, NULL, NULL);
      head = tail;
    }
    arr_size++;
  }
  void pop_front() {
    if (head != NULL) {
      ListNode<T> *temp = head;
      head = temp->next;
      delete temp;
    } else
      throw out_of_range("This list is empty.");
    arr_size--;
  }
  void pop_back() {
    if (tail != NULL) {
      ListNode<T> *temp = tail;
      tail = temp->prev;
      tail->next = NULL;
      delete temp;
    } else
      throw out_of_range("This list is empty.");
    arr_size--;
  }
  ListNode<T> *get(int index) const {
    int n = 0;
    ListNode<T> *search = head;
    while (n < index) {
      if (search != NULL && search->next != NULL) {
        search = search->next;
      }
      n++;
    }
    if (search == NULL || index < 0 || index > int(get_size())) {
      throw out_of_range("Index of element out of range");
    }
    return search;
  }
  void insert(int index, T data) {
    int n = 0;
    ListNode<T> *search = head;
    while (n < index) {
      if (search != NULL && search->next != NULL) {
        search = search->next;
      }
      n++;
    }
    if (search == NULL || index < 0 || index > int(get_size())) {
      throw out_of_range("Index of element out of range");
    }
    ListNode<T> *new_node = new ListNode<T>(data, NULL, NULL);
    ListNode<T> *temp = search->next;
    new_node->prev = search;
    new_node->next = temp;
    search->next = new_node;
    arr_size++;
  }
  ListNode<T> *insert_pointer(ListNode<T> *search, const T data) {
    if (search == NULL) {
      throw out_of_range("Index of element out of range");
    }
    if (search->next == NULL) {
      push_back(data);
    } else {
      ListNode<T> *new_node = new ListNode<T>(data, NULL, NULL);
      ListNode<T> *temp = search->next;
      new_node->prev = search;
      new_node->next = temp;
      search->next = new_node;
      arr_size++;
    }
    return search->next;
  }
  void delete_pointer(ListNode<T> *pos) {
    if (pos == NULL) {
      throw out_of_range("Index of element out of range");
    }
    ListNode<T> *temp = pos;
    if (pos->prev == NULL) {
      head = pos->next;
      head->prev = NULL;

    } else if (pos->next == NULL) {
      tail = pos->prev;
      tail->next = NULL;

    } else {
      temp->prev->next = temp->next;
      temp->next->prev = temp->prev;
    }
    delete temp;
    arr_size--;
  }
  unsigned long long get_size() const { return arr_size; }
  LinkedList<T> &operator=(LinkedList<T> &&l) {
    if (this == &l) {
      throw std::invalid_argument("Error move!");
    }
    arr_size = l.arr_size;
    head = l.head;
    tail = l.tail;
    l.arr_size = 0;
    l.head = NULL;
    l.tail = NULL;
    return *this;
  }
  void clear() {
    while (head != NULL) {
      pop_front();
    }
  }

  bool has(T value) {
    for (int i = 0; i < int(arr_size); i++) {
      if (get(i)->data == value) {
        return true;
      }
    }
    return false;
  }
};
