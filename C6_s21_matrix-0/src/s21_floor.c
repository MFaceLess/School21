#include "s21_matrix.h"

double s21_floor(double num, int x) {
  // целая часть
  int temp1 = num;
  // дробная
  num -= temp1;

  int temp_x = x;
  while (temp_x) {
    num *= 10;
    temp_x--;
  }
  // округленая дробная в int представлении
  double z = (int)num;
  while (x) {
    z /= 10;
    x--;
  }
  return (double)temp1 + z;
}
