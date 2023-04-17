#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  s21_decimal ten;
  s21_decimal valueBuff;
  s21_clear_decimal(result);
  s21_from_float_to_decimal(10, &ten);
  int remainder = 0;
  int bit1, bit2;
  int resultBit = 0;
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  int exp;
  int status;
  if (exp1 >= exp2) {
    exp = exp1;
  } else {
    exp = exp2;
  }
  if (sign1 == 1 && sign2 == 0) {
    value_1.bits[3] = exp1 << 16;
    status = s21_sub(value_2, value_1, result);
  } else if (sign1 == 0 && sign2 == 1) {
    value_2.bits[3] = exp2 << 16;
    status = s21_sub(value_1, value_2, result);
  } else {
    if (exp != 0 && exp1 != exp2) {
      if (exp1 < exp) {
        s21_decimal_pow(&ten, exp - 1 - exp1);
        s21_mul(value_1, ten, &valueBuff);
        s21_copy_to_buffer(valueBuff, &value_1);
      } else if (exp2 < exp) {
        s21_decimal_pow(&ten, exp - 1 - exp2);
        s21_mul(value_2, ten, &valueBuff);
        s21_copy_to_buffer(valueBuff, &value_2);
      }
    }

    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        bit1 = s21_get_bit(value_1, i, j);
        bit2 = s21_get_bit(value_2, i, j);

        resultBit = s21_addition(bit1, bit2, &remainder);
        if (resultBit == 1) {
          s21_set_bit(result, i, j);
        }
      }
    }

    result->bits[3] = exp << 16 | (sign1 | sign2) << 31;
    if (s21_get_sign(*result) == 1 && remainder == 1) {
      remainder = 2;
    }
    status = remainder;
  }
  return status;
}
