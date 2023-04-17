#include <stdio.h>

#include "s21_math.h"

long double s21_log(double x) {
  if (x != x || x == s21_INFINITY) {
    return x;
  } else if (x == 0) {
    return -s21_INFINITY;
  } else if (x == 1) {
    return 0;
  } else if (x < 0) {
    return s21_NAN;
  } else if (x == s21_M_E) {
    return 1;
  } else if (x == 2) {
    return s21_M_LN2;
  }
  int k = 2;
  int pow = 0;
  while (x - 1 > 1) {
    x = x * 0.1;
    pow++;
  }
  long double ln = x - 1;
  long double element = (x - 1);
  while (s21_fabs(element) >= s21_EPS && s21_fabs(x - 1) <= 1) {
    element = (element * (-1 * (x - 1)) * (k - 1)) / k;
    ln += element;
    k++;
  }
  return ln + s21_M_LN10 * pow;
}