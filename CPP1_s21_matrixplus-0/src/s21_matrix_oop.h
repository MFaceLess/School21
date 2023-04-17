#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <math.h>

#include <algorithm>
#include <iostream>

#define EPS 10E-8

class S21Matrix {
 private:
  // attributes
  int _rows, _cols;  // rows and columns attributes
  double** _p;       // pointer to the memory where the matrix will be allocated

 public:
  S21Matrix();                    // default constructor
  S21Matrix(int rows, int cols);  // parameterized constructor
  S21Matrix(const S21Matrix& o);  // copy cnstructor
  S21Matrix(S21Matrix&& o);       // move cnstructor
  ~S21Matrix();                   // destructor

  // some operators overloads
  S21Matrix& operator=(const S21Matrix& o);  // assignment operator overload
  S21Matrix& operator=(S21Matrix&& other);
  double operator()(int rows, int cols);  // index operator overload
  S21Matrix& operator+=(const S21Matrix& o);
  S21Matrix operator+(const S21Matrix& o);
  S21Matrix& operator-=(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o);
  bool operator==(const S21Matrix& o);
  S21Matrix operator*(S21Matrix& o);
  friend S21Matrix operator*(double value, S21Matrix& o);
  friend S21Matrix operator*(S21Matrix& o, double value);
  S21Matrix& operator*=(const S21Matrix& o);
  S21Matrix& operator*=(const double value);

  // some public methods
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix Transpose();
  S21Matrix InverseMatrix();

  //--------------Accessor and Mutator------------------------------
  int& get_rows();
  int& get_cols();
  S21Matrix& edit_rows(int rows);
  S21Matrix& edit_cols(int cols);
  //--------------Вывод матрицы--------------------------------------
  void print_Matrix();
  //--------------Установка значений---------------------------------
  void setValue(int row, int col, double val);
  //----------------Функции для детерменанта-------------------------
  int triangulation(S21Matrix& A);
  int col_max(S21Matrix A, int col);
  double matrixDet(S21Matrix A);
  void s21_matrix_minor(S21Matrix A, S21Matrix& result, int i, int j);
  //-----------------------------------------------------------------
};

#endif
