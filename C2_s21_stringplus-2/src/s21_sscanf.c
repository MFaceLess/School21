#include "s21_string.h"

struct Arguments {
  short asterisk;
  int width;
  char modifier;
  int success;
};

int flag_d(va_list valist, const char *str, struct Arguments *Arglist);
void flag_d_write_to_destination(va_list valist, struct Arguments *Arglist,
                                 long int *result);
int flag_c(va_list valist, const char *str, struct Arguments *Arglist);
int flag_s(va_list valist, const char *str, struct Arguments *Arglist);
int flag_f(va_list valist, const char *str, struct Arguments *Arglist,
           int *total_count);
void flag_f_write_to_destination(va_list valist, struct Arguments *Arglist,
                                 long double *result);
int flag_e(const char *str, long double *result, int *symbols_count,
           struct Arguments *Arglist);
int flag_u(va_list valist, const char *str, struct Arguments *Arglist);
int flag_o(va_list valist, const char *str, struct Arguments *Arglist);
int flag_x(va_list valist, const char *str, struct Arguments *Arglist);
long flag_x_read(const char *str, struct Arguments *Arglist,
                 int *symbols_count);
int flag_i(va_list valist, const char *str, struct Arguments *Arglist);
int flag_p(va_list valist, const char *str, struct Arguments *Arglist);
long s21_sscanf_atoi(const char *str, struct Arguments *Arglist,
                     int *symbols_count);

int s21_sscanf(const char *str, const char *format, ...) {
  int count = 0;
  long a_symbols_count = 0;
  va_list valist;
  va_start(valist, format);

  while (*format) {
    if (*format++ == '%') {
      long c_symbols_count = 0;
      char keys[] = "csdieEfgGouxXpn%";
      struct Arguments Arglist = {0, -1, '\0', 0};
      do {
        switch (*format) {
          case '*':
            Arglist.asterisk = 1;
            break;
          case '0' ... '9':
            if (Arglist.width == -1)
              Arglist.width = (*format - '0');
            else
              Arglist.width = Arglist.width * 10 + (*format - '0');
            break;
          case 'h':
          case 'l':
          case 'L':
            Arglist.modifier = *format;
            break;
          case 'd':
            c_symbols_count += flag_d(valist, str, &Arglist);
            break;
          case 'c':
            c_symbols_count += flag_c(valist, str, &Arglist);
            break;
          case 's':
            c_symbols_count += flag_s(valist, str, &Arglist);
            break;
          case 'e':
          case 'E':
          case 'g':
          case 'G':
          case 'f':
            c_symbols_count += flag_f(valist, str, &Arglist, &count);
            break;
          case 'u':
            c_symbols_count += flag_u(valist, str, &Arglist);
            break;
          case 'o':
            c_symbols_count += flag_o(valist, str, &Arglist);
            break;
          case 'X':
          case 'x':
            c_symbols_count += flag_x(valist, str, &Arglist);
            break;
          case 'i':
            c_symbols_count += flag_i(valist, str, &Arglist);
            break;
          case 'p':
            c_symbols_count += flag_p(valist, str, &Arglist);
            break;
          case 'n':
            while (*str == ' ') {
              str++;
              a_symbols_count++;
            }
            Arglist.success = 1;
            flag_d_write_to_destination(valist, &Arglist, &a_symbols_count);
            break;
          case '%':
            while (*str == ' ' || *str == '%') {
              Arglist.success = -1;
              a_symbols_count++;
              str++;
            }
            break;
        }
      } while (s21_strchr(keys, *format++) == s21_NULL);
      if (Arglist.success == 0) break;
      if (Arglist.asterisk) Arglist.success = 0;
      count += Arglist.success;
      str += c_symbols_count;
      a_symbols_count += c_symbols_count;
    }
  }
  va_end(valist);
  return count ? count : -1;
}

int flag_d(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_count = 0;
  long result = s21_sscanf_atoi(str, Arglist, &symbols_count);
  if (Arglist->asterisk == 0)
    flag_d_write_to_destination(valist, Arglist, &result);
  return symbols_count;
}

void flag_d_write_to_destination(va_list valist, struct Arguments *Arglist,
                                 long int *result) {
  if (Arglist->modifier == '\0') {
    int *destination = va_arg(valist, int *);
    *destination = (int)*result;
  } else if (Arglist->modifier == 'h') {
    short *destination = va_arg(valist, short *);
    *destination = (short)*result;
  } else if (Arglist->modifier == 'l') {
    long *destination = va_arg(valist, long *);
    *destination = (long)*result;
  }
}

int flag_i(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_count = 0;
  while (*str == ' ') {
    str++;
    symbols_count++;
  }
  if (*str == '0') {
    str++;
    symbols_count++;
    if (*str == 'x') {
      symbols_count += flag_x(valist, str, Arglist);
    } else {
      symbols_count += flag_o(valist, str, Arglist);
    }
  } else if ((*str >= '0' && *str <= '9') || *str == '-' || *str == '+') {
    symbols_count += flag_d(valist, str, Arglist);
  }
  return symbols_count;
}

int flag_x(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_count = 0;
  long decimal = flag_x_read(str, Arglist, &symbols_count);
  if (Arglist->asterisk == 0)
    flag_d_write_to_destination(valist, Arglist, &decimal);
  return symbols_count;
}

long flag_x_read(const char *str, struct Arguments *Arglist,
                 int *symbols_count) {
  long decimal = 0;
  int sign = 1;

  while (*str == ' ' || *str == '-' || *str == '+' || *str == '0' ||
         *str == 'x') {
    if (*str == '-') sign = -1;
    str++;
    (*symbols_count)++;
  }
  char hex_num[50] = {'\0'};
  int i = 0;
  while ((*str && *str != ' ' && *str != '\n' && Arglist->width--) ||
         ((hex_num[i] >= '0' && hex_num[i] <= '9') ||
          (hex_num[i] >= 'a' && hex_num[i] <= 'f') ||
          (hex_num[i] >= 'A' && hex_num[i] <= 'F'))) {
    (*symbols_count)++;
    hex_num[i++] = *str++;
  }
  int len = s21_strlen(hex_num);
  int temp = 0;
  for (i = 0; hex_num[i] != '\0'; i++) {
    if (hex_num[i] >= '0' && hex_num[i] <= '9') {
      temp = hex_num[i] - 48;
      Arglist->success = 1;
    } else if (hex_num[i] >= 'a' && hex_num[i] <= 'f') {
      temp = hex_num[i] - 87;
      Arglist->success = 1;
    } else if (hex_num[i] >= 'A' && hex_num[i] <= 'F') {
      temp = hex_num[i] - 55;
      Arglist->success = 1;
    }
    decimal += temp * pow(16, --len);
  }
  return decimal *= sign;
}

int flag_o(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_count = 0;
  long octal = s21_sscanf_atoi(str, Arglist, &symbols_count);
  long decimal = 0;

  while (*str == ' ' || *str == '-' || *str == '+' || *str == '0') str++;

  int i = 0;
  while (octal != 0 && Arglist->width--) {
    decimal = decimal + (octal % 10) * pow(8, i++);
    octal = octal / 10;
  }

  if (Arglist->asterisk == 0)
    flag_d_write_to_destination(valist, Arglist, &decimal);

  return symbols_count;
}

int flag_u(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_count = 0;
  if (Arglist->asterisk == 0) {
    if (Arglist->modifier == '\0') {
      unsigned int *destination = va_arg(valist, unsigned int *);
      long temp = s21_sscanf_atoi(str, Arglist, &symbols_count);
      *destination = (unsigned int)temp;
    } else if (Arglist->modifier == 'h') {
      unsigned short *destination = va_arg(valist, unsigned short *);
      long temp = s21_sscanf_atoi(str, Arglist, &symbols_count);
      *destination = (unsigned short)temp;
    } else if (Arglist->modifier == 'l') {
      unsigned long *destination = va_arg(valist, unsigned long *);
      long temp = s21_sscanf_atoi(str, Arglist, &symbols_count);
      *destination = (unsigned long)temp;
    }
  } else {
    s21_sscanf_atoi(str, Arglist, &symbols_count);
  }
  return symbols_count;
}

int flag_e(const char *str, long double *result, int *symbols_count,
           struct Arguments *Arglist) {
  str++;
  Arglist->width--;
  int e_symbols_count = 1;

  int n = s21_sscanf_atoi(str, Arglist, &e_symbols_count);

  if (*str == '+' || (*str >= '0' && *str <= '9')) {
    while (n--) *result *= 10.0;
  } else if (*str == '-') {
    while (n++) *result /= 10.0;
  }

  *symbols_count += e_symbols_count;
  return e_symbols_count;
}

int flag_f(va_list valist, const char *str, struct Arguments *Arglist,
           int *total_count) {
  int symbols_count = 0;
  long double left_from_dot_or_e =
      s21_sscanf_atoi(str, Arglist, &symbols_count);
  long double result = left_from_dot_or_e;

  int sign = 1;

  const char *str_temp = str;
  while (*str_temp == ' ') str_temp++;
  if (*str_temp == '-') sign = -1;

  str += symbols_count;

  switch (*str) {
    case '.':
      str++;
      int symbols_to_right_of_dot = 0;
      long double right_from_dot =
          s21_sscanf_atoi(str, Arglist, &symbols_to_right_of_dot);
      symbols_count += symbols_to_right_of_dot + 1;

      for (int n = symbols_to_right_of_dot; n > 0; n--) right_from_dot /= 10;

      if (!left_from_dot_or_e && !right_from_dot && sign == -1)
        result = -0.0;
      else if (sign == -1)
        result -= right_from_dot;
      else
        result += right_from_dot;

      str += symbols_to_right_of_dot;

      break;
    case 'e':
    case 'E':
      if (Arglist->width == 1) {
        flag_f_write_to_destination(valist, Arglist, &result);
        Arglist->success = 0;
        (*total_count)++;
        break;
      }
      str += flag_e(str, &result, &symbols_count, Arglist);
      break;
  }
  if (*str == 'e' || *str == 'E') flag_e(str, &result, &symbols_count, Arglist);

  if (Arglist->asterisk == 0 && Arglist->success)
    flag_f_write_to_destination(valist, Arglist, &result);
  return symbols_count;
}

void flag_f_write_to_destination(va_list valist, struct Arguments *Arglist,
                                 long double *result) {
  if (Arglist->modifier == 'l') {
    double *destination = va_arg(valist, double *);
    *destination = (double)*result;
  } else if (Arglist->modifier == 'L') {
    long double *destination = va_arg(valist, long double *);
    *destination = (long double)*result;
  } else {
    float *destination = va_arg(valist, float *);
    *destination = (float)*result;
  }
}

int flag_s(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_count = 0;
  while (*str == ' ' || *str == '\n') {
    str++;
    symbols_count++;
  }
  if (Arglist->asterisk == 0) {
    if (Arglist->modifier == 'l') {
      wchar_t *destination = va_arg(valist, wchar_t *);
      while (*str && *str != ' ' && *str != '\n' && Arglist->width--) {
        symbols_count++;
        *destination++ = *str++;
        Arglist->success = 1;
      }
      *destination = '\0';
    } else {
      char *destination = va_arg(valist, char *);
      while (*str && *str != ' ' && *str != '\n' && Arglist->width--) {
        symbols_count++;
        *destination++ = *str++;
        Arglist->success = 1;
      }
      *destination = '\0';
    }
  } else {
    while (*str && *str != ' ' && *str != '\n' && Arglist->width--) {
      str++;
      symbols_count++;
      Arglist->success = 1;
    }
  }

  return symbols_count;
}

int flag_c(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_count = 0;
  if (Arglist->width > 0) {
    symbols_count += flag_s(valist, str, Arglist);
  } else if (Arglist->asterisk == 0) {
    if (Arglist->modifier == 'l') {
      wchar_t *destination = va_arg(valist, wchar_t *);
      *destination = *str;
    } else {
      char *destination = va_arg(valist, char *);
      *destination = *str;
    }
    symbols_count++;
    Arglist->success = 1;
  }
  return symbols_count;
}

int flag_p(va_list valist, const char *str, struct Arguments *Arglist) {
  int symbols_count = 0;

  long decimal = flag_x_read(str, Arglist, &symbols_count);
  if (Arglist->asterisk == 0) {
    void **destination = va_arg(valist, void **);
    *destination = (void *)(0x0 + decimal);
  }

  return symbols_count;
}

long s21_sscanf_atoi(const char *str, struct Arguments *Arglist,
                     int *symbols_count) {
  long res = 0;
  int sign = 1;
  while (*str == ' ' || *str == '-' || *str == '+') {
    if (*str == '-') {
      sign = -1;
      Arglist->width--;
    } else if (*str == '+') {
      Arglist->width--;
    }
    str++;
    (*symbols_count)++;
  }
  while (*str >= '0' && *str <= '9' && Arglist->width--) {
    res = res * 10 + (*str - '0');
    str++;
    (*symbols_count)++;
    Arglist->success = 1;
  }
  return res * sign;
}
