#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  int res = 0;

  if (str1 && str2) {
    int i = 0;

    while (str1[i] && str1[i] == str2[i]) {
      i++;
    }

    res = str1[i] - str2[i];
  }

  return res;
}
