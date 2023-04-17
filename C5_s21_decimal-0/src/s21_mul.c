#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int bit;
  s21_decimal mulBuffer;
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_clear_decimal(&mulBuffer);
  s21_clear_decimal(result);
  s21_copy_to_buffer_no_exp(value_2, &mulBuffer);
  s21_decimal resultBuffer;
  s21_clear_decimal(&resultBuffer);
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  int status = 0;
  if (s21_is_equal(value_1, zero) || s21_is_equal(value_2, zero)) {
    status = 0;
  } else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit = s21_get_bit(value_1, i, j);
        if (bit == 1) {
          s21_copy_to_buffer_no_exp(*result, &resultBuffer);
          s21_clear_decimal(result);
          s21_add(mulBuffer, resultBuffer, result);
        }
        status = s21_left_shift(&mulBuffer);
      }
    }
    s21_set_exp(result, exp1 + exp2);
    if ((sign1 ^ sign2) == 1) {
      s21_set_bit(result, 31, 3);
    }
    status = status ^ 1;
    if (s21_get_sign(*result) == 1 && status == 1) {
      status = 2;
    }
  }
  return status;
}