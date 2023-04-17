#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QString>

#include "algorithm.h"
#include "credit.h"
#include "depozit.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_cos_clicked();

  void on_sin_clicked();

  void on_tan_clicked();

  void on_acos_clicked();

  void on_asin_clicked();

  void on_atan_clicked();

  void on_sqrt_clicked();

  void on_ln_clicked();

  void on_log_clicked();

  void on_plotGrapth_clicked();

  void on_credit_triggered();

  void on_depozit_triggered();

 private:
  Ui::MainWindow *ui;
  Algorithm alg;  // Связь меджу моделью и контроллером
  Credit crd;
  Depozit dpz;
};
#endif  // MAINWINDOW_H
