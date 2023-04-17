#include "check.h"
#include "s21_3DViewer.h"

START_TEST(parsing) {
  char* name = "./objects/lamp.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check) {
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(parsing_no_file) {
  char* name = "./objects/no.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 1);
}
END_TEST

START_TEST(parsing_empty_file) {
  char* name = "./objects/not.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(transforming_move_x) {
  char* name = "./objects/cube.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    move_x(&points, 0.5);
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(transforming_move_y) {
  char* name = "./objects/cube.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    move_y(&points, 0.5);
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(transforming_move_z) {
  char* name = "./objects/cube.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    move_z(&points, 0.5);
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(transforming_rotate_x) {
  char* name = "./objects/cube.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    rotate_x(&points, 3.1415);
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(transforming_rotate_y) {
  char* name = "./objects/cube.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    rotate_y(&points, 3.1415);
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(transforming_rotate_z) {
  char* name = "./objects/cube.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    rotate_z(&points, 3.1415);
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(transforming_scale_x) {
  char* name = "./objects/cube.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    scale_x(&points, 4);
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(transforming_scale_y) {
  char* name = "./objects/cube.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    scale_y(&points, 4);
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(transforming_scale_z) {
  char* name = "./objects/cube.obj";
  mass_points points;
  surfaces surface;
  int check = readFile(name, &points, &surface);
  if (check == 0) {
    scale_z(&points, 4);
    destroy_points(&points);
    destroy_surfaces(&surface);
  }
  ck_assert_int_eq(check, 0);
}
END_TEST

START_TEST(stack) {
  Stack* stack = init();
  push(stack, 1);
  push(stack, 2);
  push(stack, 3);
  push(stack, 4);
  push(stack, 5);
  ck_assert_int_eq(pop(stack), 5);
  print_stackDouble(stack);
  destroy(&stack);
}
END_TEST

Suite* lib_suite(void) {
  Suite* s;
  s = suite_create("Check");
  TCase* tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, parsing);
  tcase_add_test(tcase_core, parsing_no_file);
  tcase_add_test(tcase_core, parsing_empty_file);
  tcase_add_test(tcase_core, transforming_move_x);
  tcase_add_test(tcase_core, transforming_move_y);
  tcase_add_test(tcase_core, transforming_move_z);
  tcase_add_test(tcase_core, transforming_rotate_x);
  tcase_add_test(tcase_core, transforming_rotate_y);
  tcase_add_test(tcase_core, transforming_rotate_z);
  tcase_add_test(tcase_core, transforming_scale_x);
  tcase_add_test(tcase_core, transforming_scale_y);
  tcase_add_test(tcase_core, transforming_scale_z);
  tcase_add_test(tcase_core, stack);
  suite_add_tcase(s, tcase_core);

  return s;
}

int main(void) {
  int nf;
  Suite* s1;
  SRunner* sr;
  s1 = lib_suite();
  sr = srunner_create(s1);

  // srunner_run_all(sr, CK_ENV);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);

  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
