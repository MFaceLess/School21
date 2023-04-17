CC=gcc -std=c11 -D_GNU_SOURCE
TEST_LIBS=-lcheck -lm -lpthread 
GCOV_LIBS=--coverage
BUILD_PATH=./
SOURCES=s21_*.c
HEAD=s21_math.h
LIB_O=s21_math.o
LIB_A=s21_math.a
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

all: clean s21_math.a

rebuild: clean all

test: s21_math.a
	gcc tests.c $(GCCFLAGS) $(TESTFLAGS) -L. s21_math.a -o test
	./test

s21_math.a: all_functions
	ar rcs s21_math.a $(O_FILES)
	ranlib s21_math.a

style: clean

	clang-format -n *.c
	clang-format -n *.h

all_functions: $(C_FILES)
	gcc -c $(CC_FLAGS) $(C_FILES)

clean:
	rm -rf *.o *.gch *.out *.gcno *.gcda *.info *.gcov
	rm -rf report/
	rm -rf temp/
	rm -rf atest.c

gcov_report: s21_math.a
	$(CC) $(GCOV_LIBS) tests.c $(SOURCES) $(LIB_A) -L. $(LIB_A) $(TEST_LIBS) -o $(BUILD_PATH)$(TEST)
	$(BUILD_PATH)$(TEST)
	gcov s21_*.gcno > report.html
	make clean


