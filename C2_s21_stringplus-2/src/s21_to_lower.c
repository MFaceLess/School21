#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *new_str = malloc(s21_strlen(str) + 1);
  s21_strcpy(new_str, str);
  int i = 0;
  while (*(str + i)) {
    *(new_str + i) = tolower(*(str + i));
    i++;
  }
  return new_str;
}
