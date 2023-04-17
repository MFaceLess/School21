#include "s21_SmartCalc.h"

Stack *init() {
  Stack *out = NULL;
  out = malloc(sizeof(Stack));
  if (out == NULL) {
    exit(OUT_OF_MEMORY);
  }
  out->size = INIT_SIZE;
  out->data = malloc(out->size * sizeof(T));
  if (out->data == NULL) {
    free(out);
    exit(OUT_OF_MEMORY);
  }
  out->top = 0;
  return out;
}

void resize(Stack *stack) {
  stack->size *= MULTIPLIER;
  stack->data = realloc(stack->data, stack->size * sizeof(T));
  if (stack->data == NULL) {
    exit(STACK_OVERFLOW);
  }
}

void push(Stack *stack, T value) {
  if (stack->top >= stack->size) {
    resize(stack);
  }
  stack->data[stack->top] = value;
  stack->top++;
}

T pop(Stack *stack) {
  if (stack->top == 0) {
    exit(STACK_OVERFLOW);
  }
  stack->top--;
  return stack->data[stack->top];
}

void destroy(Stack **stack) {
  free((*stack)->data);
  free(*stack);
  *stack = NULL;
}

void print_stackDouble(Stack *stack) {
  for (size_t i = 0; i < stack->size && i < stack->top; i++) {
    printf("%c ", (char)stack->data[i]);
  }
  printf("\n");
}
