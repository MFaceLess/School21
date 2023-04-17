#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(TestGroupName, eq_operator) {
  S21Matrix mat1(5, 5);
  S21Matrix mat2(5, 5);
  ASSERT_TRUE(mat1 == mat2);
}

TEST(TestGroupName, EqMatrix1) {
  S21Matrix mat1(5, 5);
  S21Matrix mat2(5, 6);
  bool res = mat2.EqMatrix(mat1);
  ASSERT_FALSE(res);
}

TEST(TestGroupName, EqMatrix2) {
  S21Matrix mat1(5, 5);
  S21Matrix mat2(5, 5);
  bool res = mat2.EqMatrix(mat1);
  ASSERT_TRUE(res);
}

TEST(TestGroupName, constructor) {
  S21Matrix mat;
  mat.setValue(0, 0, 2);
  mat.setValue(0, 1, 5);
  mat.setValue(0, 2, 7);
  mat.setValue(1, 0, 6);
  mat.setValue(1, 1, 3);
  mat.setValue(1, 2, 4);
  mat.setValue(2, 0, 5);
  mat.setValue(2, 1, -2);
  mat.setValue(2, 2, -3);

  S21Matrix res;
  res.setValue(0, 0, 1);
  res.setValue(0, 1, -1);
  res.setValue(0, 2, 1);
  res.setValue(1, 0, -38);
  res.setValue(1, 1, 41);
  res.setValue(1, 2, -34);
  res.setValue(2, 0, 27);
  res.setValue(2, 1, -29);
  res.setValue(2, 2, 24);

  S21Matrix score = std::move(mat.InverseMatrix());
  ASSERT_TRUE(res == score);
}

TEST(TestGroupName, operations) {
  S21Matrix mat1(5, 5);
  S21Matrix mat2(5, 5);
  mat2.setValue(0, 0, 1);
  mat2.setValue(0, 1, 1);
  mat2.setValue(0, 2, 1);
  mat2.setValue(1, 0, 1);
  mat2.setValue(1, 1, 1);
  mat2.setValue(1, 2, 1);
  mat2.setValue(2, 0, 1);
  mat2.setValue(2, 1, 1);
  mat2.setValue(2, 2, 1);
  mat1 += mat2;
  mat1 *= 5;
  mat1 -= mat2;
  mat1 *= mat2;
  S21Matrix check(5, 5);
  check.setValue(0, 0, 4);
  check.setValue(0, 1, 4);
  check.setValue(0, 2, 4);
  check.setValue(1, 0, 4);
  check.setValue(1, 1, 4);
  check.setValue(1, 2, 4);
  check.setValue(2, 0, 4);
  check.setValue(2, 1, 4);
  check.setValue(2, 2, 4);
  ASSERT_TRUE(check == mat1);
}

TEST(TestGroupName, function1) {
  S21Matrix mat1(5, 5);
  S21Matrix mat2(5, 6);
  try {
    mat1 += mat2;
  } catch (const char* err) {
    std::cout << err << std::endl;
  }
  ASSERT_TRUE(mat1 == mat1);
}

TEST(TestGroupName, function2) {
  S21Matrix A;
  A.setValue(0, 0, 5);
  A.setValue(0, 1, 2.56);
  A.setValue(0, 2, 3.23);
  A.setValue(1, 0, 12.4);
  A.setValue(1, 1, 5.5);
  A.setValue(1, 2, 6.521);
  A.setValue(2, 0, 106.7);
  A.setValue(2, 1, 0);
  A.setValue(2, 2, 9.12);
  double det = A.Determinant();
  ASSERT_TRUE(det + 153.006588 < 10E-5);
}

TEST(TestGroupName, function3) {
  S21Matrix mat;
  mat.setValue(0, 0, 2);
  mat.setValue(0, 1, 5);
  mat.setValue(0, 2, 7);
  mat.setValue(1, 0, 6);
  mat.setValue(1, 1, 3);
  mat.setValue(1, 2, 4);
  mat.setValue(2, 0, 5);
  mat.setValue(2, 1, -2);
  mat.setValue(2, 2, -3);
  S21Matrix check = mat;
  check.setValue(0, 0, -1);
  check.setValue(0, 1, 38);
  check.setValue(0, 2, -27);
  check.setValue(1, 0, 1);
  check.setValue(1, 1, -41);
  check.setValue(1, 2, 29);
  check.setValue(2, 0, -1);
  check.setValue(2, 1, 34);
  check.setValue(2, 2, -24);
  ASSERT_TRUE(check == std::move(mat.CalcComplements()));
}

TEST(TestGroupName, function4) {
  S21Matrix mat;
  mat.setValue(0, 0, 2);
  mat.setValue(0, 1, 5);
  mat.setValue(0, 2, 7);
  mat.setValue(1, 0, 6);
  mat.setValue(1, 1, 3);
  mat.setValue(1, 2, 4);
  mat.setValue(2, 0, 5);
  mat.setValue(2, 1, -2);
  mat.setValue(2, 2, -3);
  S21Matrix check = mat;
  check.setValue(0, 0, 2);
  check.setValue(0, 1, 6);
  check.setValue(0, 2, 5);
  check.setValue(1, 0, 5);
  check.setValue(1, 1, 3);
  check.setValue(1, 2, -2);
  check.setValue(2, 0, 7);
  check.setValue(2, 1, 4);
  check.setValue(2, 2, -3);
  ASSERT_TRUE(check == std::move(mat.Transpose()));
}

TEST(TestGroupName, operator5) {
  S21Matrix mat;
  mat.setValue(0, 0, 2);
  mat.setValue(0, 1, 5);
  mat.setValue(0, 2, 7);
  mat.setValue(1, 0, 6);
  mat.setValue(1, 1, 3);
  mat.setValue(1, 2, 4);
  mat.setValue(2, 0, 5);
  mat.setValue(2, 1, -2);
  mat.setValue(2, 2, -3);
  ASSERT_TRUE(mat(0, 0) == 2);
}

TEST(TestGroupName, get_row) {
  S21Matrix mat;
  mat.setValue(0, 0, 2);
  mat.setValue(0, 1, 5);
  mat.setValue(0, 2, 7);
  mat.setValue(1, 0, 6);
  mat.setValue(1, 1, 3);
  mat.setValue(1, 2, 4);
  mat.setValue(2, 0, 5);
  mat.setValue(2, 1, -2);
  mat.setValue(2, 2, -3);
  ASSERT_TRUE(mat.get_rows() == 3);
}

TEST(TestGroupName, get_col) {
  S21Matrix mat;
  mat.setValue(0, 0, 2);
  mat.setValue(0, 1, 5);
  mat.setValue(0, 2, 7);
  mat.setValue(1, 0, 6);
  mat.setValue(1, 1, 3);
  mat.setValue(1, 2, 4);
  mat.setValue(2, 0, 5);
  mat.setValue(2, 1, -2);
  mat.setValue(2, 2, -3);
  ASSERT_TRUE(mat.get_cols() == 3);
}

TEST(TestGroupName, edit_row) {
  S21Matrix mat;
  mat.setValue(0, 0, 2);
  mat.setValue(0, 1, 5);
  mat.setValue(0, 2, 7);
  mat.setValue(1, 0, 6);
  mat.setValue(1, 1, 3);
  mat.setValue(1, 2, 4);
  mat.setValue(2, 0, 5);
  mat.setValue(2, 1, -2);
  mat.setValue(2, 2, -3);
  mat.edit_rows(1);
  S21Matrix check(1, 3);
  check.setValue(0, 0, 2);
  check.setValue(0, 1, 5);
  check.setValue(0, 2, 7);
  ASSERT_TRUE(mat == check);
}

TEST(TestGroupName, edit_col) {
  S21Matrix mat;
  mat.setValue(0, 0, 2);
  mat.setValue(0, 1, 5);
  mat.setValue(0, 2, 7);
  mat.setValue(1, 0, 6);
  mat.setValue(1, 1, 3);
  mat.setValue(1, 2, 4);
  mat.setValue(2, 0, 5);
  mat.setValue(2, 1, -2);
  mat.setValue(2, 2, -3);
  mat.edit_cols(1);
  S21Matrix check(3, 1);
  check.setValue(0, 0, 2);
  check.setValue(1, 0, 6);
  check.setValue(2, 0, 5);
  ASSERT_TRUE(mat == check);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
