#include "s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_from_float_to_decimal(10, &ten);
  int exp1 = s21_get_exp(a);
  int exp2 = s21_get_exp(b);
  int exp;
  int invert = 0;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }
  if (exp1 < exp) {
    s21_decimal_pow(&ten, exp - 1 - exp1);
    s21_mul(a, ten, &valueBuff);
    s21_copy_to_buffer(valueBuff, &a);
  } else if (exp2 < exp) {
    s21_decimal_pow(&ten, exp - 1 - exp2);
    s21_mul(b, ten, &valueBuff);
    s21_copy_to_buffer(valueBuff, &b);
  }
  return a.bits[0] == b.bits[0] && a.bits[1] == b.bits[1] &&
             a.bits[2] == b.bits[2] && s21_get_sign(a) == s21_get_sign(b) ||
         s21_zero_decimal(a, b);
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return s21_is_equal(a, b) == 0;
}