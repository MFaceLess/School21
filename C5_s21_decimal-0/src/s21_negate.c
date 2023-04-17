#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  result->bits[3] =
      ((s21_get_sign(*result) ^ 1) << 31) | (s21_get_exp(*result) << 16);
  return 0;
}