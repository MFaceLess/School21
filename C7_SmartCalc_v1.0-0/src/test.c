#include "check.h"
#include "s21_SmartCalc.h"

#define EPS 10E-7

START_TEST(s21_algorithm_1) {
  char *temp = Sort_Facility("2+2*5/(6*3+(-3))");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_double_le(result - 2.66667, EPS);
}
END_TEST

START_TEST(s21_algorithm_2) {
  char *temp = Sort_Facility("c(50*s(50*t(50)))");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_double_le(result - 0.407, EPS);
}
END_TEST

START_TEST(s21_algorithm_3) {
  char *temp = Sort_Facility("6%3/a(50*q(4))*l(2.72)");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_double_le(result - (6 % 3 / atan(50 * sqrt(4)) * log(2.72)), EPS);
}
END_TEST

START_TEST(s21_algorithm_4) {
  char *temp = Sort_Facility("6%3/a(50*q(4))*l(2.72)*g(1000.5555)");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_double_le(
      result - (6 % 3 / atan(50 * sqrt(4)) * log(2.72) * log10(1000.5555)),
      EPS);
}
END_TEST

START_TEST(s21_algorithm_5) {
  Stack *some = init();
  push(some, 50.50);
  pop(some);
  print_stackDouble(some);
  resize(some);
  destroy(&some);
  char *temp = Sort_Facility("i(0.5*o(0.127))");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_double_le(result - (asin(0.5 * acos(0.127))), EPS);
}
END_TEST

START_TEST(s21_algorithm_6) {
  char *temp = Sort_Facility("2^55.6*c(-55.5)");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_double_le(result - (pow(2, 55.6) * cos(-55.5) * (+5)), EPS);
}
END_TEST

START_TEST(s21_algorithm_7) {
  char *temp = Sort_Facility("cos(55.5");
  ck_assert_str_eq(temp, "Error");
}
END_TEST

START_TEST(s21_algorithm_8) {
  char *temp = Sort_Facility("((55.5+2)");
  ck_assert_str_eq(temp, "Error");
}
END_TEST

START_TEST(s21_algorithm_9) {
  char *temp = Sort_Facility("asfasfasf");
  ck_assert_str_eq(temp, "Error");
}
END_TEST

START_TEST(s21_algorithm_10) {
  char *temp = Sort_Facility("55^");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_int_eq(check, 1);
}
END_TEST

START_TEST(s21_algorithm_11) {
  char *temp = Sort_Facility("55*");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_int_eq(check, 1);
}
END_TEST

START_TEST(s21_algorithm_12) {
  char *temp = Sort_Facility("55/");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_int_eq(check, 1);
}
END_TEST

START_TEST(s21_algorithm_13) {
  char *temp = Sort_Facility("55%");
  int check;
  double result = Calculation(temp, &check);
  ck_assert_int_eq(check, 1);
}
END_TEST

Suite *lib_suite(void) {
  Suite *s;
  s = suite_create("Check");

  TCase *tc_algorithm_1;
  tc_algorithm_1 = tcase_create("s21_algorithm_1");
  suite_add_tcase(s, tc_algorithm_1);
  tcase_add_test(tc_algorithm_1, s21_algorithm_1);

  TCase *tc_algorithm_2;
  tc_algorithm_2 = tcase_create("s21_algorithm_2");
  suite_add_tcase(s, tc_algorithm_2);
  tcase_add_test(tc_algorithm_2, s21_algorithm_2);

  TCase *tc_algorithm_3;
  tc_algorithm_3 = tcase_create("s21_algorithm_3");
  suite_add_tcase(s, tc_algorithm_3);
  tcase_add_test(tc_algorithm_3, s21_algorithm_3);

  TCase *tc_algorithm_4;
  tc_algorithm_4 = tcase_create("s21_algorithm_4");
  suite_add_tcase(s, tc_algorithm_4);
  tcase_add_test(tc_algorithm_4, s21_algorithm_4);

  TCase *tc_algorithm_5;
  tc_algorithm_5 = tcase_create("s21_algorithm_5");
  suite_add_tcase(s, tc_algorithm_5);
  tcase_add_test(tc_algorithm_5, s21_algorithm_5);

  TCase *tc_algorithm_6;
  tc_algorithm_6 = tcase_create("s21_algorithm_6");
  suite_add_tcase(s, tc_algorithm_6);
  tcase_add_test(tc_algorithm_6, s21_algorithm_6);

  TCase *tc_algorithm_7;
  tc_algorithm_7 = tcase_create("s21_algorithm_7");
  suite_add_tcase(s, tc_algorithm_7);
  tcase_add_test(tc_algorithm_7, s21_algorithm_7);

  TCase *tc_algorithm_8;
  tc_algorithm_8 = tcase_create("s21_algorithm_8");
  suite_add_tcase(s, tc_algorithm_8);
  tcase_add_test(tc_algorithm_8, s21_algorithm_8);

  TCase *tc_algorithm_9;
  tc_algorithm_9 = tcase_create("s21_algorithm_9");
  suite_add_tcase(s, tc_algorithm_9);
  tcase_add_test(tc_algorithm_9, s21_algorithm_9);

  TCase *tc_algorithm_10;
  tc_algorithm_10 = tcase_create("s21_algorithm_10");
  suite_add_tcase(s, tc_algorithm_10);
  tcase_add_test(tc_algorithm_10, s21_algorithm_10);

  TCase *tc_algorithm_11;
  tc_algorithm_11 = tcase_create("s21_algorithm_11");
  suite_add_tcase(s, tc_algorithm_11);
  tcase_add_test(tc_algorithm_11, s21_algorithm_11);

  TCase *tc_algorithm_12;
  tc_algorithm_12 = tcase_create("s21_algorithm_12");
  suite_add_tcase(s, tc_algorithm_12);
  tcase_add_test(tc_algorithm_12, s21_algorithm_12);

  TCase *tc_algorithm_13;
  tc_algorithm_13 = tcase_create("s21_algorithm_13");
  suite_add_tcase(s, tc_algorithm_13);
  tcase_add_test(tc_algorithm_13, s21_algorithm_13);

  return s;
}

int main(void) {
  int nf;
  Suite *s1;
  SRunner *sr;
  s1 = lib_suite();
  sr = srunner_create(s1);

  // srunner_run_all(sr, CK_ENV);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
