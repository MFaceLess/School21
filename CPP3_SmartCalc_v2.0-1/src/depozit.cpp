#include "depozit.h"

#include "ui_depozit.h"

Depozit::Depozit(QWidget *parent) : QWidget(parent), ui(new Ui::Depozit) {
  ui->setupUi(this);
  model = new QStandardItemModel();
  ui->tableView->setModel(model);
}

Depozit::~Depozit() {
  model->removeRows(0, model->rowCount());
  delete model;
  delete ui;
}

void Depozit::calculateDeposit(double depositAmount, int depositPeriod,
                               double interestRate, double taxRate,
                               int paymentFrequency, bool compoundInterest) {
  double interestAccrued = 0;
  double totalTax = 0;
  double totalDeposit = depositAmount;
  int n = paymentFrequency;  // количество выплат в год
  double r = interestRate / n;  // процентная ставка на период
  double t = depositPeriod;  // срок размещения в годах

  // Расчет процентов
  if (compoundInterest) {
    interestAccrued = depositAmount * pow(1 + (r / 100), n * t) - depositAmount;
  } else {
    interestAccrued = depositAmount * (r / 100) * t;
  }

  // Расчет налога на проценты
  double taxableInterest = interestAccrued;
  for (size_t i = 0; i < deposits.size(); i++) {
    if (deposits[i].time <= depositPeriod) {
      totalDeposit += deposits[i].amount;
    }
  }
  for (size_t i = 0; i < withdrawals.size(); i++) {
    if (withdrawals[i].time <= depositPeriod) {
      totalDeposit -= withdrawals[i].amount;
    }
  }
  double nonTaxableAmount = totalDeposit + taxableInterest;
  if (nonTaxableAmount > 0) {
    taxableInterest =
        std::max(taxableInterest - nonTaxableAmount * taxRate / 100, 0.0);
  }
  totalTax = taxableInterest * taxRate / 100;

  // Расчет суммы вклада к концу срока
  double finalDepositAmount = depositAmount + interestAccrued - totalTax;
  for (size_t i = 0; i < deposits.size(); i++) {
    if (deposits[i].time <= depositPeriod) {
      finalDepositAmount += deposits[i].amount;
    }
  }
  for (size_t i = 0; i < withdrawals.size(); i++) {
    if (withdrawals[i].time <= depositPeriod) {
      finalDepositAmount -= withdrawals[i].amount;
    }
  }

  // Вывод результатов
  ui->interestAccrued->setValue(interestAccrued);
  ui->totalTax->setValue(totalTax);
  ui->finalDepositAmount->setValue(finalDepositAmount);
}

void Depozit::on_pushButton_3_clicked() {
  double depositAmount = ui->depositAmount->value();
  int depositPeriod = ui->depositPeriod->value();
  double interestRate = ui->interestRate->value();
  double taxRate = ui->taxRate->value();
  int paymentFrequency = ui->paymentFrequency->value();
  bool compoundInterest = ui->compoundInterest->isChecked();

  calculateDeposit(depositAmount, depositPeriod, interestRate, taxRate,
                   paymentFrequency, compoundInterest);
}

void Depozit::on_pushButton_clicked() {
  int time = ui->spinBox->value();
  double Sum = ui->doubleSpinBox->value();

  Transaction t = {time, Sum};
  deposits.push_back(t);

  // добавляем новую строку в конец таблицы
  model->insertRow(model->rowCount());

  QStandardItem *item1 = new QStandardItem("Пополнение:");
  model->setItem(model->rowCount() - 1, 0, item1);

  QStandardItem *item2 =
      new QStandardItem(QString("Время: ") + QString::number(time));
  model->setItem(model->rowCount() - 1, 1, item2);

  QStandardItem *item3 =
      new QStandardItem(QString("Cумма транзакции: ") + QString::number(Sum));
  item3->setSizeHint(QSize(10000, item3->sizeHint().height()));
  model->setItem(model->rowCount() - 1, 2, item3);
}

void Depozit::on_pushButton_2_clicked() {
  int time = ui->spinBox_2->value();
  double Sum = ui->doubleSpinBox_2->value();

  Transaction t = {time, Sum};
  withdrawals.push_back(t);

  // добавляем новую строку в конец таблицы
  model->insertRow(model->rowCount());

  QStandardItem *item1 = new QStandardItem("Снятие:");
  model->setItem(model->rowCount() - 1, 0, item1);

  QStandardItem *item2 =
      new QStandardItem(QString("Время: ") + QString::number(time));
  model->setItem(model->rowCount() - 1, 1, item2);

  QStandardItem *item3 =
      new QStandardItem(QString("Cумма транзакции: ") + QString::number(Sum));
  item3->setSizeHint(QSize(10000, item3->sizeHint().height()));
  model->setItem(model->rowCount() - 1, 2, item3);
}
