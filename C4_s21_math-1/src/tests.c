#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

START_TEST(pow_test_1) {
  for (double k = -9; k <= 9; k += 1.7) {
    for (double g = -5; g < 5; g += 1) {
      long double a = s21_pow(k, g);
      long double b = pow(k, g);
      if ((!isnan(a) && !isnan(b)) && !(a == INFINITY && b == INFINITY) &&
          !(a == -INFINITY && b == -INFINITY)) {
        ck_assert_double_eq_tol(a, b, 1e-6);
      }
      a = s21_pow(g, k);
      b = pow(g, k);
      if ((!isnan(a) && !isnan(b)) && !(a == INFINITY && b == INFINITY) &&
          !(a == -INFINITY && b == -INFINITY)) {
        ck_assert_double_eq_tol(a, b, 1e-6);
      }
    }
  }
}
END_TEST

START_TEST(pow_test_2) {
  for (double k = -1e-1; k <= 1; k += 1.1e-1) {
    for (double g = -2.55; g < 2; g += 1.1) {
      long double a = s21_pow(k, g);
      long double b = pow(k, g);
      if ((!isnan(a) && !isnan(b)) && !(a == INFINITY && b == INFINITY) &&
          !(a == -INFINITY && b == -INFINITY)) {
        ck_assert_double_eq_tol(a, b, 1e-5);
      }
      a = s21_pow(g, k);
      b = pow(g, k);
      if ((!isnan(a) && !isnan(b)) && !(a == INFINITY && b == INFINITY) &&
          !(a == -INFINITY && b == -INFINITY)) {
        ck_assert_double_eq_tol(a, b, 1e-5);
      }
    }
  }
}
END_TEST

START_TEST(pow_test_3) {
  ck_assert_double_eq(pow(1, 0), s21_pow(1, 0));
  ck_assert_double_eq(pow(-1, 3), s21_pow(-1, 3));
  ck_assert_double_eq(pow(-1, 4), s21_pow(-1, 4));
  ck_assert_double_eq(pow(0, 0), s21_pow(0, 0));
  ck_assert_double_eq(pow(0, -1), s21_pow(0, -1));
  ck_assert_double_eq(pow(0, 1), s21_pow(0, 1));
  ck_assert_double_eq(pow(INFINITY, 0), s21_pow(s21_INFINITY, 0));
  ck_assert_double_eq(pow(INFINITY, -1), s21_pow(s21_INFINITY, -1));
  ck_assert_double_eq(pow(-1, -INFINITY), s21_pow(-1, -s21_INFINITY));
  ck_assert_double_eq(pow(0, INFINITY), s21_pow(0, s21_INFINITY));
  ck_assert_double_nan(s21_pow(0, s21_NAN));
  ck_assert_double_eq(pow(NAN, 0), s21_pow(s21_NAN, 0));
  ck_assert_double_nan(s21_pow(s21_NAN, s21_NAN));
  ck_assert_double_eq(pow(INFINITY, INFINITY),
                      s21_pow(s21_INFINITY, s21_INFINITY));
  ck_assert_double_eq(pow(INFINITY, -INFINITY),
                      s21_pow(s21_INFINITY, -s21_INFINITY));
  ck_assert_double_eq(pow(-INFINITY, INFINITY),
                      s21_pow(-s21_INFINITY, s21_INFINITY));
  ck_assert_double_eq(pow(-INFINITY, -INFINITY),
                      s21_pow(-s21_INFINITY, -s21_INFINITY));
  ck_assert_double_eq(pow(1, -INFINITY), s21_pow(1, -s21_INFINITY));
  ck_assert_double_eq(pow(1, NAN), s21_pow(1, s21_NAN));
  ck_assert_double_nan(s21_pow(s21_NAN, s21_INFINITY));
  ck_assert_double_nan(s21_pow(s21_INFINITY, s21_NAN));
  ck_assert_double_nan(s21_pow(s21_NAN, -s21_INFINITY));
  ck_assert_double_nan(s21_pow(-s21_INFINITY, s21_NAN));
  ck_assert_double_eq(pow(2, INFINITY), s21_pow(2, s21_INFINITY));
  ck_assert_double_eq(pow(0.5, INFINITY), s21_pow(0.5, s21_INFINITY));
  ck_assert_double_eq(pow(-2, INFINITY), s21_pow(-2, s21_INFINITY));
  ck_assert_double_eq(pow(2, -INFINITY), s21_pow(2, -s21_INFINITY));
  ck_assert_double_eq(pow(0.5, -INFINITY), s21_pow(0.5, -s21_INFINITY));
  ck_assert_double_eq(pow(-2, -INFINITY), s21_pow(-2, -s21_INFINITY));
}
END_TEST

START_TEST(log_test_1) {
  for (double k = 1; k < 100; k += 13.2) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(log_test_2) {
  for (double k = 0.1; k < 4; k += 0.24) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(log_test_3) {
  for (double k = 0.1; k < 10000; k += 123) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(log_test_4) {
  for (double k = 0.000005; k < 1; k *= 5) {
    double a = s21_log(k);
    double b = log(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(log_test_5) {
  ck_assert_double_nan(s21_log(s21_NAN));
  // ck_assert_double_eq(log(0), s21_log(0));
  ck_assert_double_nan(s21_log(-3));
  ck_assert_double_eq(log(INFINITY), s21_log(s21_INFINITY));
  ck_assert_double_nan(s21_log(-s21_INFINITY));
  ck_assert_double_eq(log(1), s21_log(1));
  ck_assert_double_eq(log(M_E), s21_log(s21_M_E));
  ck_assert_double_eq_tol(log(2), s21_log(2), 1e-6);
}
END_TEST

START_TEST(sin_test_1) {
  for (int R = 15; R >= -15; R -= 4) {
    for (double k = 2 * s21_M_PI; k > -2 * s21_M_PI; k -= s21_M_PI / 17) {
      ck_assert_double_eq_tol(sin(k + R * s21_M_PI), s21_sin(k + R * s21_M_PI),
                              1e-6);
    }
  }
}
END_TEST

START_TEST(cos_test_1) {
  for (int R = 15; R >= -15; R -= 4) {
    for (double k = 2 * s21_M_PI; k > -2 * s21_M_PI; k -= s21_M_PI / 17) {
      ck_assert_double_eq_tol(cos(k + R * s21_M_PI), s21_cos(k + R * s21_M_PI),
                              1e-6);
    }
  }
}
END_TEST

START_TEST(tan_test_1) {
  for (int R = 15; R >= -15; R -= 4) {
    for (double k = 2 * s21_M_PI; k > -2 * s21_M_PI; k -= s21_M_PI / 9) {
      ck_assert_double_eq_tol(tan(k + R * s21_M_PI), s21_tan(k + R * s21_M_PI),
                              1e-6);
    }
  }
}
END_TEST

START_TEST(sin_cos_tan_test) {
  ck_assert_double_nan(s21_sin(s21_NAN));
  ck_assert_double_nan(s21_cos(s21_NAN));
  ck_assert_double_nan(s21_tan(s21_NAN));
  ck_assert_double_nan(s21_sin(s21_INFINITY));
  ck_assert_double_nan(s21_cos(s21_INFINITY));
  ck_assert_double_nan(s21_tan(s21_INFINITY));
  ck_assert_double_nan(s21_sin(-s21_INFINITY));
  ck_assert_double_nan(s21_cos(-s21_INFINITY));
  ck_assert_double_nan(s21_tan(-s21_INFINITY));
  // ck_assert_double_eq_tol(tan(M_PI / 2), s21_tan(s21_M_PI / 2), 1e-7);
  // ck_assert_double_eq_tol(tan(-M_PI / 2), s21_tan(-s21_M_PI / 2), 1e-7);
}
END_TEST

START_TEST(exp_test_1) {
  for (double k = -21; k < 21; k += 1) {
    double a = s21_exp(k);
    double b = exp(k);
    ck_assert_double_eq_tol(a, b, 1e-16);
  }
}
END_TEST

START_TEST(exp_test_2) {
  for (double k = -15; k < 15; k += 0.123) {
    double a = s21_exp(k);
    double b = exp(k);
    ck_assert_double_eq_tol(a, b, 1e-16);
  }
}
END_TEST

START_TEST(exp_test_3) {
  for (double k = -5; k < 5; k += 0.00573) {
    double a = s21_exp(k);
    double b = exp(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(exp_test_4) {
  ck_assert_double_nan(s21_exp(s21_NAN));
  ck_assert_double_eq(exp(INFINITY), s21_exp(s21_INFINITY));
  ck_assert_double_eq(exp(-INFINITY), s21_exp(-s21_INFINITY));
  ck_assert_double_eq(exp(0), s21_exp(0));
  ck_assert_double_eq(exp(1), s21_exp(1));
}
END_TEST

START_TEST(asin_test_1) {
  for (float k = -1; k <= 1; k += 0.1) {
    double a = s21_asin(k);
    double b = asin(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
  ck_assert_double_eq_tol(asin(1), s21_asin(1), 1e-7);
}
END_TEST

START_TEST(asin_test_2) {
  for (float k = -1; k <= 1; k += 0.0771) {
    double a = s21_asin(k);
    double b = asin(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(acos_test_1) {
  for (float k = -1; k <= 1; k += 0.1) {
    double a = s21_acos(k);
    double b = acos(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(acos_test_2) {
  for (float k = -1; k <= 1; k += 0.0305) {
    double a = s21_acos(k);
    double b = acos(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(acos_test_3) {
  double a = s21_acos(1);
  double b = acos(1);
  ck_assert_double_eq_tol(a, b, 1e-7);
}
END_TEST

START_TEST(atan_test_1) {
  for (float k = -10; k <= 10; k += 4) {
    double a = s21_atan(k);
    double b = atan(k);
    ck_assert_double_eq_tol(a, b, 1e-7);
  }
}
END_TEST

START_TEST(sqrt_test_1) {
  for (double k = 0; k < 21; k += 3) {
    double a = s21_sqrt(k);
    double b = sqrt(k);
    ck_assert_double_eq_tol(a, b, 1e-6);
  }
}
END_TEST

START_TEST(sqrt_test_2) {
  ck_assert_double_nan(s21_sqrt(s21_NAN));
  ck_assert_double_nan(sqrt(NAN));
  ck_assert_double_eq(s21_sqrt(s21_INFINITY), sqrt(INFINITY));
  ck_assert_double_nan(s21_sqrt(-s21_INFINITY));
  ck_assert_double_nan(sqrt(-INFINITY));
  // ck_assert_double_nan(s21_sqrt(-5));
  // ck_assert_double_nan(sqrt(-5));
  ck_assert_double_eq_tol(s21_sqrt(1000), sqrt(1000), 1e-7);
}
END_TEST

START_TEST(atan_test_2) {
  double a = 12;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-7);
  a = 0.4;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-7);
  a = -0.333;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-7);
  a = 55;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-7);
  a = 13.54;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-7);
  a = s21_M_E;
  ck_assert_double_eq_tol(atan(a), s21_atan(a), 1e-7);
}
END_TEST

START_TEST(asin_acos_atan_test) {
  ck_assert_double_nan(s21_asin(s21_NAN));
  ck_assert_double_nan(s21_acos(s21_NAN));
  ck_assert_double_nan(s21_atan(s21_NAN));
  ck_assert_double_nan(s21_asin(s21_INFINITY));
  ck_assert_double_nan(s21_acos(s21_INFINITY));
  ck_assert_double_eq(atan(INFINITY), s21_atan(s21_INFINITY));
  ck_assert_double_nan(s21_asin(-s21_INFINITY));
  ck_assert_double_nan(s21_acos(-s21_INFINITY));
  ck_assert_double_eq(atan(-INFINITY), atan(-s21_INFINITY));
  ck_assert_double_nan(s21_asin(5));
  ck_assert_double_nan(s21_acos(6));
  ck_assert_double_nan(s21_asin(-8));
  ck_assert_double_nan(s21_acos(-4));
}
END_TEST

START_TEST(abs_test) {
  ck_assert_double_eq(abs(-7), s21_abs(-7));
  ck_assert_double_eq(abs(-98), s21_abs(-98));
  ck_assert_double_eq(abs(123), s21_abs(123));
  ck_assert_double_eq(abs(10009), s21_abs(10009));
  ck_assert_double_eq(abs(-10009), s21_abs(-10009));
}
END_TEST

START_TEST(fabs_test) {
  ck_assert_double_eq(fabs(INFINITY), s21_fabs(s21_INFINITY));
  ck_assert_double_eq(fabs(-INFINITY), s21_fabs(-s21_INFINITY));
  ck_assert_double_nan(fabs(NAN));
  ck_assert_double_nan(s21_fabs(s21_NAN));
  ck_assert_double_eq(fabs(-7.0), s21_fabs(-7.0));
  ck_assert_double_eq(fabs(-98.1), s21_fabs(-98.1));
  ck_assert_double_eq(fabs(123.02), s21_fabs(123.02));
  ck_assert_double_eq(fabs(10009.0), s21_fabs(10009.0));
  ck_assert_double_eq(fabs(-10009.555), s21_fabs(-10009.555));
  ck_assert_double_eq(fabs(-0.10009), s21_fabs(-0.10009));
  ck_assert_double_eq(fabs(-1e23), s21_fabs(-1e23));
}
END_TEST

START_TEST(floor_test) {
  ck_assert_double_eq(floor(INFINITY), s21_floor(s21_INFINITY));
  ck_assert_double_eq(floor(-INFINITY), s21_floor(-s21_INFINITY));
  ck_assert_double_nan(floor(NAN));
  ck_assert_double_nan(s21_floor(s21_NAN));
  ck_assert_double_eq(floor(-7.0), s21_floor(-7.0));
  ck_assert_double_eq(floor(-98.1), s21_floor(-98.1));
  ck_assert_double_eq(floor(123.02), s21_floor(123.02));
  ck_assert_double_eq(floor(10009.00123), s21_floor(10009.00123));
  ck_assert_double_eq(floor(-10009.555), s21_floor(-10009.555));
  ck_assert_double_eq(floor(-0.10009), s21_floor(-0.10009));
  ck_assert_double_eq(floor(-1e-23), s21_floor(-1e-23));
  ck_assert_double_eq(floor(100091234.5), s21_floor(100091234.5));
}
END_TEST

START_TEST(ceil_test) {
  ck_assert_double_eq(ceil(INFINITY), s21_ceil(s21_INFINITY));
  ck_assert_double_eq(ceil(-INFINITY), s21_ceil(-s21_INFINITY));
  ck_assert_double_nan(ceil(NAN));
  ck_assert_double_nan(s21_ceil(s21_NAN));
  ck_assert_double_eq(ceil(-7.0), s21_ceil(-7.0));
  ck_assert_double_eq(ceil(-98.1), s21_ceil(-98.1));
  ck_assert_double_eq(ceil(123.02), s21_ceil(123.02));
  ck_assert_double_eq(ceil(10009.00123), s21_ceil(10009.00123));
  ck_assert_double_eq(ceil(-10009.555), s21_ceil(-10009.555));
  ck_assert_double_eq(ceil(-0.10009), s21_ceil(-0.10009));
  ck_assert_double_eq(ceil(-1e-23), s21_ceil(-1e-23));
}
END_TEST

START_TEST(fmod_test_1) {
  ck_assert_double_nan(fmod(1, 0));
  ck_assert_double_nan(s21_fmod(1, 0));
  ck_assert_double_eq(fmod(0, -1), s21_fmod(0, -1));
  ck_assert_double_eq(fmod(0, 1), s21_fmod(0, 1));
  ck_assert_double_nan(fmod(INFINITY, -1));
  ck_assert_double_nan(s21_fmod(INFINITY, -1));
  ck_assert_double_eq(fmod(-1, -INFINITY), s21_fmod(-1, -s21_INFINITY));
  ck_assert_double_eq(fmod(0, INFINITY), s21_fmod(0, s21_INFINITY));
  ck_assert_double_nan(s21_fmod(0, s21_NAN));
  ck_assert_double_nan(fmod(0, NAN));
  ck_assert_double_nan(s21_fmod(s21_NAN, s21_NAN));
  ck_assert_double_nan(fmod(NAN, NAN));
  ck_assert_double_nan(s21_fmod(s21_NAN, s21_INFINITY));
  ck_assert_double_nan(s21_fmod(s21_INFINITY, s21_NAN));
  ck_assert_double_nan(s21_fmod(s21_NAN, -s21_INFINITY));
  ck_assert_double_nan(s21_fmod(-s21_INFINITY, s21_NAN));
  ck_assert_double_nan(fmod(NAN, INFINITY));
  ck_assert_double_nan(fmod(INFINITY, NAN));
  ck_assert_double_nan(fmod(NAN, -INFINITY));
  ck_assert_double_nan(fmod(-INFINITY, NAN));
}
END_TEST

START_TEST(fmod_test_2) {
  for (double a = -1500; a < 1500; a += 123) {
    for (double b = -12; b < 12; b += 1.25) {
      ck_assert_double_eq(fmod(a, b), s21_fmod(a, b));
      ck_assert_double_eq(fmod(b, a), s21_fmod(b, a));
    }
  }
}
END_TEST

Suite *s21_string_suite(void) {
  Suite *suite;

  suite = suite_create("s21_string");
  TCase *tcase_core = tcase_create("Core");

  tcase_add_test(tcase_core, pow_test_1);
  tcase_add_test(tcase_core, pow_test_2);
  tcase_add_test(tcase_core, pow_test_3);
  tcase_add_test(tcase_core, log_test_1);
  tcase_add_test(tcase_core, log_test_2);
  tcase_add_test(tcase_core, log_test_3);
  tcase_add_test(tcase_core, log_test_4);
  tcase_add_test(tcase_core, log_test_5);
  tcase_add_test(tcase_core, sin_test_1);
  tcase_add_test(tcase_core, cos_test_1);
  tcase_add_test(tcase_core, tan_test_1);
  tcase_add_test(tcase_core, sin_cos_tan_test);
  tcase_add_test(tcase_core, exp_test_1);
  tcase_add_test(tcase_core, exp_test_2);
  tcase_add_test(tcase_core, exp_test_3);
  tcase_add_test(tcase_core, exp_test_4);
  tcase_add_test(tcase_core, asin_test_1);
  tcase_add_test(tcase_core, asin_test_2);
  tcase_add_test(tcase_core, acos_test_1);
  tcase_add_test(tcase_core, acos_test_2);
  tcase_add_test(tcase_core, acos_test_3);
  tcase_add_test(tcase_core, atan_test_1);
  tcase_add_test(tcase_core, atan_test_2);
  tcase_add_test(tcase_core, asin_acos_atan_test);
  tcase_add_test(tcase_core, sqrt_test_1);
  tcase_add_test(tcase_core, sqrt_test_2);
  tcase_add_test(tcase_core, abs_test);
  tcase_add_test(tcase_core, fabs_test);
  tcase_add_test(tcase_core, floor_test);
  tcase_add_test(tcase_core, ceil_test);
  tcase_add_test(tcase_core, fmod_test_1);
  tcase_add_test(tcase_core, fmod_test_2);

  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = s21_string_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
