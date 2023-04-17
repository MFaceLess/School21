#include "s21_math.h"

long double s21_powd(long double a, int n) {
  long double answ = 1;
  if (n < 0) {
    n = -n;
    a = 1 / a;
  }
  for (int i = 0; i < n; i++) {
    answ = answ * a;
  }
  return answ;
}