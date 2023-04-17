#include <gtest/gtest.h>

#include <stdexcept>

#include "s21_containers.h"
#include "s21_containersplus.h"

//------------------LIST------------------
TEST(SeqContainers, list_base_cnst) { s21::list<int> l; }

TEST(SeqContainers, list_n_cnst) {
  s21::list<int> l(5);
  ASSERT_TRUE(l.size() == 5);
}

TEST(SeqContainers, list_init_list_cnst) {
  s21::list<int> l = {1, 2, 3, 4};
  ASSERT_TRUE(l.size() == 4);
  ASSERT_TRUE(l.front() == 1);
  ASSERT_TRUE(l.back() == 4);
}

TEST(SeqContainers, list_init_list_empty_cnst) {
  s21::list<int> l = {};
  ASSERT_TRUE(l.size() == 0);
}

TEST(SeqContainers, list_copy_cnst) {
  s21::list<int> l = {1, 2, 3, 4};
  s21::list<int> l2(l);
  ASSERT_TRUE(l2.size() == 4);
  ASSERT_TRUE(l2.front() == 1);
  ASSERT_TRUE(l2.back() == 4);
}

TEST(SeqContainers, list_move_cnst) {
  s21::list<int> l = {1, 2, 3, 4};
  s21::list<int> l2 = std::move(l);
  ASSERT_TRUE(l2.size() == 4);
  ASSERT_TRUE(l2.front() == 1);
  ASSERT_TRUE(l2.back() == 4);
  ASSERT_TRUE(l.empty());
}

TEST(SeqContainers, list_iterate) {
  s21::list<int> l = {1, 2, 3, 4};
  s21::list<int>::Iterator iter = l.begin();
  ASSERT_TRUE(*(iter) == 1);
  iter++;
  ASSERT_TRUE(*(iter) == 2);
  iter++;
  ASSERT_TRUE(*(iter) == 3);
  iter++;
  ASSERT_TRUE(*(iter) == 4);
  EXPECT_THROW(iter++, std::out_of_range);
}

TEST(SeqContainers, list_clear) {
  s21::list<int> l = {1, 2, 3, 4};
  l.clear();
  ASSERT_TRUE(l.empty());
}

TEST(SeqContainers, list_push_pop_erase_insert) {
  s21::list<int> l = {1, 2, 3, 4, 5, 6};

  ASSERT_TRUE(l.back() == 6);
  l.pop_back();
  ASSERT_EQ(l.back(), 5);
  ASSERT_TRUE(l.front() == 1);
  l.pop_front();
  ASSERT_EQ(l.front(), 2);
  ASSERT_TRUE(*(l.begin()++) == 3);
  l.erase(l.begin()++);
  ASSERT_TRUE(*(l.begin()++) == 4);
  ASSERT_TRUE(l.size() == 3);

  l.push_front(41);
  l.push_back(42);

  ASSERT_TRUE(l.front() == 41 && l.back() == 42);
  ASSERT_TRUE(l.size() == 5);
  l.insert(l.begin(), 40);
  ASSERT_TRUE(*(l.begin()++) == 40);
  ASSERT_TRUE(l.size() == 6);
}

TEST(SeqContainers, list_swap) {
  s21::list<int> l = {1, 2, 3};
  s21::list<int> l2 = {4, 5, 6, 7};
  l.swap(l2);

  ASSERT_TRUE(l.size() == 4 && l2.size() == 3);
  ASSERT_TRUE(l.front() == 4 && l2.front() == 1);
}

TEST(SeqContainers, list_splice_sort_merge) {
  s21::list<int> l1 = {1, 2, 3};
  s21::list<int> l2 = {4, 5, 6, 7};
  s21::list<int> l3 = {0, -5, 22, 4};
  l1.splice(s21::list<int>::ConstIterator(l1.begin().data), l2);
  ASSERT_TRUE(*(l1.begin()++) == 4 && l1.size() == 7);
  l1.sort();
  ASSERT_TRUE(*(l1.begin()++) == 2 && l1.size() == 7);
  l1.merge(l3);
  ASSERT_TRUE(*(l1.begin()) == -5 && l1.size() == 11 && l1.back() == 22);
}

TEST(SeqContainers, list_unique) {
  s21::list<int> l1 = {1, 2, 2, 2, 3, 3};
  l1.unique();
  ASSERT_EQ(l1.size(), 3);
}

//------------------QUEUE------------------

TEST(SeqContainers, queue_base_cnst) { s21::queue<int> l; }

TEST(SeqContainers, queue_n_cnst) {
  s21::queue<int> l(5);
  ASSERT_TRUE(l.size() == 5);
}

TEST(SeqContainers, queue_init_list_cnst) {
  s21::queue<int> l = {1, 2, 3, 4};
  ASSERT_TRUE(l.size() == 4);
  ASSERT_TRUE(l.front() == 1);
  ASSERT_TRUE(l.back() == 4);
}

TEST(SeqContainers, queue_init_list_empty_cnst) {
  s21::queue<int> l = {};
  ASSERT_TRUE(l.size() == 0);
}

TEST(SeqContainers, queue_copy_cnst) {
  s21::queue<int> l = {1, 2, 3, 4};
  s21::queue<int> l2(l);
  ASSERT_TRUE(l2.size() == 4);
  ASSERT_TRUE(l2.front() == 1);
  ASSERT_TRUE(l2.back() == 4);
}

TEST(SeqContainers, queue_move_cnst) {
  s21::queue<int> l = {1, 2, 3, 4};
  s21::queue<int> l2 = std::move(l);
  ASSERT_TRUE(l2.size() == 4);
  ASSERT_TRUE(l2.front() == 1);
  ASSERT_TRUE(l2.back() == 4);
  ASSERT_TRUE(l.empty());
}

TEST(SeqContainers, queue_push_pop_erase_insert) {
  s21::queue<int> l = {1, 2, 3, 4, 5, 6};

  ASSERT_TRUE(l.front() == 1);
  l.pop();
  ASSERT_EQ(l.front(), 2);
  l.push(42);

  ASSERT_TRUE(l.front() == 2 && l.back() == 42);
  ASSERT_TRUE(l.size() == 6);
}

TEST(SeqContainers, queue_swap) {
  s21::queue<int> l = {1, 2, 3};
  s21::queue<int> l2 = {4, 5, 6, 7};
  l.swap(l2);

  ASSERT_TRUE(l.size() == 4 && l2.size() == 3);
  ASSERT_TRUE(l.front() == 4 && l2.front() == 1);
}

//-------------------STACK------------

TEST(SeqContainers, stack_base_cnst) { s21::stack<int> l; }

TEST(SeqContainers, stack_n_cnst) {
  s21::stack<int> l(5);
  ASSERT_TRUE(l.size() == 5);
}

TEST(SeqContainers, stack_init_list_cnst) {
  s21::stack<int> l = {1, 2, 3, 4};
  ASSERT_TRUE(l.size() == 4);
  ASSERT_TRUE(l.top() == 4);
}

TEST(SeqContainers, stack_init_list_empty_cnst) {
  s21::stack<int> l = {};
  ASSERT_TRUE(l.size() == 0);
}

TEST(SeqContainers, stack_copy_cnst) {
  s21::stack<int> l = {1, 2, 3, 4};
  s21::stack<int> l2(l);
  ASSERT_TRUE(l2.size() == 4);
  ASSERT_TRUE(l2.top() == 4);
}

TEST(SeqContainers, stack_move_cnst) {
  s21::stack<int> l = {1, 2, 3, 4};
  s21::stack<int> l2 = std::move(l);
  ASSERT_TRUE(l2.size() == 4);
  ASSERT_TRUE(l2.top() == 4);
  ASSERT_TRUE(l.empty());
}

TEST(SeqContainers, stack_push_pop_erase_insert) {
  s21::stack<int> l = {1, 2, 3, 4, 5, 6};

  ASSERT_TRUE(l.top() == 6);
  l.pop();
  ASSERT_EQ(l.top(), 5);
  l.push(42);

  ASSERT_TRUE(l.top() == 42);
  ASSERT_TRUE(l.size() == 6);
}

TEST(SeqContainers, stack_swap) {
  s21::stack<int> l = {1, 2, 3};
  s21::stack<int> l2 = {4, 5, 6, 7};
  l.swap(l2);

  ASSERT_TRUE(l.size() == 4 && l2.size() == 3);
  ASSERT_TRUE(l.top() == 7 && l2.top() == 3);
}

//---------------------VECTOR------------------------------

TEST(SeqContainers, vector_base_cnst) { s21::vector<int> l; }

TEST(SeqContainers, vector_n_cnst) {
  s21::vector<int> l(5);
  ASSERT_TRUE(l.capacity() == 5);
}

TEST(SeqContainers, vector_init_list_cnst) {
  s21::vector<int> l = {1, 2, 3, 4};
  ASSERT_TRUE(l.size() == 4);
  ASSERT_TRUE(l.front() == 1);
  ASSERT_TRUE(l.back() == 4);
}

TEST(SeqContainers, vector_init_list_empty_cnst) {
  s21::vector<int> l = {};
  ASSERT_TRUE(l.size() == 0);
}

TEST(SeqContainers, vector_copy_cnst) {
  s21::vector<int> l = {1, 2, 3, 4};
  s21::vector<int> l2(l);
  ASSERT_TRUE(l2.size() == 4);
  ASSERT_TRUE(l2.front() == 1);
  ASSERT_TRUE(l2.back() == 4);
}

TEST(SeqContainers, vector_move_cnst) {
  s21::vector<int> l = {1, 2, 3, 4};
  s21::vector<int> l2 = std::move(l);
  ASSERT_TRUE(l2.size() == 4);
  ASSERT_TRUE(l2.front() == 1);
  ASSERT_TRUE(l2.back() == 4);
  ASSERT_TRUE(l.empty());
}

TEST(SeqContainers, vector_push) {
  s21::vector<int> v = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                        12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
                        23, 24, 25, 26, 27, 28, 29, 30, 31};
  ASSERT_TRUE(v.back() == 31 && v.capacity() == 32);
  v.push_back(32);
  ASSERT_TRUE(v.back() == 32 && v.capacity() == 64);
  v.insert(v.begin()++, 100);
  ASSERT_TRUE(*((v.begin()++)++) == 100 && v.size() == 33);
  v.erase(v.begin());
  v.pop_back();
  ASSERT_TRUE(v.front() == 2 && v.size() == 31 && v.back() == 31);
  s21::vector<int> v2 = {1, 2, 3};
  v.swap(v2);
  ASSERT_TRUE(v.front() == 1 && v.size() == 3 && v.back() == 3);
  v.shrink_to_fit();
  ASSERT_TRUE(v.capacity() == 3);
}

//-------------------ARRAY-----------------------------------------
TEST(SeqContainers, array_base_cnst) { s21::array<int, 32> l; }

TEST(SeqContainers, array_init_list_cnst) {
  s21::array<int, 32> l = {1, 2, 3, 4};
  ASSERT_TRUE(l.size() == 32);
  ASSERT_TRUE(l.front() == 1);
  ASSERT_TRUE(l.at(3) == 4);
}

TEST(SeqContainers, array_init_list_empty_cnst) {
  s21::array<int, 32> l = {};
  ASSERT_TRUE(l.size() == 32);
}

TEST(SeqContainers, array_copy_cnst) {
  s21::array<int, 32> l = {1, 2, 3, 4};
  s21::array<int, 32> l2(l);
  ASSERT_TRUE(l2.size() == 32);
  ASSERT_TRUE(l2.front() == 1);
  ASSERT_TRUE(l2.at(3) == 4);
}

TEST(SeqContainers, array_move_cnst) {
  s21::array<int, 32> l = {1, 2, 3, 4};
  s21::array<int, 32> l2 = std::move(l);
  ASSERT_TRUE(l2.size() == 32);
  ASSERT_TRUE(l2.front() == 1);
  ASSERT_TRUE(l2.at(3) == 4);
  ASSERT_TRUE(l.empty());
}

//-------------------MAP-----------------------------------------
TEST(MapTest, DefaultConstructor) {
  s21::map<int, int> m;
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, InitializerListConstructor) {
  s21::map<int, int> m{{1, 2}, {3, 4}};
  EXPECT_EQ(m.size(), 2);
  EXPECT_NE(m.find(1), m.end());
  EXPECT_EQ(m.find(2), m.end());
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, int> m{{1, 2}, {3, 4}};
  s21::map<int, int> copy(m);
  EXPECT_EQ(m.size(), copy.size());
}

TEST(MapTest, AssignmentOperator) {
  s21::map<int, int> m{{1, 2}, {3, 4}};
  s21::map<int, int> copy = m;
  EXPECT_EQ(m.size(), copy.size());
}

TEST(MapTest, ElementAccess) {
  s21::map<int, int> m{{1, 2}, {3, 4}};
  m[1] = 5;
  EXPECT_EQ(m[1], 5);
  EXPECT_EQ(m.at(1), 5);

  bool exceptionThrown = false;
  try {
    m.at(2);
  } catch (std::out_of_range &) {
    exceptionThrown = true;
  }
  EXPECT_TRUE(exceptionThrown);
}

TEST(MapTest, Iterators) {
  s21::map<int, int> m{{1, 2}, {3, 4}};
  s21::map<int, int>::iterator it = m.begin();
  EXPECT_EQ(it, m.find(1));
  EXPECT_NE(it, m.end());
}

TEST(MapTest, Modifiers) {
  s21::map<int, int> m{{1, 2}, {3, 4}};
  EXPECT_TRUE(m.insert({2, 3}).second);
  EXPECT_FALSE(m.insert({1, 0}).second);

  m.insert_or_assign(1, 5);
  EXPECT_EQ(m[1], 5);

  m.erase(m.find(2));
  EXPECT_EQ(m.find(2), m.end());

  s21::map<int, int> m2{{5, 6}};
  m.swap(m2);
  EXPECT_EQ(m.size(), 1);

  s21::map<int, int> merged{{4, 8}, {3, 6}};
  m.merge(merged);
  EXPECT_EQ(m[4], 8);
}

TEST(MapTest, Lookup) {
  s21::map<int, int> m{{1, 2}, {3, 4}};
  EXPECT_TRUE(m.contains(1));
  EXPECT_FALSE(m.contains(2));
  EXPECT_NE(m.find(1), m.end());
  EXPECT_EQ(m.find(2), m.end());
}

TEST(MapTest, InsertOrAssign) {
  s21::map<int, int> m{{1, 2}, {3, 4}};
  auto [it, success] = m.insert_or_assign(2, 5);
  EXPECT_EQ((*it).second, 5);
  EXPECT_TRUE(success);

  auto [it2, success2] = m.insert_or_assign(1, 6);
  EXPECT_EQ((*it2).second, 6);
  EXPECT_FALSE(success2);
}

//-------------------SET-----------------------------------------
TEST(SetTest, DefaultConstructor) {
  s21::set<int> s;
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(0, s.size());
}

TEST(SetTest, InitializerListConstructor) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2({3, 4, 5});
  s1.merge(s2);
  ASSERT_TRUE(s2.empty());
  ASSERT_FALSE(s1.empty());
  ASSERT_EQ(5, s1.size());
  ASSERT_EQ(0, s2.size());
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2(s1);
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s2.empty());
  ASSERT_EQ(s1.size(), s2.size());
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2(std::move(s1));
  ASSERT_TRUE(s1.empty());
  ASSERT_FALSE(s2.empty());
  ASSERT_EQ(3, s2.size());
}

TEST(SetTest, AssignmentOperator) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2;
  s2 = s1;
  ASSERT_FALSE(s1.empty());
  ASSERT_FALSE(s2.empty());
  ASSERT_EQ(s1.size(), s2.size());

  s21::set<int> s3({4, 5, 6});
  s2 = std::move(s3);
  ASSERT_TRUE(s3.empty());
  ASSERT_FALSE(s2.empty());
  ASSERT_EQ(3, s2.size());
}

TEST(SetTest, Contains) {
  s21::set<int> s({1, 2, 3});
  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
  ASSERT_FALSE(s.contains(4));
}

TEST(SetTest, InsertAndErase) {
  s21::set<int> s;
  auto result = s.insert(1);
  ASSERT_TRUE(result.second);
  ASSERT_EQ(1, s.size());

  result = s.insert(1);
  ASSERT_FALSE(result.second);
  ASSERT_EQ(1, s.size());

  s.insert(2);
  s.insert(3);
  auto it = s.find(1);
  ASSERT_NE(s.end(), it);
  s.erase(it);
  ASSERT_EQ(2, s.size());
  ASSERT_FALSE(s.contains(1));
  ASSERT_TRUE(s.contains(2));
  ASSERT_TRUE(s.contains(3));
}

TEST(SetTest, Swap) {
  s21::set<int> s1({1, 2, 3});
  s21::set<int> s2({4, 5, 6});

  s1.swap(s2);

  ASSERT_EQ(3, s2.size());
  ASSERT_EQ(3, s1.size());
  ASSERT_TRUE(s2.contains(1));
  ASSERT_TRUE(s2.contains(2));
  ASSERT_TRUE(s2.contains(3));
  ASSERT_TRUE(s1.contains(4));
  ASSERT_TRUE(s1.contains(5));
  ASSERT_TRUE(s1.contains(6));
}

TEST(SetTest, Clear) {
  s21::set<int> s({1, 2, 3});
  ASSERT_FALSE(s.empty());
  s.clear();
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(0, s.size());
}

//-------------------MULTISET-----------------------------------------
TEST(MultisetTest, SizeTest) {
  s21::multiset<int> s1{5, 10, 5, 20, 5};
  ASSERT_EQ(s1.size(), 5);
}

TEST(MultisetTest, IteratorTest) {
  s21::multiset<int> s1{5, 10, 5, 20, 5};
  auto iter = s1.begin();
  ASSERT_EQ(*(iter), 5);
  ++iter;
  ASSERT_EQ(*(iter), 5);
  ++iter;
  ASSERT_EQ(*(iter), 5);
  ++iter;
  ASSERT_EQ(*(iter), 10);
  ++iter;
  ASSERT_EQ(*(iter), 20);
}

TEST(MultisetTest, EmptyTest) {
  s21::multiset<int> s1;
  ASSERT_TRUE(s1.empty());
}

TEST(MultisetTest, InsertTest) {
  s21::multiset<int> s1;
  auto pair1 = s1.insert(5);
  auto pair2 = s1.insert(5);
  auto pair3 = s1.insert(10);
  auto pair4 = s1.insert(15);
  auto pair5 = s1.insert(20);
  ASSERT_EQ(pair1.second, true);
  ASSERT_EQ(pair2.second, true);
  ASSERT_EQ(pair3.second, true);
  ASSERT_EQ(pair4.second, true);
  ASSERT_EQ(pair5.second, true);
  ASSERT_EQ(s1.size(), 5);
  auto iter = s1.begin();
  ASSERT_EQ(*(iter), 5);
  ++iter;
  ASSERT_EQ(*(iter), 5);
  ++iter;
  ASSERT_EQ(*(iter), 10);
  ++iter;
  ASSERT_EQ(*(iter), 15);
  ++iter;
  ASSERT_EQ(*(iter), 20);
}

TEST(MultisetTest, EraseTest) {
  s21::multiset<int> s1{5, 10, 5, 20, 5};
  auto iter = s1.find(10);
  s1.erase(iter);
  ASSERT_EQ(s1.size(), 4);
  iter = s1.begin();
  ASSERT_EQ(*(iter), 5);
  ++iter;
  ASSERT_EQ(*(iter), 5);
  ++iter;
  ASSERT_EQ(*(iter), 5);
  ++iter;
  ASSERT_EQ(*(iter), 20);
}

TEST(MultisetTest, MergeTest) {
  s21::multiset<int> s1{5, 10, 15};
  s21::multiset<int> s2{15, 20, 25};
  s1.merge(s2);
  ASSERT_EQ(s1.size(), 6);
  ASSERT_TRUE(s2.empty());
  auto iter = s1.begin();
  ASSERT_EQ(*(iter), 5);
  ++iter;
  ASSERT_EQ(*(iter), 10);
  ++iter;
  ASSERT_EQ(*(iter), 15);
  ++iter;
  ASSERT_EQ(*(iter), 15);
  ++iter;
  ASSERT_EQ(*(iter), 20);
  ++iter;
  ASSERT_EQ(*(iter), 25);
}

TEST(MultisetTest, ContainsTest) {
  s21::multiset<int> s1{5, 10, 15};
  ASSERT_TRUE(s1.contains(10));
  ASSERT_FALSE(s1.contains(20));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
