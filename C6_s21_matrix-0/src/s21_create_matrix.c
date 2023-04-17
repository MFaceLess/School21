#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int check = 0;
  if (rows <= 0 || columns <= 0) {
    check = 1;
  } else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix == NULL) {
      check = 1;
    } else {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          check = 1;
          break;
        }
      }
    }
  }
  return check;
}
