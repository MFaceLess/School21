#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1E-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// --------------------Основные функции--------------------------
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
// --------------------------------------------------------------

// -----------------Вспомогательные функции----------------------
void s21_print_matrix(matrix_t *result);
double s21_floor(double num, int x);
int s21_matrix_minor(matrix_t *A, matrix_t *result, int i, int j);
int col_max(matrix_t *A, int col);
int triangulation(matrix_t *A);
double matrixDet(matrix_t *A);
// --------------------------------------------------------------

// SRC_S21_MATRIX_H_
#endif
