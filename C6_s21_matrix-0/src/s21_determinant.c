#include "s21_matrix.h"

int col_max(matrix_t *A, int col) {
  int n = A->rows;
  double max = fabs(A->matrix[col][col]);
  int maxPos = col;
  for (int i = col + 1; i < n; ++i) {
    double element = fabs(A->matrix[i][col]);
    if (element > max) {
      max = element;
      maxPos = i;
    }
  }
  return maxPos;
}

int triangulation(matrix_t *A) {
  int n = A->rows;
  unsigned int swapCount = 0;

  const int num_cols = A->columns;
  for (int i = 0; i < n - 1; ++i) {
    int imax = col_max(A, i);
    if (i != imax) {
      double *temp = A->matrix[i];
      A->matrix[i] = A->matrix[imax];
      A->matrix[imax] = temp;
      ++swapCount;
    }
    for (int j = i + 1; j < n; ++j) {
      double mul = -(A->matrix[j][i]) / (A->matrix[i][i]);
      for (int k = i; k < num_cols; ++k) {
        A->matrix[j][k] += A->matrix[i][k] * mul;
      }
    }
  }
  return swapCount;
}

int s21_determinant(matrix_t *A, double *result) {
  int check = 0;
  if (A->rows == A->columns && A->rows >= 1) {
    matrix_t copy;
    s21_create_matrix(A->rows, A->columns, &copy);
    for (int i = 0; i < copy.rows; i++) {
      for (int j = 0; j < copy.columns; j++) {
        copy.matrix[i][j] = A->matrix[i][j];
      }
    }
    unsigned int swapCount = triangulation(A);
    double determinant = 1;

    if (swapCount % 2 == 1) {
      determinant = -1;
    }
    for (int i = 0; i < A->rows; ++i) {
      determinant *= A->matrix[i][i];
    }
    if (isnan(determinant)) {
      *result = matrixDet(&copy);
    } else {
      *result = determinant;
    }
    s21_remove_matrix(&copy);
  } else {
    if (A->rows < 1) {
      check = 1;
    } else {
      check = 2;
    }
  }
  return check;
}

//Вычисление определителя матрицы разложение по первой строке (рекурсивный
//алгоритм)
double matrixDet(matrix_t *A) {
  double det = 0;
  // (-1)^(1+j) из формулы определителя
  int degree = 1;

  //Условие выхода из рекурсии
  if (A->rows == 1) {
    return A->matrix[0][0];
  }
  //Условие выхода из рекурсии
  else if (A->rows == 2) {
    return ((A->matrix[0][0]) * (A->matrix[1][1]) -
            (A->matrix[0][1]) * (A->matrix[1][0]));
  } else {
    //Матрица без строки и столбца
    matrix_t newMatrix;

    //Раскладываем по 0-ой строке, цикл бежит по столбцам
    for (int j = 0; j < A->rows; j++) {
      //Удалить из матрицы i-ю строку и j-ый столбец
      //Результат в newMatrix
      s21_matrix_minor(A, &newMatrix, 0, j);
      double temp = A->matrix[0][j];
      //Рекурсивный вызов
      //По формуле: сумма по j, (-1)^(1+j) * matrix[0][j] * minor_j (это и есть
      //сумма из формулы) где minor_j - дополнительный минор элемента
      // matrix[0][j]
      // (напомню, что минор это определитель матрицы без 0-ой строки и j-го
      // столбца)
      det = det + (degree * temp * matrixDet(&newMatrix));
      //"Накручиваем" степень множителя
      degree = -degree;
      //Чистим память на каждом шаге рекурсии
      s21_remove_matrix(&newMatrix);
    }
  }
  return det;
}
