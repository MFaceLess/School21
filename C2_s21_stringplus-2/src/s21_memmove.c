#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *to = (char *)dest;
  char *from = (char *)src;

  char *tmp = (char *)malloc(sizeof(char) * n);

  if (tmp) {
    s21_memcpy(tmp, from, n);
    s21_memcpy(to, tmp, n);
    free(tmp);
  }
  return dest;
}
