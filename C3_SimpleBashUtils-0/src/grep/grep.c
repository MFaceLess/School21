#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100000

typedef struct options {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} opt;

int match(char* string, char* pattern, regex_t* re);
void parser(int argc, char* argv[], opt* options, char* e_optarg,
            char* f_optarg);
void reader(char* argv[], opt* options, char* e_optarg, char* f_optarg);
char* lower(char shit[]);
static char* substr(char* str, unsigned start, unsigned end);
void match_for_a(char* string, char* pattern, regex_t* re, int check_n,
                 int check_i, int check_h, char* argv[], int ind,
                 int counter_of_line);

int main(int argc, char* argv[]) {
  opt options = {0};
  char e_optarg[BUFSIZE];
  char f_optarg[BUFSIZE];
  parser(argc, argv, &options, e_optarg, f_optarg);

  // printf("e = %d, i = %d, v = %d, c = %d, l = %d, n = %d, h = %d, s = %d, f =
  // %d, o = %d\n", options.e, options.i, options.v, options.c, options.l,
  // options.n, options.h, options.s, options.f, options.o);

  reader(argv, &options, e_optarg, f_optarg);

  return 0;
}

int match(char* string, char* pattern, regex_t* re) {
  int status;
  if ((status = regcomp(re, pattern, REG_EXTENDED)) != 0) return (status);
  status = regexec(re, string, 0, NULL, 0);
  regfree(re);
  return status;
}

void parser(int argc, char* argv[], opt* options, char* e_optarg,
            char* f_optarg) {
  int opt;
  int option_index;
  const struct option long_options[] = {{"regexp", 0, 0, 'e'},
                                        {"ignore-case", 0, 0, 'i'},
                                        {"invert-match", 0, 0, 'v'},
                                        {"count", 0, 0, 'c'},
                                        {"files-with-matches", 0, 0, 'l'},
                                        {"line-number", 0, 0, 'n'},
                                        {"no-filename", 0, 0, 'h'},
                                        {"no-messages", 0, 0, 's'},
                                        {"file", 0, 0, 'f'},
                                        {"only-matching", 0, 0, 'o'},
                                        {0, 0, 0, 0}};

  opterr = 0;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'e': {
        options->e = 1;
        strcpy(e_optarg, optarg);
        break;
      }
      case 'i': {
        options->i = 1;
        break;
      }
      case 'v': {
        options->v = 1;
        break;
      }
      case 'c': {
        options->c = 1;
        break;
      }
      case 'l': {
        options->l = 1;
        break;
      }
      case 'n': {
        options->n = 1;
        break;
      }
      case 'h': {
        options->h = 1;
        break;
      }
      case 's': {
        options->s = 1;
        break;
      }
      case 'f': {
        options->f = 1;
        strcpy(f_optarg, optarg);
        break;
      }
      case 'o': {
        options->o = 1;
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

void reader(char* argv[], opt* options, char* e_optarg, char* f_optarg) {
  if (argv[optind] == NULL) {
    return;
  }
  regex_t re;
  char* estr;
  char str[BUFSIZE];
  char pattern[BUFSIZE];
  int ind;
  if (options->f) {
    FILE* pattern_file = fopen(f_optarg, "r");
    if (pattern_file) {
      estr = fgets(str, sizeof(str), pattern_file);
      if (estr == NULL) {
        printf("Error!!!!");
        exit(1);
      }
      strcpy(pattern, estr);
      ind = optind;
      fclose(pattern_file);
    } else {
      printf("Error!!!!\n");
      exit(1);
    }
  } else if (options->e) {
    strcpy(pattern, e_optarg);
    ind = optind;
  } else {
    strcpy(pattern, argv[optind]);
    ind = optind + 1;
  }
  int counter = 0;
  int counter_of_line = 0;
  int global_retval = 1;
  FILE* f;
  int check_for_manyFiles = 0;
  while (1) {
    if (argv[ind] == NULL) {
      return;
    }
    if (argv[ind + 1] != NULL) {
      check_for_manyFiles = 1;
    }
    f = fopen(argv[ind], "r");
    counter_of_line = 0;
    counter = 0;
    if (f) {
      while (1) {
        estr = fgets(str, sizeof(str), f);
        if (estr == NULL) {
          break;
        }
        int retval = match(str, pattern, &re);
        counter_of_line++;
        if (options->i) {
          char* check1 = lower(str);
          char* check2 = lower(pattern);
          int compare = match(check1, check2, &re);
          if (compare == 0) {
            retval = 0;
          } else {
            retval = 1;
          }
          free(check1);
          free(check2);
        }
        if (options->v) {
          if (retval == 0) {
            retval = 1;
          } else {
            retval = 0;
          }
        }
        if (options->c) {
          if (retval == 0) {
            counter++;
          }
        }
        if (options->h) {
          check_for_manyFiles = 0;
        }
        if (options->n && !(options->l) && !(options->c) && !(options->o)) {
          if (retval == 0) {
            if (check_for_manyFiles) {
              printf("%s:", argv[ind]);
            }
            printf("%d:", counter_of_line);
            printf("%s", estr);
          }
        }
        if (options->o && !(options->l) && !(options->c)) {
          int check_n, check_i, check_h;
          if (options->n) {
            check_n = 1;
          }
          if (options->i) {
            check_i = 1;
          }
          if (options->h) {
            check_h = 0;
          } else {
            check_h = check_for_manyFiles;
          }
          if (retval == 0) {
            match_for_a(str, pattern, &re, check_n, check_i, check_h, argv, ind,
                        counter_of_line);
          }
        }
        if (options->l) {
          if (retval == 0) {
            global_retval = 0;
          }
        }
        if ((options->e || !(options->e)) && !(options->l) && !(options->n) &&
            !(options->c) && !(options->o)) {
          if (retval == 0) {
            if (check_for_manyFiles) {
              printf("%s:", argv[ind]);
            }
            printf("%s", str);
          }
        }
      }
      if (options->l) {
        if (global_retval == 0) {
          printf("%s\n", argv[ind]);
        }
      }
      if (options->c && !(options->l)) {
        if (check_for_manyFiles) {
          printf("%s:", argv[ind]);
        }
        printf("%d\n", counter);
      }
      fclose(f);
      ind++;
    } else {
      if (!(options->s)) {
        printf("No such file\n");
      }
      ind++;
      continue;
    }
  }
}

char* lower(char shit[]) {
  char* fucker = malloc(sizeof(char) * BUFSIZE);
  strcpy(fucker, shit);
  char* temp = fucker;
  while (*temp) {
    *temp = tolower(*temp);
    temp++;
  }
  return fucker;
}

static char* substr(char* str, unsigned start, unsigned end) {
  unsigned n = end - start;
  static char stbuf[256];
  strncpy(stbuf, str + start, n);
  stbuf[n] = 0;
  return stbuf;
}

void match_for_a(char* string, char* pattern, regex_t* re, int check_n,
                 int check_i, int check_h, char* argv[], int ind,
                 int counter_of_line) {
  regmatch_t pm[10];
  size_t nmatch = 10;
  if (check_i == 1) {
    regcomp(re, pattern, REG_ICASE);
  } else {
    regcomp(re, pattern, REG_EXTENDED);
  }
  char* temp = malloc(sizeof(char) * strlen(string));
  char* for_free = temp;
  strncpy(temp, string, strlen(string));
  regexec(re, temp, nmatch, pm, 0);
  int old;
  int new;
  do {
    old = pm[0].rm_eo;
    if (check_h == 0) {
      if (check_n == 1) {
        printf("%d:%s\n", counter_of_line,
               substr(temp, pm[0].rm_so, pm[0].rm_eo));
      } else {
        printf("%s\n", substr(temp, pm[0].rm_so, pm[0].rm_eo));
      }
    } else {
      if (check_n == 1) {
        printf("%s:%d:%s\n", argv[ind], counter_of_line,
               substr(temp, pm[0].rm_so, pm[0].rm_eo));
      } else {
        printf("%s:%s\n", argv[ind], substr(temp, pm[0].rm_so, pm[0].rm_eo));
      }
    }
    temp += pm[0].rm_eo;
    regexec(re, temp, nmatch, pm, 0);
    new = pm[0].rm_eo;
  } while (new != old);
  regfree(re);
  free(for_free);
}
