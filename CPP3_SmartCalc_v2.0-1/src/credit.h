#ifndef CREDIT_H
#define CREDIT_H

#include <math.h>

#include <QWidget>

namespace Ui {
class Credit;
}

class Credit : public QWidget {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // CREDIT_H
