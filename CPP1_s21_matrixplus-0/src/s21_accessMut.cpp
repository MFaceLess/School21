#include "s21_matrix_oop.h"

int& S21Matrix::get_rows() { return _rows; }

int& S21Matrix::get_cols() { return _cols; }

S21Matrix& S21Matrix::edit_rows(int rows) {
  S21Matrix copy(rows, this->_cols);
  int _rows_;
  if (rows < this->_rows) {
    _rows_ = rows;
  } else {
    _rows_ = this->_rows;
  }
  for (auto i = 0; i < _rows_; i++) {
    for (auto j = 0; j < this->_cols; j++) {
      copy._p[i][j] = this->_p[i][j];
    }
  }
  *this = copy;
  return *this;
}

S21Matrix& S21Matrix::edit_cols(int cols) {
  S21Matrix copy(this->_rows, cols);
  int _cols_;
  if (cols < this->_cols) {
    _cols_ = cols;
  } else {
    _cols_ = this->_cols;
  }
  for (auto i = 0; i < this->_rows; i++) {
    for (auto j = 0; j < _cols_; j++) {
      copy._p[i][j] = this->_p[i][j];
    }
  }
  *this = copy;
  return *this;
}
