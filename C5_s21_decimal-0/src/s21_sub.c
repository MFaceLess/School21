#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_clear_decimal(&valueBuff);
  s21_from_float_to_decimal(10, &ten);
  s21_clear_decimal(result);
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  int exp;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }
  int status;
  if (sign1 == 1 && sign2 == 0) {
    s21_set_sign(&value_2);
    status = s21_add(value_1, value_2, result);
  } else if (sign1 == 0 && sign2 == 1) {
    value_2.bits[3] = exp2 << 16;
    status = s21_add(value_1, value_2, result);
  } else {
    if (exp != 0 && exp1 != exp2) {
      if (exp1 < exp) {
        s21_decimal_pow(&ten, exp - 1 - exp1);
        s21_mul(value_1, ten, &valueBuff);
        s21_copy_to_buffer(valueBuff, &value_1);
        exp1 = exp;
      } else if (exp2 < exp) {
        s21_decimal_pow(&ten, exp - 1 - exp2);
        s21_mul(value_2, ten, &valueBuff);
        s21_copy_to_buffer(valueBuff, &value_2);
        exp2 = exp;
      }
    }
    sign2 = sign2 ^ 1;
    value_2.bits[3] = exp2 << 16;
    value_1.bits[3] = exp1 << 16;

    if (s21_is_greater(value_1, value_2) == 1) {
      s21_invert_decimal(&value_2);
      status = s21_add(value_1, value_2, result) ^ 1;
      result->bits[3] = exp << 16 | (sign1) << 31;
      one.bits[3] = exp << 16 | (sign1) << 31;
      s21_add(*result, one, &valueBuff);
      s21_copy_to_buffer(valueBuff, result);

    } else if (s21_is_less(value_1, value_2) == 1) {
      s21_invert_decimal(&value_1);
      status = s21_add(value_2, value_1, result) ^ 1;
      result->bits[3] = exp << 16 | (sign2) << 31;
      one.bits[3] = exp << 16 | (sign2) << 31;
      s21_add(*result, one, &valueBuff);
      s21_copy_to_buffer(valueBuff, result);
    } else {
      status = 0;
    }
    if (s21_get_sign(*result) == 1 && status == 1) {
      status = 2;
    }
  }
  return status;
}