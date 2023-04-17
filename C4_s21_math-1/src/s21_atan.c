#include "s21_math.h"

long double atan_1(double x) {
  long double result = x, temp = x, i = 1;
  while (s21_fabs(result) > s21_EPS) {
    result = -1 * result * x * x * (2 * i - 1) / (2 * i + 1);
    i += 1;
    temp += result;
  }
  return temp;
}

/**
 вычисляет арктангенс
 проверка на вхождение в допустимый диапазон (1;1), тернарная условная операция
 arctg x = pi/2 - arctg 1/x
 s21_EPS-Общая проверяемая точность - 16 значащих цифр
 */
long double s21_atan(double x) {
  long double temp = 0;
  if (x != x) {
    return s21_NAN;
  } else if (s21_fabs(x) == s21_INFINITY) {
    return s21_M_PI_2;
  }
  temp = (x < 1 && x > -1) ? atan_1(x) : temp;
  temp = x == 1 ? s21_M_PI / 4 : x == -1 ? -s21_M_PI / 4 : x == 0 ? 0 : temp;
  temp = x > 1    ? s21_M_PI / 2 - atan_1(1 / x)
         : x < -1 ? -s21_M_PI / 2 - atan_1(1 / x)
                  : temp;
  return temp;
}
