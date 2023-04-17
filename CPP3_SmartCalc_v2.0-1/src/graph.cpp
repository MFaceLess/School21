#include "graph.h"

#include "ui_graph.h"

Graph::Graph() : ui(new Ui::Graph) {
  ui->setupUi(this);
  chart = new QChart();
  chartView = new QChartView();
  ui->Chart->addWidget(chartView);
  chartView->setRenderHint(QPainter::Antialiasing);
}

Graph::~Graph() {
  delete ui;
  DeleteChart();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Graph::Create2DChart(QList<QPointF> series0) {
  if (series != nullptr) {
    DeleteChart();
  }
  series = new QLineSeries();
  axisX = new QValueAxis;
  axisY = new QValueAxis;
  series->append(series0);

  chart->addSeries(series);

  chart->addAxis(axisX, Qt::AlignBottom);
  chart->addAxis(axisY, Qt::AlignLeft);

  series->attachAxis(axisX);
  series->attachAxis(axisY);
  chartView->setChart(chart);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Graph::AddSeries2DChart(QList<QPointF> series0, QString nameSeries) {
  QLineSeries* seriesAdd = new QLineSeries();
  seriesAdd->append(series0);
  seriesAdd->setName(nameSeries);

  chart->addSeries(seriesAdd);
  seriesAdd->attachAxis(axisX);
  seriesAdd->attachAxis(axisY);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Graph::PropertiesAxis(QString nameAxis, double rangeLow, double rangeHigh,
                           double count, QString format) {
  if (nameAxis == "X") {
    axisX->setRange(rangeLow, rangeHigh);
    axisX->setTickCount(count);
    axisX->setLabelFormat(format);
  }
  if (nameAxis == "Y") {
    axisY->setRange(rangeLow, rangeHigh);
    axisY->setTickCount(count);
    axisY->setLabelFormat(format);
  }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Graph::SetNameAxis(QString nameAxisX, QString nameAxisY) {
  axisX->setTitleText(nameAxisX);
  axisY->setTitleText(nameAxisY);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Graph::DeleteChart() {
  if (axisX != nullptr) {
    axisX->deleteLater();
  }
  if (axisY != nullptr) {
    axisY->deleteLater();
  }
  chart->removeAllSeries();
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
