#include "s21_math.h"

// Следует потом заменить функции ниже factorial и fast_power на библиотечные,
// когда они будут реализованы

long double s21_acos(double x) {
  if (x > 1 || x < -1) return s21_NAN;
  if (x == 1) {
    return 0;
  } else if (x == -1) {
    return s21_M_PI;
  } else {
    return s21_M_PI_2 - s21_asin(x);
  }
}
