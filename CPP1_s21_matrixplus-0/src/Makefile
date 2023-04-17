CC_FLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
TESTFLAGS := -lrt -lm -lsubunit

CPP_FILES = s21_*.cpp
O_FILES = s21_*.o

all: clean example

rebuild: clean all

test: s21_matrix_oop.a
	g++ test.cpp $(GCCFLAGS) $(TESTFLAGS) -L. s21_matrix_oop.a -o test $(TESTFLAGS) -lgtest -lgmock -pthread
	./test

example: s21_matrix_oop.a
	gcc main.cpp $(CC_FLAGS) $(TESTFLAGS) -L. s21_matrix_oop.a -o example $(TESTFLAGS)
	./example

s21_matrix_oop.a: all_functions
	ar rcs s21_matrix_oop.a $(O_FILES) s21_matrix_oop.h
	ranlib s21_matrix_oop.a

style:
	clang-format -i --style=Google *.cpp
	clang-format -i --style=Google *.h

linter:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cpp *.h
	rm -rf .clang-format

all_functions:
	gcc -c $(CC_FLAGS) s21_*.cpp

clean:
	rm -rf *.o *.out *.a
	rm -rf example
	rm -rf test
