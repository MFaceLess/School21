CC_FLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
TESTFLAGS := -lrt -lm -lsubunit -lgtest -lgtest_main -pthread

CPP_FILES = s21_*.cc
O_FILES = s21_*.o

all: clean seq_test

rebuild: clean all

test: seq_test

seq_test:
	g++ seq_test.cc $(CC_FLAGS) $(TESTFLAGS) && ./a.out

s21_containersplus:
	ar rcs s21_containersplus.a s21_containers.h s21_containersplus.h
	ranlib s21_containersplus.a

style:
	clang-format -i --style=Google *.cc
	clang-format -i --style=Google *.h

linter:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cc *.h
	rm -rf .clang-format

all_functions:
	gcc -c $(CC_FLAGS) $(CPP_FILES)

clean:
	rm -rf *.o *.out *.a
