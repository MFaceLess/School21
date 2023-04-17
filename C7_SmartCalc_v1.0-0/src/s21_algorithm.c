#include "s21_SmartCalc.h"

char *Sort_Facility(char *input) {
  char *inpos = input;

  char *out = (char *)malloc(10 * strlen(input) * sizeof(char));
  char *outpos = out;

  Stack *temp = init();

  while (*inpos != '\0') {
    if (is_ident(*inpos) || *inpos == '.') {
      while (is_ident(*inpos) || *inpos == '.') {
        *outpos = *inpos;
        outpos++;
        inpos++;
      }
      *outpos = '|';
      outpos++;
      continue;
    } else if (is_function(*inpos)) {
      push(temp, *inpos);
    } else if (*inpos == ',') {
      int check = 0;
      while (temp->top > 0) {
        if ((char)temp->data[temp->top - 1] == '(') {
          check = 1;
          break;
        } else {
          *outpos = (char)pop(temp);
          outpos++;
        }
      }
      if (!check) {
        printf("Error in note!\n");
        destroy(&temp);
        free(out);
        return "Error";
      }
    } else if (is_operator(*inpos)) {
      while (temp->top > 0) {
        char symbol = temp->data[temp->top - 1];
        if (is_operator(symbol) &&
            ((op_left_assoc(*inpos) &&
              (op_preced(*inpos) <= op_preced(symbol))) ||
             (!op_left_assoc(*inpos) &&
              (op_preced(*inpos) < op_preced(symbol))))) {
          *outpos = (char)pop(temp);
          outpos++;
        } else {
          break;
        }
      }
      if (*inpos == '-' && !is_ident(*(inpos - 1)) && *(inpos - 1) != ')') {
        push(temp, '~');
      } else if (*inpos == '+' && !is_ident(*(inpos - 1)) &&
                 *(inpos - 1) != ')') {
        push(temp, ';');
      } else {
        push(temp, *inpos);
      }
    } else if (*inpos == '(') {
      push(temp, *inpos);
    } else if (*inpos == ')') {
      int check = 0;
      while (temp->top > 0) {
        char symbol = (char)temp->data[temp->top - 1];
        if (symbol == '(') {
          check = 1;
          break;
        } else {
          *outpos = (char)pop(temp);
          outpos++;
        }
      }
      if (!check) {
        printf("Error: parentheses mismatched\n");
        destroy(&temp);
        free(out);
        return "Error";
      }
      pop(temp);
      if (temp->top > 0) {
        char symbol = temp->data[temp->top - 1];
        if (is_function(symbol)) {
          *outpos = (char)pop(temp);
          outpos++;
        }
      }
    } else {
      printf("Unknown token %c\n", *inpos);
      destroy(&temp);
      free(out);
      return "Error";
    }
    inpos++;
  }
  while (temp->top > 0) {
    char symbol = temp->data[temp->top - 1];
    if (symbol == '(' || symbol == ')') {
      printf("Error: parentheses mismatched\n");
      destroy(&temp);
      free(out);
      return "Error";
    }
    *outpos = (char)pop(temp);
    outpos++;
  }
  *outpos = 0;

  // printf("Итог: %s\n", out);

  // char str[] = "65.12121212121212121212+65.55";
  // char* test = str;
  // // double temp1 = atof(test);
  // while (is_ident(*test) || *test == '.') {
  //     test++;
  // }
  // printf("test = %s\n", test);

  destroy(&temp);
  return out;
}

// c == '+' || c == '-' || c == '/' || c == '*' || c == '^' || c == '%' || c ==
// '=' || c == '~'

double Calculation(char *middle, int *check) {
  *check = 0;
  Stack *calculation = init();

  char *pointer = middle;
  while (*pointer != '\0') {
    if (is_ident(*pointer)) {
      double temp = atof(pointer);
      push(calculation, temp);
    }
    while (is_ident(*pointer) || *pointer == '.') {
      pointer++;
    }
    if (*pointer == '|') {
      pointer++;
    }
    if (is_operator(*pointer)) {
      if (*pointer == '+') {
        if (calculation->top < 2) {
          *check = 1;
          break;
        }
        double number2 = pop(calculation);
        double number1 = pop(calculation);
        push(calculation, number1 + number2);
      } else if (*pointer == '-') {
        if (calculation->top < 2) {
          *check = 1;
          break;
        }
        double number2 = pop(calculation);
        double number1 = pop(calculation);
        push(calculation, number1 - number2);
      } else if (*pointer == '/') {
        if (calculation->top < 2) {
          *check = 1;
          break;
        }
        double number2 = pop(calculation);
        double number1 = pop(calculation);
        push(calculation, number1 / number2);
      } else if (*pointer == '*') {
        if (calculation->top < 2) {
          *check = 1;
          break;
        }
        double number2 = pop(calculation);
        double number1 = pop(calculation);
        push(calculation, number1 * number2);
      } else if (*pointer == '^') {
        if (calculation->top < 2) {
          *check = 1;
          break;
        }
        double number2 = pop(calculation);
        double number1 = pop(calculation);
        push(calculation, pow(number1, number2));
      } else if (*pointer == '%') {
        if (calculation->top < 2) {
          *check = 1;
          break;
        }
        double number2 = pop(calculation);
        double number1 = pop(calculation);
        push(calculation, fmod(number1, number2));
      } else if (*pointer == '~') {
        double number1 = pop(calculation);
        push(calculation, 0.0 - number1);
      } else if (*pointer == ';') {
        double number1 = pop(calculation);
        push(calculation, number1);
      }
      pointer++;
    } else if (is_function(*pointer)) {
      if (*pointer == 'c') {
        double number1 = pop(calculation);
        push(calculation, cos(number1));
      } else if (*pointer == 's') {
        double number1 = pop(calculation);
        push(calculation, sin(number1));
      } else if (*pointer == 't') {
        double number1 = pop(calculation);
        push(calculation, tan(number1));
      } else if (*pointer == 'o') {
        double number1 = pop(calculation);
        push(calculation, acos(number1));
      } else if (*pointer == 'i') {
        double number1 = pop(calculation);
        push(calculation, asin(number1));
      } else if (*pointer == 'a') {
        double number1 = pop(calculation);
        push(calculation, atan(number1));
      } else if (*pointer == 'q') {
        double number1 = pop(calculation);
        push(calculation, sqrt(number1));
      } else if (*pointer == 'l') {
        double number1 = pop(calculation);
        push(calculation, log(number1));
      } else if (*pointer == 'g') {
        double number1 = pop(calculation);
        push(calculation, log10(number1));
      }
      pointer++;
    }
  }
  double result = pop(calculation);

  if (calculation->top != 0) {
    *check = 1;
  }

  free(middle);
  destroy(&calculation);
  return result;
}

int op_preced(const char c) {
  switch (c) {
    case ';':
    case '~':
      return 5;

    case '^':
      return 4;

    case '*':
    case '/':
    case '%':
      return 3;

    case '+':
    case '-':
      return 2;

    case '=':
      return 1;
  }
  return 0;
}

int op_left_assoc(const char c) {
  switch (c) {
    // лево-ассоциативные операторы
    case '*':
    case '/':
    case '%':
    case '+':
    case '-':
    case '=':
      return 1;
    // право-ассоциативные операторы
    case ';':  // унарный плюс(нахер не нужен, если у пользователя руки не из
               // жопы)
    case '~':  // унарный минус
    case '^':
      return 0;
  }
  return 0;
}

// char* stroka = "s(-90*3.14/180)";

// char* out = Sort_Facility(stroka);
// printf("Итог: %s\n", out);

// double result = Calculation(out);

// printf("result = %f\n", result);
