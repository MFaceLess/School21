#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <math.h>

#include <QDebug>
#include <QStack>
#include <QString>

#include "graph.h"

#define is_function(c)                                                     \
  (c == 'c' || c == 's' || c == 't' || c == 'o' || c == 'i' || c == 'a' || \
   c == 'q' || c == 'l' || c == 'g')
#define is_ident(c) ((c >= '0' && c <= '9') || c == 'x')
#define is_operator(c)                                                     \
  (c == '+' || c == '-' || c == '/' || c == '*' || c == '^' || c == '%' || \
   c == '=' || c == '~' || c == ';')

namespace s21 {
class Algorithm;
}

class Algorithm {
 public:
  Algorithm() = default;
  ~Algorithm() = default;
  QString Sort_Facility(const QString& input);
  double Calculation(const QString afterFacility);
  int op_preced(const QChar c);
  int op_left_assoc(const QChar c);
  void plot(const QString afterFacility, double x_left, double x_right,
            double y_down, double y_up);

 private:
  QStack<char> symbols;
  Graph chrt;
};

#endif  // ALGORITHM_H
