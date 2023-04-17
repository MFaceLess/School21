#include "s21_math.h"

long double s21_tan(double x) {
  if (x != x) {
    return x;
  } else if (s21_fabs(x) == s21_INFINITY) {
    return s21_NAN;
  }
  return s21_sin(x) / s21_cos(x);
}