#include "s21_matrix_oop.h"

double S21Matrix::operator()(int rows, int cols) {
  if (rows >= _rows || cols >= _cols) {
    throw "Incorrect input, index is out of range";
  }
  return _p[rows][cols];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
  if (this == &o) {
    return *this;
  }
  if (this->_p) {
    for (int i = 0; i < this->_rows; i++) {
      if (this->_p[i]) {
        delete[] this->_p[i];
      }
    }
    delete[] this->_p;
  }
  _p = new double*[o._rows]();
  for (auto i = 0; i < o._rows; i++) {
    _p[i] = new double[o._cols]();
  }
  for (int i = 0; i < o._rows; i++) {
    for (int j = 0; j < o._cols; j++) {
      _p[i][j] = o._p[i][j];
    }
  }
  _rows = o._rows;
  _cols = o._cols;
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this == &other) {
    return *this;
  }
  if (this->_p) {
    for (int i = 0; i < _rows; i++) {
      if (_p[i]) {
        delete[] this->_p[i];
      }
    }
    delete[] this->_p;
  }
  _p = other._p;
  _rows = other._rows;
  _cols = other._cols;
  other._rows = 0;
  other._cols = 0;
  other._p = nullptr;
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) {
  // creating result matrix
  S21Matrix res = *this;
  res.SumMatrix(o);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) {
  S21Matrix res = *this;
  res.SubMatrix(o);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& o) {
  bool result = this->EqMatrix(o);
  return result;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
  this->SumMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
  this->SubMatrix(o);
  return *this;
}

S21Matrix operator*(double value, S21Matrix& mat) {
  S21Matrix result = mat;
  result.MulNumber(value);
  return result;
}

S21Matrix operator*(S21Matrix& matrix, double value) {
  S21Matrix result = matrix;
  result.MulNumber(value);
  return result;
}

S21Matrix S21Matrix::operator*(S21Matrix& o) {
  S21Matrix result = *this;
  result.MulMatrix(o);
  return result;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
  this->MulMatrix(o);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double value) {
  this->MulNumber(value);
  return *this;
}
