#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  _rows = 3;
  _cols = 3;
  _p = new double*[_rows]();
  for (auto i = 0; i < _rows; i++) {
    _p[i] = new double[_cols]();
  }
}

S21Matrix::S21Matrix(int rows, int cols) : _rows(rows), _cols(cols) {
  _p = new double*[_rows]();
  for (auto i = 0; i < _rows; i++) {
    _p[i] = new double[_cols]();
  }
}

S21Matrix::S21Matrix(const S21Matrix& o) : _rows(o._rows), _cols(o._cols) {
  _p = new double*[o._rows]();
  for (auto i = 0; i < o._rows; i++) {
    _p[i] = new double[o._cols]();
  }
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      _p[i][j] = o._p[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& o) {
  _p = o._p;
  _rows = o._rows;
  _cols = o._cols;
  o._rows = 0;
  o._cols = 0;
  o._p = nullptr;
}

S21Matrix::~S21Matrix() {
  if (_p) {
    for (int i = 0; i < _rows; i++) {
      if (_p[i]) {
        delete[] _p[i];
      }
    }
    delete[] _p;
  }
}
