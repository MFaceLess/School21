CC=gcc -std=c11 -D_GNU_SOURCE
TEST_LIBS=-lcheck -lm -lpthread 
GCOV_LIBS=--coverage
BUILD_PATH=./
SOURCES=s21_*.c
HEAD=s21_SmartCalc.h
LIB_O=s21_SmartCalc.o
LIB_A=s21_SmartCalc.a
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

REPORT = gcov s21_*.gcno && gcovr --html > report.html


all: clean install

install: s21_3DViewer.a
	gcc main.c $(CC_FLAGS) -L. s21_3DViewer.a -o example $(TESTFLAGS) `pkg-config --cflags --libs gtk+-3.0` -lepoxy
	./example

uninstall:
	make clean

rebuild: clean all

test: s21_3DViewer.a
	gcc test.c $(GCCFLAGS) $(TESTFLAGS) -L. s21_3DViewer.a -o test $(TESTFLAGS)
	./test

#-lGL -lGLU -lglut

s21_3DViewer.a: all_functions
	ar rcs s21_3DViewer.a $(O_FILES) s21_3DViewer.h
	ranlib s21_3DViewer.a

gcov_report: all_functions_gcov
	ar -rv s21_3DViewer.a $(O_FILES) s21_3DViewer.h
	ranlib s21_3DViewer.a
	gcc test.c $(GCCFLAGS) $(TESTFLAGS) -L. s21_3DViewer.a -o test $(TESTFLAGS)
	./test
	$(REPORT)

style:
	clang-format -i --style=Google *.c
	clang-format -i --style=Google *.h

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
	rm -rf test

dist:
	tar -cf projects.tar ./*.c ./*.h ./Makefile

dvi:
	cd ./html/ && explorer.exe annotated.html
	