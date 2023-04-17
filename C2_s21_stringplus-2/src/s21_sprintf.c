#include "s21_string.h"

struct option {
  int width;
  int prec;
  int space;
  int len;
  int ljust;
  int sign;
  int l;
  int h;
  int L;
  int u;
  int f;
  int base;
  int hash;
  int upper;
  int g;
  long long e;
  int zeroP;
};

#define noOption -1
#define widthOption 0
#define precOption 1
#define endOption 2

char *itoa(int value, char *result, int base, struct option *options) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result, *ptr1 = result, tmp_char;
  long long tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
        "uvwxyz"[35 + (tmp_value - value * base)];
    if (options->f == 0) {
      options->prec--;
    }
  } while (value);

  if (options->prec > -1 && options->f == 0) {
    while (options->prec) {
      *ptr++ = '0';
      options->prec--;
    }
  }

  if (tmp_value < 0) {
    *ptr++ = '-';
  } else if (tmp_value >= 0 && options->sign == 1) {
    *ptr++ = '+';
  } else if (options->space) {
    *ptr++ = ' ';
  }

  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

char *litoa(long long value, char *result, int base, struct option *options) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result, *ptr1 = result, tmp_char;
  long long tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
        "uvwxyz"[35 + (tmp_value - value * base)];
    if (options->f == 0) {
      options->prec--;
    }
  } while (value);

  if (options->prec > -1 && (options->f == 0 || options->zeroP == 1)) {
    while (options->prec) {
      *ptr++ = '0';
      options->prec--;
    }
  }

  if (tmp_value < 0) {
    *ptr++ = '-';
  } else if (tmp_value >= 0 && options->sign == 1) {
    *ptr++ = '+';
  } else if (options->space) {
    *ptr++ = ' ';
  }

  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

char *hitoa(short value, char *result, int base, struct option *options) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result, *ptr1 = result, tmp_char;
  long long tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
        "uvwxyz"[35 + (tmp_value - value * base)];
    options->prec--;
  } while (value);

  if (options->prec > -1) {
    while (options->prec) {
      *ptr++ = '0';
      options->prec--;
    }
  }

  if (tmp_value < 0) {
    *ptr++ = '-';
  } else if (tmp_value >= 0 && options->sign == 1) {
    *ptr++ = '+';
  } else if (options->space) {
    *ptr++ = ' ';
  }

  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

char *uitoa(unsigned int value, char *result, int base,
            struct option *options) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result, *ptr1 = result, tmp_char;
  long long tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
        "uvwxyz"[35 + (tmp_value - value * base)];
    options->prec--;
  } while (value);

  if (options->prec > -1) {
    while (options->prec) {
      *ptr++ = '0';
      options->prec--;
    }
  }

  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

char *ulitoa(unsigned long long value, char *result, int base,
             struct option *options) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result, *ptr1 = result, tmp_char;
  long long tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
        "uvwxyz"[35 + (tmp_value - value * base)];
    options->prec--;
  } while (value);

  if (options->prec > -1) {
    while (options->prec) {
      *ptr++ = '0';
      options->prec--;
    }
  }

  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

char *uhitoa(unsigned short value, char *result, int base,
             struct option *options) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result, *ptr1 = result, tmp_char;
  long long tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
        "uvwxyz"[35 + (tmp_value - value * base)];
    options->prec--;
  } while (value);

  if (options->prec > -1) {
    while (options->prec) {
      *ptr++ = '0';
      options->prec--;
    }
  }

  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

void ftoa(long double n, char *res, int afterpoint, struct option *options) {
  long long ipart = (long long)n;
  char currNum;
  long double fpart = n - (long double)ipart;
  char ibuff[BUFF_SIZE];

  litoa(ipart, ibuff, 10, options);
  s21_strcpy(res, ibuff);

  if (afterpoint != 0) {
    s21_strcat(res, ".");
  }
  if (fpart < 0) {
    fpart = -1 * fpart;
  }

  while (afterpoint > 0) {
    afterpoint--;
    if (afterpoint == 0) {
      if (((fpart * 10) - (long long)((fpart + 1e-9) * 10)) * 10 >= 5) {
        currNum = '0' + (long long)((fpart + 1e-9) * 10) + 1;
      } else {
        currNum = '0' + (long long)((fpart + 1e-9) * 10);
      }
    } else {
      currNum = '0' + (long long)((fpart + 1e-9) * 10);
    }

    s21_strncat(res, &currNum, 1);
    fpart = (fpart * 10) - (long long)((fpart + 1e-9) * 10);
  }
}

char *elitoa(long long value, char *result, int base, struct option *options) {
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result, *ptr1 = result, tmp_char;
  long long tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
        "uvwxyz"[35 + (tmp_value - value * base)];
    if (options->f == 0) {
      options->prec--;
    }
  } while (value);
  if (options->prec > -1 && (options->f == 0 || options->zeroP == 1)) {
    while (options->prec - 4 - (8)) {
      *ptr++ = '0';
      options->prec--;
    }
  }

  if (tmp_value < 0) {
    *ptr++ = '-';
  } else if (tmp_value >= 0 && options->sign == 1) {
    *ptr++ = '+';
  } else if (options->space) {
    *ptr++ = ' ';
  }

  *ptr-- = '\0';
  while (ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}

void eftoal(long double n, char *res, int afterpoint, struct option *options) {
  long long ipart = (long long)n;
  char currNum;
  long double fpart = n - (long double)ipart;
  if (fpart * 10 >= 5 && options->prec == 0) {
    ipart++;
  }
  if (n != n) {
    ipart = 0;
  }
  char ibuff[BUFF_SIZE];
  elitoa(ipart, ibuff, 10, options);
  s21_strcpy(res, ibuff);
  if (afterpoint != 0) {
    s21_strcat(res, ".");
  }
  if (fpart < 0) {
    fpart = -1 * fpart;
  }

  while (afterpoint > 0) {
    afterpoint--;
    if (afterpoint == 0) {
      if (((fpart * 10) - (long long)((fpart)*10)) * 10 >= 5 &&
          ((long long)((fpart)*10)) != 9) {
        currNum = '0' + (long long)((fpart)*10) + 1;
      } else {
        currNum = '0' + (long long)((fpart)*10);
      }
    } else {
      currNum = '0' + (long long)((fpart)*10);
    }

    s21_strncat(res, &currNum, 1);
    fpart = (fpart * 10) - (long long)((fpart)*10);
  }
}

void eftoa(double n, char *res, int afterpoint, struct option *options) {
  long long ipart = (long long)n;
  char currNum;
  double fpart = n - (double)ipart;
  if (fpart * 10 >= 5 && options->prec == 0) {
    ipart++;
  }
  if (n != n) {
    ipart = 0;
  }
  char ibuff[BUFF_SIZE];
  elitoa(ipart, ibuff, 10, options);
  s21_strcpy(res, ibuff);
  if (afterpoint != 0) {
    s21_strcat(res, ".");
  }
  if (fpart < 0) {
    fpart = -1 * fpart;
  }

  while (afterpoint > 0) {
    afterpoint--;
    if (afterpoint == 0) {
      if (((fpart * 10) - (long long)((fpart)*10)) * 10 >= 5 &&
          ((long long)((fpart)*10)) != 9) {
        currNum = '0' + (long long)((fpart)*10) + 1;
      } else {
        currNum = '0' + (long long)((fpart)*10);
      }
    } else {
      currNum = '0' + (long long)((fpart)*10);
    }

    s21_strncat(res, &currNum, 1);
    fpart = (fpart * 10) - (long long)((fpart)*10);
  }
}

void resetOption(struct option *options) {
  options->width = -1;
  options->prec = -1;
  options->space = 0;
  options->len = 0;
  options->ljust = 0;
  options->sign = 0;
  options->l = 0;
  options->h = 0;
  options->L = 0;
  options->u = 0;
  options->f = 0;
  options->base = 0;
  options->hash = 0;
  options->upper = 0;
  options->e = -2281337;
  options->zeroP = 0;
  options->g = 0;
}

void formatString(struct option *options, char *buff, char *str) {
  int i = 0;
  char currChar = *str;
  int formatW;

  if (options->prec == -1 || options->prec > (int)s21_strlen(str)) {
    formatW = (int)s21_strlen(str);
  } else {
    formatW = options->prec;
  }
  if (options->width != -1) {
    if (options->width <= formatW) {
    } else if (options->ljust == 0) {
      for (int i = 0; i < options->width - formatW; i++) {
        s21_strncat(buff, " ", 1);
      }
    }
  }

  while (*(str + i) != '\0' && (options->prec <= -1 || options->prec > 0)) {
    currChar = *(str + i);
    s21_strncat(buff, &currChar, 1);
    i++;
    options->prec--;
  }
  if (options->ljust == 1 && options->width > formatW) {
    for (int i = 0; i < options->width - formatW; i++) {
      s21_strncat(buff, " ", 1);
    }
  }
}

void formatDecimal(struct option *options, char *buff, long long num) {
  int i = 0;
  char *str = malloc(BUFF_SIZE);
  s21_strcpy(str, "");
  char currChar;
  int shift = 0;

  if (num == 0 && options->prec == 0) {
  } else if (options->l) {
    if (options->u) {
      ulitoa(num, str, options->base, options);
    } else {
      litoa(num, str, options->base, options);
    }

  } else if (options->h) {
    if (options->u) {
      uhitoa(num, str, options->base, options);
    } else {
      hitoa(num, str, options->base, options);
    }
  } else {
    if (options->u) {
      uitoa(num, str, options->base, options);
    } else {
      itoa(num, str, options->base, options);
    }
  }

  if (num != 0 && (options->hash != 0 || options->upper == 2)) {
    if (options->base == 8) {
      shift = 1;
    } else if (options->base == 16 && options->upper == 1) {
      shift = 2;
    } else if (options->base == 16 && options->upper == 2) {
      shift = 4;
    } else if (options->base == 16) {
      shift = 2;
    }
  } else if (num == 0 && options->upper == 2) {
    shift = 2;
  }

  if (options->upper == 1) {
    int i = 0;
    while (*(str + i)) {
      *(str + i) = toupper(*(str + i));
      i++;
    }
  }

  if (options->width != -1) {
    if (options->width <= (int)s21_strlen(str) + shift) {
    } else if (options->ljust == 0) {
      for (int i = 0; i < options->width - (int)s21_strlen(str) - shift; i++) {
        s21_strncat(buff, " ", 1);
      }
    }
  }

  if (num != 0 && (options->hash != 0 || options->upper == 2)) {
    if (options->base == 8) {
      s21_strncat(buff, "0", 1);
    } else if (options->base == 16 && options->upper == 1) {
      s21_strncat(buff, "0X", 2);
    } else if (options->base == 16 && options->upper == 2) {
      s21_strncat(buff, "0x10", 4);
    } else if (options->base == 16) {
      s21_strncat(buff, "0x", 2);
    }
  } else if (num == 0 && options->upper == 2) {
    s21_strncat(buff, "0x", 2);
  }

  while (*(str + i) != '\0') {
    currChar = *(str + i);
    s21_strncat(buff, &currChar, 1);
    i++;
  }
  if (options->ljust == 1 && options->width > (int)s21_strlen(str) + shift) {
    for (int i = 0; i < options->width - (int)s21_strlen(str) - shift; i++) {
      s21_strncat(buff, " ", 1);
    }
  }
  free(str);
}

void remove_trailing_zeroes(char *buff) {
  int len = s21_strlen(buff);
  char *dot = s21_strchr(buff, '.');
  if (dot) {
    for (int i = len - 1; buff[i] != s21_dot; i--) {
      if (buff[i] == '0')
        buff[i] = '\0';
      else
        break;
    }
    if (dot[1] == '\0') dot[0] = '\0';
  }
}

void formatFloat(struct option *options, char *buff, long double num) {
  int i = 0;
  char *str = malloc(BUFF_SIZE);
  char currChar;
  int afterpoint = options->prec;

  if (options->zeroP == 1) {
    afterpoint = 6;
  }

  if (options->e == -2281337) {
    if (options->prec != -1) {
      ftoa(num, str, afterpoint, options);
    } else {
      ftoa(num, str, 6, options);
    }
  } else {
    if (options->prec != -1) {
      if (options->L != -1) {
        eftoal(num, str, afterpoint, options);
      } else {
        eftoa(num, str, afterpoint, options);
      }
    } else {
      if (options->L != -1) {
        eftoal(num, str, 6, options);
      } else {
        eftoa(num, str, 6, options);
      }
    }
  }

  if (options->g == 1) {
    remove_trailing_zeroes(str);
  }

  if (options->e != -2281337 && options->upper == 1) {
    char exp[6];
    s21_sprintf(exp, "E%+02d", options->e);
    s21_strncat(str, exp, 5);
  } else if (options->e != -2281337) {
    char exp[6];
    s21_sprintf(exp, "e%+02d", options->e);
    s21_strncat(str, exp, 5);
  }

  if (options->width != -1) {
    if (options->width <= (int)s21_strlen(str)) {
    } else if (options->ljust == 0) {
      for (int i = 0; i < options->width - (int)s21_strlen(str); i++) {
        s21_strncat(buff, " ", 1);
      }
    }
  }

  while (*(str + i) != '\0') {
    currChar = *(str + i);
    s21_strncat(buff, &currChar, 1);
    i++;
  }
  if (options->ljust == 1 && options->width > (int)s21_strlen(str)) {
    for (int i = 0; i < options->width - (int)s21_strlen(str); i++) {
      s21_strncat(buff, " ", 1);
    }
  }
  free(str);
}

int find_nonzero(double num) {
  int pow = 0;
  while (num < 1) {
    num = num * 10;
    pow++;
  }
  return pow;
}

double num_find_nonzero(double num) {
  int pow = 0;
  while (num < 1) {
    num = num * 10;
    pow++;
  }
  return num;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list va;
  va_start(va, format);

  struct option options;
  resetOption(&options);

  char charArg;

  char *buff = malloc(BUFF_SIZE + 1);
  char *strArg = malloc(BUFF_SIZE + 1);
  s21_strcpy(buff, "");

  unsigned long intArg;
  long double doubleArg;
  int i = 0;
  int argFlag = 0;
  int currFlag = noOption;
  char currChar = *format;

  while (format != s21_NULL && *(format + i) != '\0') {
    currChar = *(format + i);
    if (currChar == '%' && argFlag == 0) {
      argFlag = 1;
      currFlag = noOption;
    } else if (argFlag == 0) {
      s21_strncat(buff, &currChar, 1);
    } else if (argFlag == 1) {
      if (isdigit(currChar)) {
        if (currFlag == noOption) {
          if (currChar == '0') {
            options.zeroP = 1;
            currFlag = precOption;
            options.prec = 0;
          } else {
            currFlag = widthOption;
            options.width = currChar - '0';
          }
        } else if (currFlag == widthOption) {
          options.width = options.width * 10 + currChar - '0';
        } else if (currFlag == precOption) {
          options.prec = options.prec * 10 + currChar - '0';
        }
      } else if (currChar == '.') {
        if (currFlag != precOption) {
          currFlag = precOption;
          options.prec = 0;
        } else {
          options.width = 0;
          options.zeroP = 0;
          options.prec = 0;
        }
      } else if (currChar == '-') {
        options.ljust = 1;
        currFlag = noOption;
      } else if (currChar == '+') {
        options.sign = 1;
        currFlag = noOption;
      } else if (currChar == ' ') {
        options.space = 1;
        currFlag = noOption;
      } else if (currChar == 'h') {
        options.h = 1;
        currFlag = noOption;
      } else if (currChar == 'l') {
        options.l = 1;
        currFlag = noOption;
      } else if (currChar == 'L') {
        options.L = 1;
        currFlag = noOption;
      } else if (currChar == '#') {
        options.hash = 1;
        currFlag = noOption;
      } else if (currChar == '*') {
        if (currFlag == precOption) {
          options.prec = va_arg(va, int);
        } else {
          options.width = va_arg(va, int);
        }
        currFlag = noOption;
      } else {
        argFlag = 0;
        currFlag = endOption;
      }
    }
    if (currFlag == endOption) {
      if (currChar == 'c' || currChar == '%') {
        options.prec = -1;
        if (currChar == '%') {
          formatString(&options, buff, "%");
        } else {
          charArg = va_arg(va, int);
          s21_strcpy(strArg, &charArg);
          strArg[1] = 0;
          formatString(&options, buff, strArg);
        }

      } else if (currChar == 's') {
        s21_strcpy(strArg, va_arg(va, char *));
        formatString(&options, buff, strArg);

      } else if (currChar == 'p') {
        options.base = 16;
        options.upper = 2;
        intArg = (long)va_arg(va, void *);
        formatDecimal(&options, buff, intArg);

      } else if (currChar == 'd' || currChar == 'i') {
        options.base = 10;
        intArg = va_arg(va, long);
        formatDecimal(&options, buff, intArg);
      } else if (currChar == 'o') {
        options.base = 8;
        intArg = va_arg(va, long);
        formatDecimal(&options, buff, intArg);
      } else if (currChar == 'b') {
        options.base = 2;
        intArg = va_arg(va, long);
        formatDecimal(&options, buff, intArg);
      } else if (currChar == 'u') {
        options.base = 10;
        options.u = 1;
        intArg = va_arg(va, long);
        formatDecimal(&options, buff, intArg);
      } else if (currChar == 'x') {
        options.base = 16;
        options.u = 1;
        intArg = va_arg(va, long);
        formatDecimal(&options, buff, intArg);
      } else if (currChar == 'X') {
        options.base = 16;
        options.upper = 1;
        options.u = 1;
        intArg = va_arg(va, long);
        formatDecimal(&options, buff, intArg);
      } else if (currChar == 'f') {
        options.base = 10;
        options.f = 1;
        if (options.L) {
          doubleArg = va_arg(va, long double);
        } else {
          doubleArg = va_arg(va, double);
        }
        formatFloat(&options, buff, doubleArg);
      } else if (currChar == 'g' || currChar == 'G') {
        options.g = 1;
        options.base = 10;
        options.f = 1;
        if (options.L) {
          doubleArg = va_arg(va, long double);
        } else {
          doubleArg = va_arg(va, double);
        }
        long long inum = (long long)log10l(fabsl(doubleArg));
        if (options.prec == -1 && inum > 0) {
          options.prec = 5 - inum;
        } else if (options.prec == -1) {
          options.prec = 6;
        }
        if (options.prec == 0 && inum > -6) {
          options.prec = find_nonzero(doubleArg);
        } else if (inum <= -5 && doubleArg != 0) {
          options.e = inum - 1;
          if (currChar == 'G') {
            options.upper = 1;
          }
          doubleArg = (doubleArg / pow(10, options.e));
        }

        formatFloat(&options, buff, doubleArg);
      } else if (currChar == 'e' || currChar == 'E') {
        if (currChar == 'E') {
          options.upper = 1;
        }
        options.base = 10;
        options.f = 1;
        if (options.L) {
          doubleArg = va_arg(va, long double);
          options.e = (long long)log10l(fabsl(doubleArg));
          if (options.e < 0) {
            options.e--;
          }
          long double mantissa = (doubleArg / powl(10, options.e));
          doubleArg = mantissa;
        } else {
          doubleArg = va_arg(va, double);
          options.e = (long long)log10(fabsl(doubleArg));
          if (options.e > -1e10 && options.e < 0) {
            options.e--;
          }
          double mantissa = (doubleArg / pow(10, options.e));
          doubleArg = mantissa;
        }
        formatFloat(&options, buff, doubleArg);
      }
      currFlag = noOption;
      resetOption(&options);
    }
    i++;
  }
  s21_strcpy(str, buff);

  int answ = (int)s21_strlen(buff);
  free(buff);
  free(strArg);
  va_end(va);
  return answ;
}
