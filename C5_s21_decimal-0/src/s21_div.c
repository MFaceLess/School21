#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal R;
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_clear_decimal(&R);
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_clear_decimal(&valueBuff);
  s21_from_float_to_decimal(10, &ten);
  int bit;
  s21_decimal divBuffer;
  s21_clear_decimal(&divBuffer);
  s21_clear_decimal(result);

  int status = 0;
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;

  int exp;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }

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
  if (s21_is_equal(value_2, zero) == 1) {
    status = 3;
  } else {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit = s21_get_bit(value_1, 31 - i, 2 - j);
        s21_left_shift(&R);
        if (bit == 1) {
          s21_set_bit(&R, 0, 0);
        }

        if (s21_is_greater_or_equal(R, value_2)) {
          s21_clear_decimal(&divBuffer);
          s21_sub(R, value_2, &divBuffer);
          s21_copy_to_buffer(divBuffer, &R);
          s21_set_bit(result, 31 - i, 2 - j);
        }
      }
    }
    s21_set_exp(result, exp1 - exp2);
    if ((sign1 ^ sign2) == 1) {
      s21_set_bit(result, 31, 3);
    }
  }
  return status;
}