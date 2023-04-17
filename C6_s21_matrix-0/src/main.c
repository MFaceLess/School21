#include "s21_matrix.h"

int main() {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(3, 3, &shit1);
  s21_create_matrix(3, 3, &shit2);

  shit1.matrix[0][0] = 2;
  shit1.matrix[0][1] = 5;
  shit1.matrix[0][2] = 7;
  shit1.matrix[1][0] = 6;
  shit1.matrix[1][1] = 3;
  shit1.matrix[1][2] = 4;
  shit1.matrix[2][0] = 5;
  shit1.matrix[2][1] = -2;
  shit1.matrix[2][2] = -3;

  s21_print_matrix(&shit1);

  matrix_t result;
  printf("Код выполнения = %d\n", s21_inverse_matrix(&shit1, &result));

  s21_print_matrix(&result);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  s21_remove_matrix(&result);
  return 0;
}