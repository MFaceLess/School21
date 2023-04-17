#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui {
class Graph;
}
QT_END_NAMESPACE

class Graph : public QWidget {
  Q_OBJECT

 public:
  Graph();
  ~Graph();

  QLineSeries* series = nullptr;
  QValueAxis* axisX = nullptr;
  QValueAxis* axisY = nullptr;

  void Create2DChart(QList<QPointF>);  // создание графика 2D
  void AddSeries2DChart(QList<QPointF> series0,
                        QString nameSeries);  // добавление серии к графику
  void PropertiesAxis(QString nameAxis, double rangeLow, double rangeHigh,
                      double count, QString format);  // свойства осей
  void SetNameAxis(QString nameAxisX, QString nameAxisY);  // имена осей
  void DeleteChart();

 private:
  Ui::Graph* ui;
  QChartView* chartView = nullptr;
  QChart* chart = nullptr;
};

#endif  // GRAPH_H
