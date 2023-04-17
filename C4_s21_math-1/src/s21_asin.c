#include "s21_math.h"

long double s21_asin(double x) {
  long double asin = x;
  int k = 1;
  long double element = x;
  if (x > 1 || x < -1) return s21_NAN;
  if (x == 1) {
    asin = s21_M_PI_2;
  } else if (x == -1) {
    asin = -s21_M_PI_2;
  } else {
    while (s21_fabs(element) >= s21_EPS) {
      element = ((element) * (x * x) * (2 * k - 1) * (2 * k - 1)) /
                ((2 * k + 1) * (2 * k));
      asin += element;
      k++;
    }
  }
  return asin;
}
