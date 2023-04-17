#include "credit.h"

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_clicked() {
  double x1 = ui->totalSum->value();
  double x2 = ui->timeMonth->value();
  double x3 = ui->stavka->value();

  double result;
  if (ui->comboBox->currentIndex() == 0) {
    double stavka = x3 / 12.0 / 100.0;
    double koeff =
        (stavka * pow((1 + stavka), x2)) / (pow((1 + stavka), x2) - 1);
    result = x1 * koeff;
  } else {
    double Cd = x1 / x2;
    double sum = 0;
    for (int i = 0; i < x2; i++) {
      double temp = (x1 - Cd * i) * x3 / 100 * 31 / 365;
      sum += temp;
    }
    result = Cd * x2 + sum;
  }
  ui->monthPay->setValue(result);
  ui->Pereplata->setValue((result * x2) - x1);
  ui->totalPay->setValue((result * x2) - x1 + x1);
}
