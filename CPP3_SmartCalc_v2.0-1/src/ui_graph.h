/********************************************************************************
** Form generated from reading UI file 'graph.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPH_H
#define UI_GRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Graph
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *Chart;

    void setupUi(QWidget *Graph)
    {
        if (Graph->objectName().isEmpty())
            Graph->setObjectName(QString::fromUtf8("Graph"));
        Graph->resize(800, 600);
        gridLayout = new QGridLayout(Graph);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Chart = new QVBoxLayout();
        Chart->setObjectName(QString::fromUtf8("Chart"));

        gridLayout->addLayout(Chart, 0, 0, 1, 1);


        retranslateUi(Graph);

        QMetaObject::connectSlotsByName(Graph);
    } // setupUi

    void retranslateUi(QWidget *Graph)
    {
        Graph->setWindowTitle(QCoreApplication::translate("Graph", "Graph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Graph: public Ui_Graph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPH_H
