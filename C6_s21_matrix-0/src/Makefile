CC=gcc -std=c11 -D_GNU_SOURCE
TEST_LIBS=-lcheck -lm -lpthread 
GCOV_LIBS=--coverage
BUILD_PATH=./
SOURCES=s21_*.c
HEAD=s21_matrix.h
LIB_O=s21_matrix.o
LIB_A=s21_matrix.a
TEST=test.out

CC_FLAGS = -Wall -Werror -Wextra -std=c11
ASAN = -g -fsanitize=address
TESTFLAGS := -lcheck -coverage -lpthread -pthread 
GCOVFLAGS = -fprofile-arcs -ftest-coverage

C_FILES = s21_*.c 
O_FILES = s21_*.o

ifeq ($(shell uname -s),Linux)
	TESTFLAGS += -lrt -lm -lsubunit
endif

ifeq ($(shell uname -s),Linux)
	REPORT = gcov s21_*.gcno && gcovr --html > report.html
else ifeq ($(shell uname -s),Darwin)
	REPORT = gcov s21_*.gcno > report.html && cat report.html
endif

all: clean s21_matrix.a

rebuild: clean all

test: s21_matrix.a
	gcc test.c $(GCCFLAGS) $(TESTFLAGS) -L. s21_matrix.a -o test $(TESTFLAGS)
	./test

example: s21_matrix.a
	gcc main.c $(CC_FLAGS) $(TESTFLAGS) -L. s21_matrix.a -o example $(TESTFLAGS)
	./example

s21_matrix.a: all_functions
	ar rcs s21_matrix.a $(O_FILES) s21_matrix.h
	ranlib s21_matrix.a

gcov_report: all_functions_gcov
	ar -rv s21_matrix.a $(O_FILES) s21_matrix.h
	ranlib s21_matrix.a
	gcc test.c $(GCCFLAGS) $(TESTFLAGS) -L. s21_matrix.a -o test $(TESTFLAGS)
	./test
	$(REPORT)

style:
	clang-format -i *.c
	clang-format -i *.h

linter:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h
	rm -rf .clang-format

all_functions:
	gcc -c $(CC_FLAGS) s21_*.c 

all_functions_gcov:
	gcc -c $(CC_FLAGS) $(TESTFLAGS) s21_*.c $(TESTFLAGS)

clean:
	rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov *.a
	rm -rf report/
	rm -rf temp/
	rm -rf atest.c
	rm -rf example
