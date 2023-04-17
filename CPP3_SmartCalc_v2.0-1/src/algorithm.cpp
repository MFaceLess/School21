#include "algorithm.h"

QString Algorithm::Sort_Facility(const QString& in) {
  QString input = in;
  input.replace("acos", "o");
  input.replace("asin", "i");
  input.replace("atan", "a");
  input.replace("cos", "c");
  input.replace("sin", "s");
  input.replace("tan", "t");
  input.replace("sqrt", "q");
  input.replace("ln", "l");
  input.replace("log", "g");
  input.replace("mod", "%");
  input.replace(" ", "");

  QString result;

  QStack<QChar> temp;

  for (int i = 0; i < input.length();) {
    QChar ch = input.at(i);

    if (is_ident(ch) || ch == '.' || ch == 'e') {
      while (is_ident(ch) || ch == '.' || ch == 'e') {
        if (ch == 'e') {
          result.append(ch);
          ++i;
          if (i != input.length()) {
            ch = input.at(i);
          } else {
            break;
          }
        }
        result.append(ch);
        ++i;
        if (i != input.length()) {
          ch = input.at(i);
        } else {
          break;
        }
      }
      result.append('|');
      continue;
    } else if (is_function(ch)) {
      temp.push(ch);
    } else if (ch == ',') {
      int check = 0;
      while (!temp.isEmpty()) {
        const QChar top = temp.top();
        if (top == '(') {
          check = 1;
          break;
        } else {
          result.append(top);
          temp.pop();
        }
      }
      if (!check) {
        QString error = "Error in note!";
        throw error;
      }
    } else if (is_operator(ch)) {
      while (!temp.isEmpty()) {
        const QChar symbol = temp.top();
        if (is_operator(symbol) &&
            ((op_left_assoc(ch) && (op_preced(ch) <= op_preced(symbol))) ||
             (!op_left_assoc(ch) && (op_preced(ch) < op_preced(symbol))))) {
          result.append(symbol);
          temp.pop();
        } else {
          break;
        }
      }
      if (ch == '-' &&
          (i == 0 || (!is_ident(input.at(i - 1)) && input.at(i - 1) != ')'))) {
        temp.push('~');
      } else if (ch == '+' && (i == 0 || (!is_ident(input.at(i - 1)) &&
                                          input.at(i - 1) != ')'))) {
        temp.push(';');
      } else {
        temp.push(ch);
      }
    } else if (ch == '(') {
      temp.push(ch);
    } else if (ch == ')') {
      int check = 0;
      while (!temp.isEmpty()) {
        const QChar symbol = temp.top();
        if (symbol == '(') {
          check = 1;
          break;
        } else {
          result.append(symbol);
          temp.pop();
        }
      }
      if (!check) {
        QString error = "Error: parentheses mismatched";
        throw error;
      }
      temp.pop();
      if (!temp.isEmpty()) {
        const QChar symbol = temp.top();
        if (is_function(symbol)) {
          result.append(symbol);
          temp.pop();
        }
      }
    } else {
      QString error = "Unknown token ";
      error.append(ch);
      throw error;
    }
    ++i;
  }
  while (!temp.isEmpty()) {
    const QChar symbol = temp.top();
    if (symbol == '(' || symbol == ')') {
      QString error = "Error: parentheses mismatched";
      throw error;
    }
    result.append(symbol);
    temp.pop();
  }

  return result;
}

double Algorithm::Calculation(const QString afterFacility) {
  QStack<double> calculation;
  QString::const_iterator it = afterFacility.constBegin();

  while (it != afterFacility.constEnd()) {
    if (it->isDigit() || *it == '.' || *it == 'e') {
      QString temp;
      while (*it != '|') {
        temp.append(*it);
        ++it;
      }
      double num = temp.toDouble();
      calculation.push(num);
    } else if (*it == '|') {
      ++it;
    } else if (is_operator(*it)) {
      if (calculation.size() < 2 &&
          ((*it).unicode() != '~' && (*it).unicode() != ';')) {
        QString error = "too low arguments in Stack";
        throw error;
      }
      if ((*it).unicode() == '~' || (*it).unicode() == ';') {
        double number = calculation.pop();
        switch ((*it).unicode()) {
          case '~':
            calculation.push(-number);
            break;
          case ';':
            calculation.push(number);
            break;
        }
      } else {
        double number2 = calculation.pop();
        double number1 = calculation.pop();
        switch ((*it).unicode()) {
          case '+':
            calculation.push(number1 + number2);
            break;
          case '-':
            calculation.push(number1 - number2);
            break;
          case '*':
            calculation.push(number1 * number2);
            break;
          case '/':
            calculation.push(number1 / number2);
            break;
          case '^':
            calculation.push(pow(number1, number2));
            break;
          case '%':
            calculation.push(fmod(number1, number2));
            break;
          case '~':
            calculation.push(-number1);
            break;
          case ';':
            calculation.push(number1);
            break;
        }
      }
      ++it;
    } else if (is_function(*it)) {
      if (calculation.size() < 1) {
        QString error = "too low arguments in Stack";
        throw error;
      }
      double number1 = calculation.pop();
      switch ((*it).unicode()) {
        case 'c':
          calculation.push(cos(number1));
          break;
        case 's':
          calculation.push(sin(number1));
          break;
        case 't':
          calculation.push(tan(number1));
          break;
        case 'o':
          calculation.push(acos(number1));
          break;
        case 'i':
          calculation.push(asin(number1));
          break;
        case 'a':
          calculation.push(atan(number1));
          break;
        case 'q':
          calculation.push(sqrt(number1));
          break;
        case 'l':
          calculation.push(log(number1));
          break;
        case 'g':
          calculation.push(log10(number1));
          break;
      }
      ++it;
    } else {
      ++it;
    }
  }
  double result = calculation.pop();
  if (calculation.size() != 0) {
    QString error = "too many arguments in Stack";
    throw error;
  }
  return result;
}

void Algorithm::plot(const QString afterFacility, double x_left, double x_right,
                     double y_down, double y_up) {
  QLineSeries series;

  for (double i = x_left; i < x_right; i += 0.01) {
    QString temp = afterFacility;
    if (i < 0) {
      QString with_minus = QString::number(fabs(i)) + "|" + "~";
      temp.replace("x|", with_minus);
    } else {
      temp.replace("x", QString::number(i));
    }
    qDebug() << (Calculation(temp));
    series.append(i, Calculation(temp));
  }

  chrt.Create2DChart(series.points());
  chrt.series->setName("График по точкам");
  chrt.PropertiesAxis("X", x_left, x_right, 11, "%.2lf");
  chrt.PropertiesAxis("Y", y_down, y_up, 11, "%.2lf");
  chrt.SetNameAxis("Ось X", "Ось Y");

  chrt.show();
}

int Algorithm::op_preced(const QChar c) {
  switch (c.unicode()) {
    case ';':
    case '~':
      return 5;

    case '^':
      return 4;

    case '*':
    case '/':
    case '%':
      return 3;

    case '+':
    case '-':
      return 2;

    case '=':
      return 1;
  }
  return 0;
}

int Algorithm::op_left_assoc(const QChar c) {
  switch (c.unicode()) {
    // лево-ассоциативные операторы
    case '*':
    case '/':
    case '%':
    case '+':
    case '-':
    case '=':
      return 1;
    // право-ассоциативные операторы
    case ';':  // унарный плюс
    case '~':  // унарный минус
    case '^':
      return 0;
  }
  return 0;
}
