#include "s21_matrix.h"

int s21_matrix_minor(matrix_t *A, matrix_t *result, int i, int j) {
  int check = 0;
  if (A->rows != A->columns || A->rows < 1) {
    if (A->rows < 1) {
      check = 1;
    } else {
      check = 2;
    }
  } else {
    int ki, kj, di, dj;
    di = 0;
    s21_create_matrix(A->rows - 1, A->rows - 1, result);
    for (ki = 0; ki < A->rows - 1; ki++) {
      if (ki == i) {
        di = 1;
      }
      dj = 0;
      for (kj = 0; kj < A->rows - 1; kj++) {
        if (kj == j) {
          dj = 1;
        }
        result->matrix[ki][kj] = A->matrix[ki + di][kj + dj];
      }
    }
  }
  return check;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int check = 0;
  if (A->rows != A->columns || A->rows <= 1) {
    if (A->rows <= 1) {
      check = 1;
    } else {
      check = 2;
    }
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    matrix_t temp;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_matrix_minor(A, &temp, i, j);
        double det;
        s21_determinant(&temp, &det);
        s21_remove_matrix(&temp);

        result->matrix[i][j] =
            (round(pow(-1.0, (double)i + j) * det * 1000000) / 1000000);
      }
    }
  }
  return check;
}
