#ifndef SRC_S21_3DVIEWER_H_
#define SRC_S21_3DVIEWER_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF 100000
#define INIT_SIZE 10
#define MULTIPLIER 2

#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY -102

#define is_Digit(c) (c >= '0' && c <= '9')

typedef int T;

typedef struct Stack {
  T* data;
  size_t size;
  size_t top;
} Stack;

typedef struct point {
  double x;
  double y;
  double z;
  int serial_number;
} point;

typedef struct mass_points {
  point* points;
  int num;
} mass_points;

typedef struct surfaces {
  Stack** mass_of_surfaces;  // массив указателей на стеки
  int amount_of_surfaces;
} surfaces;

// --------------------Основные функции--------------------------

// --------------------------------------------------------------

// -------------------------Парcинг файла------------------------
int readFile(char* file_name, mass_points* points, surfaces* surface);
void destroy_points(mass_points* points);
void destroy_surfaces(surfaces* surface);
// --------------------------------------------------------------

// ---------------------Аффинные трансформации-------------------
void move_x(mass_points* points_arr, double x);
void move_y(mass_points* points_arr, double y);
void move_z(mass_points* points_arr, double z);

void rotate_x(mass_points* points_arr, double angle);
void rotate_y(mass_points* points_arr, double angle);
void rotate_z(mass_points* points_arr, double angle);

void scale_x(mass_points* points_arr, double x);
void scale_y(mass_points* points_arr, double y);
void scale_z(mass_points* points_arr, double z);

// --------------------------------------------------------------

// ----------------------------Stack-----------------------------
Stack* init();
void push(Stack* stack, T value);
T pop(Stack* stack);
void resize(Stack* stack);
void destroy(Stack** stack);
void print_stackDouble(Stack* stack);
// --------------------------------------------------------------

#endif  // SRC_S21_3DVIEWER_H_
