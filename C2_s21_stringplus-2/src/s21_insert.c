#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if ((start_index <= s21_strlen(src))) {
    char *strC = malloc(s21_strlen(str) + s21_strlen(src) + 1);
    s21_strncpy(strC, src, start_index);
    strC[start_index] = '\0';
    if (str != s21_NULL) {
      s21_strcat(strC, str);
    }
    s21_strcat(strC, src + start_index);
    return strC;
  }
  return s21_NULL;
}
