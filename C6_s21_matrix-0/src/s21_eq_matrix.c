#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int check = SUCCESS;
  if ((A->rows == B->rows) && (A->columns == B->columns)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (s21_floor((A->matrix)[i][j], 7) !=
            s21_floor((B->matrix)[i][j], 7)) {
          check = FAILURE;
          break;
        }
      }
    }
  } else {
    check = FAILURE;
  }
  return check;
}
