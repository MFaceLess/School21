#include "s21_matrix_oop.h"

void S21Matrix::print_Matrix() {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      std::cout << _p[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void S21Matrix::setValue(int row, int col, double val) {
  if (row >= this->_rows || col >= this->_cols) {
    throw "Incorrect input, index is out of range";
  }
  this->_p[row][col] = val;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool result = true;
  if (this->_rows != other._rows || this->_cols != other._cols) {
    result = false;
  } else {
    for (auto i = 0; i < other._rows; i++) {
      for (auto j = 0; j < other._cols; j++) {
        if (this->_p[i][j] - other._p[i][j] > EPS) {
          result = false;
          break;
        }
      }
      if (!result) {
        break;
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  // exception throwing example
  if (_rows != other._rows || _cols != other._cols) {
    throw "Incorrect input, matrices should have the same size";
  }
  for (auto i = 0; i < this->_rows; i++) {
    for (auto j = 0; j < this->_cols; j++) {
      this->_p[i][j] = this->_p[i][j] + other._p[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  // exception throwing example
  if (_rows != other._rows || _cols != other._cols) {
    throw "Incorrect input, matrices should have the same size";
  }
  for (auto i = 0; i < this->_rows; i++) {
    for (auto j = 0; j < this->_cols; j++) {
      this->_p[i][j] = this->_p[i][j] - other._p[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < this->_rows; i++) {
    for (auto j = 0; j < this->_cols; j++) {
      this->_p[i][j] = this->_p[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->_cols != other._rows) {
    throw "_cols != _rows";
  }
  S21Matrix temp_matrix = *this;
  for (auto i = 0; i < this->_rows; i++) {
    for (auto j = 0; j < other._cols; j++) {
      this->_p[i][j] = 0;
      for (auto k = 0; k < this->_cols; k++)
        this->_p[i][j] += temp_matrix._p[i][k] * other._p[k][j];
    }
  }
}

double S21Matrix::Determinant() {
  if (this->_rows != this->_cols) {
    throw "Error: The matrix is not a square";
  }
  if (this->_rows < 1) {
    throw "Error: _rows and _cols < 1";
  }
  double result;
  S21Matrix copy1 = *this;
  S21Matrix copy2 = *this;

  unsigned int swapCount = triangulation(copy1);
  double determinant = 1;

  if (swapCount % 2 == 1) {
    determinant = -1;
  }
  for (int i = 0; i < this->_rows; ++i) {
    determinant *= copy1._p[i][i];
  }
  if (isnan(determinant)) {
    result = matrixDet(copy2);
  } else {
    result = determinant;
  }
  return result;
}

int S21Matrix::triangulation(S21Matrix& A) {
  int n = A._rows;
  unsigned int swapCount = 0;

  const int num_cols = A._cols;
  for (int i = 0; i < n - 1; ++i) {
    int imax = col_max(A, i);
    if (i != imax) {
      double* temp = A._p[i];
      A._p[i] = A._p[imax];
      A._p[imax] = temp;
      ++swapCount;
    }
    for (int j = i + 1; j < n; ++j) {
      double mul = -(A._p[j][i]) / (A._p[i][i]);
      for (int k = i; k < num_cols; ++k) {
        A._p[j][k] += A._p[i][k] * mul;
      }
    }
  }
  return swapCount;
}

int S21Matrix::col_max(S21Matrix A, int col) {
  int n = A._rows;
  double max = fabs(A._p[col][col]);
  int maxPos = col;
  for (int i = col + 1; i < n; ++i) {
    double element = fabs(A._p[i][col]);
    if (element > max) {
      max = element;
      maxPos = i;
    }
  }
  return maxPos;
}

double S21Matrix::matrixDet(S21Matrix A) {
  double det = 0;
  // (-1)^(1+j) из формулы определителя
  int degree = 1;

  //Условие выхода из рекурсии
  if (A._rows == 1) {
    return A._p[0][0];
  }
  //Условие выхода из рекурсии
  else if (A._rows == 2) {
    return ((A._p[0][0]) * (A._p[1][1]) - (A._p[0][1]) * (A._p[1][0]));
  } else {
    //Матрица без строки и столбца
    S21Matrix newMatrix = S21Matrix(A._rows - 1, A._cols - 1);

    //Раскладываем по 0-ой строке, цикл бежит по столбцам
    for (auto j = 0; j < A._rows; j++) {
      //Удалить из матрицы i-ю строку и j-ый столбец
      //Результат в newMatrix
      s21_matrix_minor(A, newMatrix, 0, j);
      double temp = A._p[0][j];
      //Рекурсивный вызов
      //По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть
      //сумма из формулы) где minor_j - дополнительный минор элемента
      // matrix[0][j]
      // (напомню, что минор это определитель матрицы без 0-ой строки и j-го
      // столбца)
      det = det + (degree * temp * matrixDet(newMatrix));
      //"Накручиваем" степень множителя
      degree = -degree;
    }
  }
  return det;
}

void S21Matrix::s21_matrix_minor(S21Matrix A, S21Matrix& result, int i, int j) {
  int ki, kj, di, dj;
  di = 0;
  for (ki = 0; ki < A._rows - 1; ki++) {
    if (ki == i) {
      di = 1;
    }
    dj = 0;
    for (kj = 0; kj < A._rows - 1; kj++) {
      if (kj == j) {
        dj = 1;
      }
      result._p[ki][kj] = A._p[ki + di][kj + dj];
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result = S21Matrix(this->_cols, this->_rows);
  for (int i = 0; i < this->_rows; i++) {
    for (int j = 0; j < this->_cols; j++) {
      result._p[j][i] = this->_p[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->_rows != this->_cols) {
    throw "Error: The matrix is not a square";
  }
  if (this->_rows < 1) {
    throw "Error: _rows and _cols < 1";
  }
  S21Matrix copy = *this;
  S21Matrix result = S21Matrix(this->_rows, this->_cols);
  S21Matrix temp = S21Matrix(this->_rows - 1, this->_cols - 1);
  for (auto i = 0; i < this->_rows; i++) {
    for (auto j = 0; j < this->_cols; j++) {
      s21_matrix_minor(copy, temp, i, j);
      double det = temp.Determinant();
      result._p[i][j] =
          (round(pow(-1.0, (double)i + j) * det * 1000000) / 1000000);
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (this->Determinant() == 0) {
    throw "Determinant is null";
  }
  double det = this->Determinant();
  S21Matrix copy = *this;
  S21Matrix temp = std::move(copy.CalcComplements());
  S21Matrix transpon = std::move(temp.Transpose());
  transpon.MulNumber(1.0 / det);
  S21Matrix result = transpon;
  return result;
}
