
#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdio.h>
#include <stdlib.h>

#define NUM_OF_MEM \
  1000  //Определяет количество членов суммы ряда Тейлора (регулирует точность)
#define s21_EPS 1e-17  //Общая проверяемая точность - 16 значащих цифр
#define s21_NAN __builtin_nanf("0x7fc00000")
#define s21_INFINITY __builtin_huge_valf()
#define s21_M_E 2.71828182845904523536028747135266250
#define s21_M_LOG2E 1.44269504088896340735992468100189214
#define s21_M_LOG10E 0.434294481903251827651128918916605082
#define s21_M_LN2 0.693147180559945309417232121458176568
#define s21_M_LN10 2.30258509299404568401799145468436421
#define s21_M_PI 3.14159265358979323846264338327950288
#define s21_M_PI_2 1.57079632679489661923132169163975144
#define s21_M_PI_4 0.785398163397448309615660845819875721
#define s21_M_1_PI 0.318309886183790671537767526745028724
#define s21_M_2_PI 0.636619772367581343075535053490057448
#define s21_M_2_SQRTPI 1.12837916709551257389615890312154517
#define s21_M_SQRT2 1.41421356237309504880168872420969808
#define s21_M_SQRT1_2 0.707106781186547524400844362104849039
#define CL_DBL_MAX 1.7976931348623157E308

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);

long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);

long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);

long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);

long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

long double s21_powd(long double a, int n);
double delete (double x);

#endif  // SRC_S21_MATH_H_
