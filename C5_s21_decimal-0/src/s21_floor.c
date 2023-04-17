#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int status;
  s21_decimal valueBuff;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_clear_decimal(&valueBuff);
  if (s21_get_sign(value) == 0) {
    status = s21_truncate(value, result);
  } else {
    status = s21_truncate(value, result);
    result->bits[3] = 0;
    s21_add(*result, one, &valueBuff);
    s21_copy_to_buffer(valueBuff, result);
    result->bits[3] = (unsigned long)1 << 31;
  }
  return status;
}