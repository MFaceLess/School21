#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_SIZE 10
#define MULTIPLIER 2
#define STACK_OVERFLOW -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY -102

#define BUFF 10000

#define NUM_POINTS 5
#define NUM_COMMANDS 7

#define is_function(c)                                                     \
  (c == 'c' || c == 's' || c == 't' || c == 'o' || c == 'i' || c == 'a' || \
   c == 'q' || c == 'l' || c == 'g')
#define is_ident(c) ((c >= '0' && c <= '9') || c == 'x')
#define is_operator(c)                                                     \
  (c == '+' || c == '-' || c == '/' || c == '*' || c == '^' || c == '%' || \
   c == '=' || c == '~' || c == ';')

typedef double T;

typedef struct Stack {
  T *data;
  size_t size;
  size_t top;
} Stack;

// --------------------Основные функции--------------------------
int op_preced(const char c);
int op_left_assoc(const char c);

char *Sort_Facility(char *input);
double Calculation(char *middle, int *check);
// --------------------------------------------------------------

// -----------------Вспомогательные функции----------------------
Stack *init();
void push(Stack *stack, double value);
T pop(Stack *stack);
void resize(Stack *stack);
void destroy(Stack **stack);
void print_stackDouble(Stack *stack);
char *find_and_insert(char *str, char *sub_str, char *sub_str_rep);
// --------------------------------------------------------------

// SRC_S21_SMARTCALC_H_
#endif