CC=gcc
CFLAGS=-c -Wall -Wextra -Werror

all: s21_grep 

s21_grep: grep.o
	$(CC) grep.o -o s21_grep

s21_grep.o: ../grep/grep.c
	$(CC) $(CFLAGS) ../grep/grep.c

clean:
	rm -rf *.o s21_grep

rebuild: clean all
