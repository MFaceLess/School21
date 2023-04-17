#include "s21_matrix_oop.h"

int main() {
  S21Matrix m1;

  try {
    std::cout << m1(-1,1);
  } catch (const char* err) {
    std::cout << "Обошли\n";
  }


  return 0;
}
