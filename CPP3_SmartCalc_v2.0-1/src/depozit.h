#ifndef DEPOZIT_H
#define DEPOZIT_H

#include <math.h>

#include <QCloseEvent>
#include <QStandardItem>
#include <QString>
#include <QWidget>

namespace Ui {
class Depozit;
}

class Depozit : public QWidget {
  Q_OBJECT

 public:
  explicit Depozit(QWidget* parent = nullptr);
  ~Depozit();

  struct Transaction {
    int time;       //время транзакции
    double amount;  // сумма транзакции
  };
  void calculateDeposit(double depositAmount, int depositPeriod,
                        double interestRate, double taxRate,
                        int paymentFrequency, bool compoundInterest);

 private slots:
  void on_pushButton_3_clicked();

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::Depozit* ui;
  std::vector<Transaction> deposits;
  std::vector<Transaction> withdrawals;
  QStandardItemModel* model;

 protected:
  void closeEvent(QCloseEvent*) override {
    model->removeRows(0, model->rowCount());
    deposits.clear();
    withdrawals.clear();
  }
};

#endif  // DEPOZIT_H
