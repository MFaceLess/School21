#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} opt;

void parser(int argc, char* argv[], opt* options);
void reader(char* argv[], opt* options);

void reader(char* argv[], opt* options) {
  int ind = optind;
  int cur;
  int str_count = 0;
  int counter;
  int counter_of_n;
  FILE* f;
  while (1) {
    if (argv[ind] == NULL) {
      return;
    }
    f = fopen(argv[ind], "r");
    counter = 0;
    counter_of_n = 0;
    if (f) {
      while ((cur = fgetc(f)) != EOF) {
        if (options->b) {
          if (cur != '\n') {
            if (counter == 0) {
              printf("%6d\t", ++str_count);
              counter = 1;
            }
          } else {
            counter = 0;
          }
        } else if (options->n) {
          if (cur != '\n') {
            if (counter == 0) {
              printf("%6d\t", ++str_count);
              counter = 1;
            }
          } else {
            if (counter == 0) {
              printf("%6d\t", ++str_count);
            }
            counter = 0;
          }
        }
        if (options->t && cur == '\t') {
          printf("^I");
          continue;
        }
        if (cur == '\n') {
          counter_of_n += 1;
        } else {
          counter_of_n = 0;
        }
        if (options->s && counter_of_n >= 3) {
          continue;
        }
        if (options->v) {
          if (cur >= 0 && cur <= 31 && cur != '\n' && cur != '\t' &&
              cur != '\0') {
            switch (cur) {
              case 7:
                printf("^G");
                break;
              case 8:
                printf("^H");
                break;
              case 11:
                printf("^K");
                break;
              case 12:
                printf("^L");
                break;
              case 13:
                printf("^M");
                break;
              default:
                printf("^M");
                break;
            }
            continue;
          }
        }
        if (options->e) {
          if (cur == '\n') {
            printf("$");
          }
        }
        printf("%c", cur);
      }
      fclose(f);
      ind++;
    } else {
      printf("No such file");
      exit(1);
    }
  }
}

void parser(int argc, char* argv[], opt* options) {
  int opt;
  int option_index;
  const struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                        {"number", 0, 0, 'n'},
                                        {"squeeze-blank", 0, 0, 's'},
                                        {0, 0, 0, 0}};

  opterr = 0;
  while ((opt = getopt_long(argc, argv, "benstvTE", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b': {
        options->b = 1;
        break;
      }
      case 'e': {
        options->e = 1;
        options->v = 1;
        break;
      }
      case 'E': {
        options->e = 1;
        break;
      }
      case 'n': {
        options->n = 1;
        break;
      }
      case 's': {
        options->s = 1;
        break;
      }
      case 't': {
        options->t = 1;
        options->v = 1;
        break;
      }
      case 'T': {
        options->t = 1;
        break;
      }
      case 'v': {
        options->v = 1;
        break;
      }
      case '?':
      default: {
        printf("Unknown option\n");
        exit(1);
        break;
      };
    }
  }
}

int main(int argc, char* argv[]) {
  opt options = {0};
  parser(argc, argv, &options);
  // printf("b = %d, e = %d, n = %d, s = %d, t = %d, v = %d\n", options.b,
  // options.e, options.n, options.s,
  //                                                        options.t,
  //                                                        options.v);
  reader(argv, &options);
  return 0;
}
