#include "check.h"
#include "s21_matrix.h"

#define OK 0
#define WRONG_MATRIX 1
#define CALCULATION_ERROR 2

#define SUCCESS 1
#define FAILURE 0

START_TEST(s21_create_matrix_1) {
  matrix_t shit1;
  int check = s21_create_matrix(5, 5, &shit1);
  s21_print_matrix(&shit1);
  s21_remove_matrix(&shit1);

  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_create_matrix_2) {
  matrix_t shit1;
  int check = s21_create_matrix(-10, 0, &shit1);
  ck_assert_int_eq(check, WRONG_MATRIX);
}
END_TEST

START_TEST(s21_eq_matrix_1) {
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
  s21_print_matrix(&shit2);

  int check = s21_eq_matrix(&shit1, &shit2);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);

  ck_assert_int_eq(check, FAILURE);
}
END_TEST

START_TEST(s21_eq_matrix_2) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(3, 3, &shit1);
  s21_create_matrix(3, 3, &shit2);

  s21_print_matrix(&shit1);
  s21_print_matrix(&shit2);

  int check = s21_eq_matrix(&shit1, &shit2);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);

  ck_assert_int_eq(check, SUCCESS);
}
END_TEST

START_TEST(s21_sum_matrix_1) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(2, 3, &shit1);
  s21_create_matrix(2, 2, &shit2);

  matrix_t result;
  int check = s21_sum_matrix(&shit1, &shit2, &result);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);

  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_sum_matrix_2) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(2, 2, &shit1);
  s21_create_matrix(2, 2, &shit2);

  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 1;
  shit1.matrix[1][0] = 1;
  shit1.matrix[1][1] = 1;

  shit2.matrix[0][0] = 1;
  shit2.matrix[0][1] = 1;
  shit2.matrix[1][0] = 1;
  shit2.matrix[1][1] = 1;

  matrix_t sum;
  s21_create_matrix(2, 2, &sum);
  sum.matrix[0][0] = 2;
  sum.matrix[0][1] = 2;
  sum.matrix[1][0] = 2;
  sum.matrix[1][1] = 2;

  matrix_t result;
  int check = s21_sum_matrix(&shit1, &shit2, &result);

  int check2 = s21_eq_matrix(&sum, &result);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  s21_remove_matrix(&sum);
  s21_remove_matrix(&result);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_sub_matrix_1) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(2, 3, &shit1);
  s21_create_matrix(2, 2, &shit2);

  matrix_t result;
  int check = s21_sub_matrix(&shit1, &shit2, &result);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);

  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_sub_matrix_2) {
  matrix_t shit1;
  matrix_t shit2;
  s21_create_matrix(2, 2, &shit1);
  s21_create_matrix(2, 2, &shit2);

  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 1;
  shit1.matrix[1][0] = 1;
  shit1.matrix[1][1] = 1;

  shit2.matrix[0][0] = 1;
  shit2.matrix[0][1] = 1;
  shit2.matrix[1][0] = 1;
  shit2.matrix[1][1] = 1;

  matrix_t sum;
  s21_create_matrix(2, 2, &sum);
  sum.matrix[0][0] = 0;
  sum.matrix[0][1] = 0;
  sum.matrix[1][0] = 0;
  sum.matrix[1][1] = 0;

  matrix_t result;
  int check = s21_sub_matrix(&shit1, &shit2, &result);

  int check2 = s21_eq_matrix(&sum, &result);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  s21_remove_matrix(&sum);
  s21_remove_matrix(&result);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_mult_number_1) {
  matrix_t shit1;
  s21_create_matrix(3, 3, &shit1);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 2;
  shit1.matrix[0][2] = 3;
  shit1.matrix[1][0] = 0;
  shit1.matrix[1][1] = 4;
  shit1.matrix[1][2] = 2;
  shit1.matrix[2][0] = 2;
  shit1.matrix[2][1] = 3;
  shit1.matrix[2][2] = 4;

  double A = 2;

  matrix_t res;
  s21_create_matrix(3, 3, &res);
  res.matrix[0][0] = 2;
  res.matrix[0][1] = 4;
  res.matrix[0][2] = 6;
  res.matrix[1][0] = 0;
  res.matrix[1][1] = 8;
  res.matrix[1][2] = 4;
  res.matrix[2][0] = 4;
  res.matrix[2][1] = 6;
  res.matrix[2][2] = 8;

  matrix_t result;
  s21_mult_number(&shit1, A, &result);
  int check = s21_eq_matrix(&result, &res);
  s21_remove_matrix(&shit1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res);

  ck_assert_int_eq(check, SUCCESS);
}
END_TEST

START_TEST(s21_mult_matrix_1) {
  matrix_t shit1;
  matrix_t shit2;

  s21_create_matrix(2, 2, &shit1);
  s21_create_matrix(3, 2, &shit2);

  matrix_t result;
  int check = s21_mult_matrix(&shit1, &shit2, &result);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_mult_matrix_2) {
  matrix_t shit1;
  matrix_t shit2;

  s21_create_matrix(3, 2, &shit1);
  s21_create_matrix(2, 3, &shit2);

  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 4;
  shit1.matrix[1][0] = 2;
  shit1.matrix[1][1] = 5;
  shit1.matrix[2][0] = 3;
  shit1.matrix[2][1] = 6;

  shit2.matrix[0][0] = 1;
  shit2.matrix[0][1] = -1;
  shit2.matrix[0][2] = 1;
  shit2.matrix[1][0] = 2;
  shit2.matrix[1][1] = 3;
  shit2.matrix[1][2] = 4;

  matrix_t res;
  s21_create_matrix(3, 3, &res);
  res.matrix[0][0] = 9;
  res.matrix[0][1] = 11;
  res.matrix[0][2] = 17;
  res.matrix[1][0] = 12;
  res.matrix[1][1] = 13;
  res.matrix[1][2] = 22;
  res.matrix[2][0] = 15;
  res.matrix[2][1] = 15;
  res.matrix[2][2] = 27;

  matrix_t result;
  int check = s21_mult_matrix(&shit1, &shit2, &result);
  int check2 = s21_eq_matrix(&res, &result);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&shit2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&result);
  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_transpose_1) {
  matrix_t shit1;
  s21_create_matrix(3, 2, &shit1);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 4;
  shit1.matrix[1][0] = 2;
  shit1.matrix[1][1] = 5;
  shit1.matrix[2][0] = 3;
  shit1.matrix[2][1] = 6;

  matrix_t res;
  s21_create_matrix(2, 3, &res);
  res.matrix[0][0] = 1;
  res.matrix[0][1] = 2;
  res.matrix[0][2] = 3;
  res.matrix[1][0] = 4;
  res.matrix[1][1] = 5;
  res.matrix[1][2] = 6;

  matrix_t result;
  int check = s21_transpose(&shit1, &result);

  int check2 = s21_eq_matrix(&res, &result);

  s21_remove_matrix(&shit1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_1) {
  matrix_t shit1;
  s21_create_matrix(3, 3, &shit1);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 2;
  shit1.matrix[0][2] = 3;
  shit1.matrix[1][0] = 0;
  shit1.matrix[1][1] = 4;
  shit1.matrix[1][2] = 2;
  shit1.matrix[2][0] = 5;
  shit1.matrix[2][1] = 2;
  shit1.matrix[2][2] = 1;

  matrix_t for_check;
  s21_create_matrix(3, 3, &for_check);
  for_check.matrix[0][0] = 0;
  for_check.matrix[0][1] = 10;
  for_check.matrix[0][2] = -20;
  for_check.matrix[1][0] = 4;
  for_check.matrix[1][1] = -14;
  for_check.matrix[1][2] = 8;
  for_check.matrix[2][0] = -8;
  for_check.matrix[2][1] = -2;
  for_check.matrix[2][2] = 4;

  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);

  int check2 = s21_eq_matrix(&for_check, &result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_2) {
  matrix_t A;
  s21_create_matrix(3, 1, &A);

  matrix_t result;
  int check = s21_calc_complements(&A, &result);

  s21_remove_matrix(&A);
  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_determinant_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  double result;
  int check = s21_determinant(&A, &result);

  s21_remove_matrix(&A);
  ck_assert_int_eq((result == 0), OK);
}
END_TEST

START_TEST(s21_determinant_2) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 0;

  double result;
  int check = s21_determinant(&A, &result);

  s21_remove_matrix(&A);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_inverse_matrix_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  matrix_t B;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = -38;
  B.matrix[1][1] = 41;
  B.matrix[1][2] = -34;
  B.matrix[2][0] = 27;
  B.matrix[2][1] = -29;
  B.matrix[2][2] = 24;

  matrix_t result;
  int check = s21_inverse_matrix(&A, &result);
  int check2 = s21_eq_matrix(&result, &B);

  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      if (s21_floor((B.matrix)[i][j], 7) !=
          s21_floor((result.matrix)[i][j], 7)) {
        // printf("correct %.8f\n", s21_floor((B.matrix)[i][j], 7));
        // printf("not correct %.8f\n", s21_floor((result.matrix)[i][j], 7));
      }
    }
  }

  s21_print_matrix(&result);

  s21_print_matrix(&B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_inverse_matrix_2) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 0;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 0;

  matrix_t result;
  int check = s21_inverse_matrix(&A, &result);

  s21_remove_matrix(&A);
  ck_assert_int_eq(check, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_calc_complements_3) {
  matrix_t shit1;
  s21_create_matrix(3, 3, &shit1);
  shit1.matrix[0][0] = 1;
  shit1.matrix[0][1] = 2;
  shit1.matrix[0][2] = 4;
  shit1.matrix[1][0] = 3;
  shit1.matrix[1][1] = 3;
  shit1.matrix[1][2] = 5;
  shit1.matrix[2][0] = 2;
  shit1.matrix[2][1] = 4;
  shit1.matrix[2][2] = 4;

  matrix_t for_check;
  s21_create_matrix(3, 3, &for_check);
  for_check.matrix[0][0] = -8;
  for_check.matrix[0][1] = -2;
  for_check.matrix[0][2] = 6;
  for_check.matrix[1][0] = 8;
  for_check.matrix[1][1] = -4;
  for_check.matrix[1][2] = 0;
  for_check.matrix[2][0] = -2;
  for_check.matrix[2][1] = 7;
  for_check.matrix[2][2] = -3;

  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);

  int check2 = s21_eq_matrix(&for_check, &result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_4) {
  matrix_t shit1;
  s21_create_matrix(4, 4, &shit1);
  shit1.matrix[0][0] = 5;
  shit1.matrix[0][1] = 1;
  shit1.matrix[0][2] = 1;
  shit1.matrix[0][3] = 1;
  shit1.matrix[1][0] = 1;
  shit1.matrix[1][1] = 1;
  shit1.matrix[1][2] = 2;
  shit1.matrix[1][3] = 1;
  shit1.matrix[2][0] = 1;
  shit1.matrix[2][1] = 19;
  shit1.matrix[2][2] = 3;
  shit1.matrix[2][3] = 1;
  shit1.matrix[3][0] = 27;
  shit1.matrix[3][1] = 1;
  shit1.matrix[3][2] = 1;
  shit1.matrix[3][3] = 5;

  matrix_t for_check;
  s21_create_matrix(4, 4, &for_check);
  for_check.matrix[0][0] = -158;
  for_check.matrix[0][1] = 22;
  for_check.matrix[0][2] = -396;
  for_check.matrix[0][3] = 928;
  for_check.matrix[1][0] = 64;
  for_check.matrix[1][1] = 12;
  for_check.matrix[1][2] = 20;
  for_check.matrix[1][3] = -352;
  for_check.matrix[2][0] = 4;
  for_check.matrix[2][1] = -14;
  for_check.matrix[2][2] = 16;
  for_check.matrix[2][3] = -22;
  for_check.matrix[3][0] = 18;
  for_check.matrix[3][1] = -4;
  for_check.matrix[3][2] = 72;
  for_check.matrix[3][3] = -158;

  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);

  int check2 = s21_eq_matrix(&for_check, &result);

  // for (int i = 0; i < for_check.rows; i++) {
  //   for (int j = 0; j < for_check.columns; j++) {
  //     if (s21_floor((for_check.matrix)[i][j], 7) !=
  //         s21_floor((result.matrix)[i][j], 7)) {
  //           double temp = s21_floor((result.matrix)[i][j], 8) -
  //           (int)s21_floor((result.matrix)[i][j], 8); printf("shit %d\n",
  //           (fabs(fabs(temp) - 0.99999999) < EPS));
  //     }
  //   }
  // }

  s21_print_matrix(&result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_5) {
  matrix_t shit1;
  s21_create_matrix(3, 3, &shit1);
  shit1.matrix[0][0] = -215.5;
  shit1.matrix[0][1] = -23.3;
  shit1.matrix[0][2] = 4;
  shit1.matrix[1][0] = 12.2;
  shit1.matrix[1][1] = 23.3;
  shit1.matrix[1][2] = 32.2;
  shit1.matrix[2][0] = 5;
  shit1.matrix[2][1] = 1;
  shit1.matrix[2][2] = -1.25;

  matrix_t for_check;
  s21_create_matrix(3, 3, &for_check);
  for_check.matrix[0][0] = -61.325;
  for_check.matrix[0][1] = 176.25;
  for_check.matrix[0][2] = -104.3;
  for_check.matrix[1][0] = -25.125;
  for_check.matrix[1][1] = 249.375;
  for_check.matrix[1][2] = 99;
  for_check.matrix[2][0] = -843.46;
  for_check.matrix[2][1] = 6987.9;
  for_check.matrix[2][2] = -4736.89;

  s21_print_matrix(&shit1);

  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);

  int check2 = s21_eq_matrix(&for_check, &result);

  s21_print_matrix(&result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_6) {
  matrix_t shit1;
  s21_create_matrix(2, 2, &shit1);
  shit1.matrix[0][0] = -12551.1;
  shit1.matrix[0][1] = 1035.5;
  shit1.matrix[1][0] = 124.5151;
  shit1.matrix[1][1] = 0;

  matrix_t for_check;
  s21_create_matrix(2, 2, &for_check);
  for_check.matrix[0][0] = 0;
  for_check.matrix[0][1] = -124.5151;
  for_check.matrix[1][0] = -1035.5;
  for_check.matrix[1][1] = -12551.1;

  s21_print_matrix(&shit1);

  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);

  int check2 = s21_eq_matrix(&for_check, &result);

  s21_print_matrix(&result);

  s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_calc_complements_7) {
  matrix_t shit1;
  s21_create_matrix(1, 3, &shit1);
  shit1.matrix[0][0] = -12551.1;
  shit1.matrix[0][1] = 1035.5;
  shit1.matrix[0][2] = 124.5151;

  matrix_t for_check;
  s21_create_matrix(2, 2, &for_check);
  for_check.matrix[0][0] = 0;
  for_check.matrix[0][1] = -124.5151;
  for_check.matrix[1][0] = -1035.5;
  for_check.matrix[1][1] = -12551.1;

  s21_print_matrix(&shit1);

  matrix_t result;
  int check = s21_calc_complements(&shit1, &result);

  // int check2 = s21_eq_matrix(&for_check, &result);

  // s21_print_matrix(&result);

  // s21_remove_matrix(&result);
  s21_remove_matrix(&for_check);
  s21_remove_matrix(&shit1);

  // ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, WRONG_MATRIX);
}
END_TEST

START_TEST(s21_calc_complements_8) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  matrix_t B;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = -1;
  B.matrix[0][1] = 38;
  B.matrix[0][2] = -27;
  B.matrix[1][0] = 1;
  B.matrix[1][1] = -41;
  B.matrix[1][2] = 29;
  B.matrix[2][0] = -1;
  B.matrix[2][1] = 34;
  B.matrix[2][2] = -24;

  matrix_t result;
  int check = s21_calc_complements(&A, &result);
  int check2 = s21_eq_matrix(&result, &B);

  printf("RESULT!!!!!\n");
  s21_print_matrix(&result);

  s21_print_matrix(&B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

START_TEST(s21_inverse_matrix_3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 3;

  matrix_t B;
  s21_create_matrix(3, 3, &B);
  B.matrix[0][0] = 2;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 0;
  B.matrix[1][0] = -1;
  B.matrix[1][1] = 2;
  B.matrix[1][2] = -1;
  B.matrix[2][0] = 0;
  B.matrix[2][1] = -1;
  B.matrix[2][2] = 1;

  matrix_t result;
  int check = s21_inverse_matrix(&A, &result);
  int check2 = s21_eq_matrix(&result, &B);

  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      if (s21_floor((B.matrix)[i][j], 7) !=
          s21_floor((result.matrix)[i][j], 7)) {
        // printf("correct %.8f\n", s21_floor((B.matrix)[i][j], 7));
        // printf("not correct %.8f\n", s21_floor((result.matrix)[i][j], 7));
      }
    }
  }

  s21_print_matrix(&result);

  s21_print_matrix(&B);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);

  ck_assert_int_eq(check2, SUCCESS);
  ck_assert_int_eq(check, OK);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Check");

  TCase *tc_create_matrix_1;
  tc_create_matrix_1 = tcase_create("s21_create_matrix_1");
  suite_add_tcase(s, tc_create_matrix_1);
  tcase_add_test(tc_create_matrix_1, s21_create_matrix_1);

  TCase *tc_create_matrix_2;
  tc_create_matrix_2 = tcase_create("s21_create_matrix_2");
  suite_add_tcase(s, tc_create_matrix_2);
  tcase_add_test(tc_create_matrix_2, s21_create_matrix_2);

  TCase *tc_eq_matrix_1;
  tc_eq_matrix_1 = tcase_create("s21_eq_matrix_1");
  suite_add_tcase(s, tc_eq_matrix_1);
  tcase_add_test(tc_eq_matrix_1, s21_eq_matrix_1);

  TCase *tc_eq_matrix_2;
  tc_eq_matrix_2 = tcase_create("s21_eq_matrix_2");
  suite_add_tcase(s, tc_eq_matrix_2);
  tcase_add_test(tc_eq_matrix_2, s21_eq_matrix_2);

  TCase *tc_sum_matrix_1;
  tc_sum_matrix_1 = tcase_create("s21_sum_matrix_1");
  suite_add_tcase(s, tc_sum_matrix_1);
  tcase_add_test(tc_sum_matrix_1, s21_sum_matrix_1);

  TCase *tc_sum_matrix_2;
  tc_sum_matrix_2 = tcase_create("s21_sum_matrix_2");
  suite_add_tcase(s, tc_sum_matrix_2);
  tcase_add_test(tc_sum_matrix_2, s21_sum_matrix_2);

  TCase *tc_sub_matrix_1;
  tc_sub_matrix_1 = tcase_create("s21_sub_matrix_1");
  suite_add_tcase(s, tc_sub_matrix_1);
  tcase_add_test(tc_sub_matrix_1, s21_sub_matrix_1);

  TCase *tc_sub_matrix_2;
  tc_sub_matrix_2 = tcase_create("s21_sub_matrix_2");
  suite_add_tcase(s, tc_sub_matrix_2);
  tcase_add_test(tc_sub_matrix_2, s21_sub_matrix_2);

  TCase *tc_mult_number_1;
  tc_mult_number_1 = tcase_create("s21_mult_number_1");
  suite_add_tcase(s, tc_mult_number_1);
  tcase_add_test(tc_mult_number_1, s21_mult_number_1);

  TCase *tc_mult_matrix_1;
  tc_mult_matrix_1 = tcase_create("s21_mult_matrix_1");
  suite_add_tcase(s, tc_mult_matrix_1);
  tcase_add_test(tc_mult_matrix_1, s21_mult_matrix_1);

  TCase *tc_mult_matrix_2;
  tc_mult_matrix_2 = tcase_create("s21_mult_matrix_2");
  suite_add_tcase(s, tc_mult_matrix_2);
  tcase_add_test(tc_mult_matrix_2, s21_mult_matrix_2);

  TCase *tc_transpose_1;
  tc_transpose_1 = tcase_create("s21_transpose_1");
  suite_add_tcase(s, tc_transpose_1);
  tcase_add_test(tc_transpose_1, s21_transpose_1);

  TCase *tc_calc_complements_1;
  tc_calc_complements_1 = tcase_create("s21_calc_complements_1");
  suite_add_tcase(s, tc_calc_complements_1);
  tcase_add_test(tc_calc_complements_1, s21_calc_complements_1);

  TCase *tc_calc_complements_2;
  tc_calc_complements_2 = tcase_create("s21_calc_complements_2");
  suite_add_tcase(s, tc_calc_complements_2);
  tcase_add_test(tc_calc_complements_2, s21_calc_complements_2);

  TCase *tc_calc_complements_3;
  tc_calc_complements_3 = tcase_create("s21_calc_complements_3");
  suite_add_tcase(s, tc_calc_complements_3);
  tcase_add_test(tc_calc_complements_3, s21_calc_complements_3);

  TCase *tc_calc_complements_4;
  tc_calc_complements_4 = tcase_create("s21_calc_complements_4");
  suite_add_tcase(s, tc_calc_complements_4);
  tcase_add_test(tc_calc_complements_4, s21_calc_complements_4);

  TCase *tc_calc_complements_5;
  tc_calc_complements_5 = tcase_create("s21_calc_complements_5");
  suite_add_tcase(s, tc_calc_complements_5);
  tcase_add_test(tc_calc_complements_5, s21_calc_complements_5);

  TCase *tc_calc_complements_6;
  tc_calc_complements_6 = tcase_create("s21_calc_complements_6");
  suite_add_tcase(s, tc_calc_complements_6);
  tcase_add_test(tc_calc_complements_6, s21_calc_complements_6);

  TCase *tc_calc_complements_7;
  tc_calc_complements_7 = tcase_create("s21_calc_complements_7");
  suite_add_tcase(s, tc_calc_complements_7);
  tcase_add_test(tc_calc_complements_7, s21_calc_complements_7);

  TCase *tc_calc_complements_8;
  tc_calc_complements_8 = tcase_create("s21_calc_complements_8");
  suite_add_tcase(s, tc_calc_complements_8);
  tcase_add_test(tc_calc_complements_8, s21_calc_complements_8);

  TCase *tc_determinant_1;
  tc_determinant_1 = tcase_create("s21_determinant_1");
  suite_add_tcase(s, tc_determinant_1);
  tcase_add_test(tc_determinant_1, s21_determinant_1);

  TCase *tc_determinant_2;
  tc_determinant_2 = tcase_create("s21_determinant_2");
  suite_add_tcase(s, tc_determinant_2);
  tcase_add_test(tc_determinant_2, s21_determinant_2);

  TCase *tc_inverse_matrix_1;
  tc_inverse_matrix_1 = tcase_create("s21_inverse_matrix_1");
  suite_add_tcase(s, tc_inverse_matrix_1);
  tcase_add_test(tc_inverse_matrix_1, s21_inverse_matrix_1);

  TCase *tc_inverse_matrix_2;
  tc_inverse_matrix_2 = tcase_create("s21_inverse_matrix_2");
  suite_add_tcase(s, tc_inverse_matrix_2);
  tcase_add_test(tc_inverse_matrix_2, s21_inverse_matrix_2);

  TCase *tc_inverse_matrix_3;
  tc_inverse_matrix_3 = tcase_create("s21_inverse_matrix_3");
  suite_add_tcase(s, tc_inverse_matrix_3);
  tcase_add_test(tc_inverse_matrix_3, s21_inverse_matrix_3);

  return s;
}

int main(void) {
  int nf;
  Suite *s1;
  SRunner *sr;
  s1 = lib_suite();
  sr = srunner_create(s1);

  // srunner_run_all(sr, CK_ENV);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
