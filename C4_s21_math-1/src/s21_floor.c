#include "s21_math.h"

long double s21_floor(double x) {
  if (s21_fabs(x) != s21_INFINITY && x == x) {
    int sign = 1;
    if (x < 0) {
      sign = -1;
    }
    long ipart = (long)x;
    if (sign == -1 && ipart != x) {
      ipart--;
    }
    return (long double)ipart;
  } else if (s21_fabs(x) == s21_INFINITY) {
    return x;
  } else {
    return s21_NAN;
  }
}
