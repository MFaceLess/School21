CC=gcc
CFLAGS=-c -Wall -Wextra -Werror

all: s21_cat

s21_cat: cat.o
	$(CC) cat.o -o s21_cat

s21_cat.o: ../cat/cat.c
	$(CC) $(CFLAGS) ../cat/cat.c

clean:
	rm -rf *.o s21_cat

rebuild: clean all