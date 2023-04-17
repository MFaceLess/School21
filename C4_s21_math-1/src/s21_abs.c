#include "s21_math.h"

int s21_abs(int x) {
  int result;
  if (x < 0) {
    result = -1 * x;
  } else {
    result = x;
  }
  return result;
}
