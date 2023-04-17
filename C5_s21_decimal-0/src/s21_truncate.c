#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_clear_decimal(&valueBuff);
  s21_from_float_to_decimal(10, &ten);
  int error = 0;
  int sign_op = s21_get_sign(value);
  int exp = s21_get_exp(value);
  value.bits[3] = 0;

  while (exp > 0) {
    s21_div(value, ten, result);
    s21_copy_to_buffer(*result, &value);
    exp--;
  }
  if (sign_op == 1) {
    result->bits[3] = (unsigned long)1 << 31;
  }
  return error;
}
