#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int check = 0;
  if (A->rows != A->columns || A->rows <= 1) {
    if (A->rows <= 1) {
      check = 1;
    } else {
      check = 2;
    }
  } else {
    double det;
    matrix_t copy;
    s21_create_matrix(A->columns, A->rows, &copy);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        copy.matrix[i][j] = A->matrix[i][j];
      }
    }
    s21_determinant(A, &det);
    if (det == 0) {
      check = 2;
      s21_remove_matrix(&copy);
    } else {
      matrix_t temp;
      s21_calc_complements(&copy, &temp);
      matrix_t transpon;
      s21_transpose(&temp, &transpon);
      s21_mult_number(&transpon, 1.0 / det, result);

      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] =
              (round(result->matrix[i][j] * 1000000) / 1000000);
        }
      }

      s21_remove_matrix(&temp);
      s21_remove_matrix(&transpon);
      s21_remove_matrix(&copy);
    }
  }
  return check;
}
