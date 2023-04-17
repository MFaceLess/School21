#include "s21_string.h"

static int contains(char const *set, char c) {
  s21_size_t i;
  i = 0;
  while (i < s21_strlen(set)) {
    if (set[i] == c) return (1);
    i++;
  }
  return (0);
}

void *s21_trim(const char *src, const char *trim_chars) {
  size_t s1_length;
  size_t i;
  char *result_start;
  char *result_end;
  char *result;
  char *space = " ";
  int spaceFlag = 0;

  if (!src) {
    return (calloc(2, sizeof(char)));
  }
  if (trim_chars == s21_NULL || s21_strlen(trim_chars) <= 0) {
    spaceFlag = 1;
  }
  s1_length = s21_strlen(src);
  i = 0;
  if (!spaceFlag) {
    while (contains(trim_chars, src[i]) && i < s1_length) {
      i++;
    }
    if (i == s1_length) {
      return (calloc(2, sizeof(char)));
    }

    result_start = (char *)&src[i];
    i = s1_length - 1;

    while (contains(trim_chars, src[i]) && i > 0) {
      i--;
    }
    result_end = (char *)&src[i + 1];
    result = malloc(sizeof(*result) * (result_end - result_start + 1));

    if (!result) {
      return (NULL);
    }

    s21_memcpy(result, result_start, result_end - result_start);
    result[result_end - result_start] = '\0';
    return (result);
  } else {
    while (contains(space, src[i]) && i < s1_length) {
      i++;
    }
    if (i == s1_length) {
      return (calloc(2, sizeof(char)));
    }

    result_start = (char *)&src[i];
    i = s1_length - 1;

    while (contains(space, src[i]) && i > 0) {
      i--;
    }
    result_end = (char *)&src[i + 1];
    result = malloc(sizeof(*result) * (result_end - result_start + 1));

    if (!result) {
      return (NULL);
    }

    s21_memcpy(result, result_start, result_end - result_start);
    result[result_end - result_start] = '\0';
    return (result);
  }
}
