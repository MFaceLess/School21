#include "s21_math.h"

long double s21_exp(double x) {
  long double result = 1, temp = 1;
  long double e = 1;
  int flag = 0;
  if (x < 0) {
    x *= -1;
    flag = 1;
  }
  while (s21_fabs(result) > s21_EPS) {
    result *= x / e;
    e += 1;
    temp += result;
    if (temp > CL_DBL_MAX) {
      temp = s21_INFINITY;
      break;
    }
  }
  temp = flag == 1 ? temp > CL_DBL_MAX ? 0 : 1. / temp : temp;
  return temp = temp > CL_DBL_MAX ? s21_INFINITY : temp;
}

/**
 long double s21_exp(double x) {
  if (x != x) {
    return x;
  }
  int iters = 1;
  long double e = 1;
  long double element = x / iters;
  if (s21_fabs(x) != s21_INFINITY) {
    while (s21_fabs(element) >= s21_EPS) {
      e += element;
      iters++;
      element = (element * x) / iters;
    }
  } else if (x > 0) {
    return x;
  } else {
    return 0;
  }
  return e;
}
*/
