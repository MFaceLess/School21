#include "s21_math.h"

long double s21_pow(double base, double exp) {
  if (base == 1) {
    return 1;
  }
  if (base == -1 && s21_fabs(exp) == s21_INFINITY) {
    return 1;
  }
  if (base == 0 && (exp > 0)) {
    return 0;
  }
  if (exp == 0) {
    return 1;
  }
  if (base == 0 && exp >= 0) {
    return s21_INFINITY;
  }
  if (base != base || exp != exp) {
    return s21_NAN;
  }
  if ((exp == s21_INFINITY && s21_fabs(base) > 1) ||
      (exp == -s21_INFINITY && s21_fabs(base) < 1)) {
    return s21_INFINITY;
  } else if (exp == -s21_INFINITY ||
             (exp == s21_INFINITY && s21_fabs(base) < 1)) {
    return 0;
  }
  if (exp == 0) {
    return 1;
  } else {
    if (exp == (long int)exp || s21_fabs(exp) == s21_INFINITY) {
      return s21_powd(base, (int)exp);
    } else if (exp > 0) {
      return s21_exp(exp * s21_log(base));
    } else {
      return 1 / (s21_exp(-exp * s21_log(base)));
    }
  }
}
