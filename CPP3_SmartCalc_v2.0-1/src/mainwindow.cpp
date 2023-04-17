#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->LCD, &QLineEdit::returnPressed, this,
          &MainWindow::on_plotGrapth_clicked);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_cos_clicked() {
  QString temp = ui->LCD->text();
  temp += "cos(";
  ui->LCD->setText(temp);
}

void MainWindow::on_sin_clicked() {
  QString temp = ui->LCD->text();
  temp += "sin(";
  ui->LCD->setText(temp);
}

void MainWindow::on_tan_clicked() {
  QString temp = ui->LCD->text();
  temp += "tan(";
  ui->LCD->setText(temp);
}

void MainWindow::on_acos_clicked() {
  QString temp = ui->LCD->text();
  temp += "acos(";
  ui->LCD->setText(temp);
}

void MainWindow::on_asin_clicked() {
  QString temp = ui->LCD->text();
  temp += "asin(";
  ui->LCD->setText(temp);
}

void MainWindow::on_atan_clicked() {
  QString temp = ui->LCD->text();
  temp += "atan(";
  ui->LCD->setText(temp);
}

void MainWindow::on_sqrt_clicked() {
  QString temp = ui->LCD->text();
  temp += "sqrt(";
  ui->LCD->setText(temp);
}

void MainWindow::on_ln_clicked() {
  QString temp = ui->LCD->text();
  temp += "ln(";
  ui->LCD->setText(temp);
}

void MainWindow::on_log_clicked() {
  QString temp = ui->LCD->text();
  temp += "log(";
  ui->LCD->setText(temp);
}

void MainWindow::on_plotGrapth_clicked() {
  QString temp = ui->LCD->text();
  if (temp != "") {
    try {
      QString mid = alg.Sort_Facility(temp);
      if (mid.contains("x")) {
        qDebug() << "Wee-Wee";
        alg.plot(mid, ui->X_Left->value(), ui->X_Right->value(),
                 ui->Y_Down->value(), ui->Y_Hight->value());
      } else {
        QString res = QString::number(alg.Calculation(mid));
        ui->LCD->setText(res);
      }
    } catch (const QString err) {
      ui->LCD->setText(err);
      qDebug() << err;
    }
  }
}

void MainWindow::on_credit_triggered() { crd.show(); }

void MainWindow::on_depozit_triggered() { dpz.show(); }
