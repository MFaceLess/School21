#include "s21_math.h"

long double s21_cos(double x) {
  if (x != x) {
    return x;
  } else if (s21_fabs(x) == s21_INFINITY) {
    return s21_NAN;
  }
  int k = 1;
  double cos = 0;
  long double element = 1;
  x = delete (x);
  while (s21_fabs(element) >= s21_EPS) {
    cos = cos + element;
    element = (-element) * (x * x) / ((2 * k - 1) * (2 * k));
    k++;
  }
  return cos;
}
