/********************************************************************************
** Form generated from reading UI file 'credit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDIT_H
#define UI_CREDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Credit
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QDoubleSpinBox *totalSum;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QDoubleSpinBox *timeMonth;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QDoubleSpinBox *stavka;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *monthPay;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_6;
    QDoubleSpinBox *Pereplata;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QDoubleSpinBox *totalPay;
    QPushButton *pushButton;

    void setupUi(QWidget *Credit)
    {
        if (Credit->objectName().isEmpty())
            Credit->setObjectName(QString::fromUtf8("Credit"));
        Credit->resize(544, 307);
        gridLayout = new QGridLayout(Credit);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(Credit);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_4->addWidget(label);

        totalSum = new QDoubleSpinBox(Credit);
        totalSum->setObjectName(QString::fromUtf8("totalSum"));
        totalSum->setMaximum(1000000000.000000000000000);

        verticalLayout_4->addWidget(totalSum);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_2 = new QLabel(Credit);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        timeMonth = new QDoubleSpinBox(Credit);
        timeMonth->setObjectName(QString::fromUtf8("timeMonth"));
        timeMonth->setMaximum(1000000.000000000000000);

        verticalLayout_3->addWidget(timeMonth);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_3 = new QLabel(Credit);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        stavka = new QDoubleSpinBox(Credit);
        stavka->setObjectName(QString::fromUtf8("stavka"));
        stavka->setMaximum(10000000.000000000000000);

        verticalLayout_2->addWidget(stavka);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(Credit);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFrameShadow(QFrame::Plain);

        verticalLayout->addWidget(label_4);

        comboBox = new QComboBox(Credit);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_8->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_5 = new QLabel(Credit);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_5->addWidget(label_5);

        monthPay = new QDoubleSpinBox(Credit);
        monthPay->setObjectName(QString::fromUtf8("monthPay"));
        monthPay->setMaximum(10000000000000.000000000000000);

        verticalLayout_5->addWidget(monthPay);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_6 = new QLabel(Credit);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_6->addWidget(label_6);

        Pereplata = new QDoubleSpinBox(Credit);
        Pereplata->setObjectName(QString::fromUtf8("Pereplata"));
        Pereplata->setMaximum(100000000000000.000000000000000);

        verticalLayout_6->addWidget(Pereplata);


        horizontalLayout_2->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_7 = new QLabel(Credit);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_7->addWidget(label_7);

        totalPay = new QDoubleSpinBox(Credit);
        totalPay->setObjectName(QString::fromUtf8("totalPay"));
        totalPay->setMaximum(10000000000000.000000000000000);

        verticalLayout_7->addWidget(totalPay);


        horizontalLayout_2->addLayout(verticalLayout_7);


        verticalLayout_8->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(Credit);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_8->addWidget(pushButton);


        gridLayout->addLayout(verticalLayout_8, 0, 0, 1, 1);


        retranslateUi(Credit);

        QMetaObject::connectSlotsByName(Credit);
    } // setupUi

    void retranslateUi(QWidget *Credit)
    {
        Credit->setWindowTitle(QCoreApplication::translate("Credit", "Credit", nullptr));
        label->setText(QCoreApplication::translate("Credit", "\320\236\320\261\321\211\320\260\321\217 \321\201\321\203\320\274\320\274\320\260 \320\272\321\200\320\265\320\264\320\270\321\202\320\260(\321\200\321\203\320\261)", nullptr));
        label_2->setText(QCoreApplication::translate("Credit", "\320\241\321\200\320\276\320\272 \320\262 \320\274\320\265\321\201\321\217\321\206\320\260\321\205", nullptr));
        label_3->setText(QCoreApplication::translate("Credit", "\320\237\321\200\320\276\321\206\320\265\320\275\321\202\320\275\320\260\321\217 \321\201\321\202\320\260\320\262\320\272\320\260 (%)", nullptr));
        label_4->setText(QCoreApplication::translate("Credit", "\320\242\320\270\320\277", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Credit", "\320\220\320\275\320\275\321\203\320\270\321\202\320\265\321\202\320\275\321\213\320\271", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Credit", "\320\224\320\270\321\204\321\204\320\265\321\200\320\265\320\275\321\206\320\270\321\200\320\276\320\262\320\260\320\275\320\275\321\213\320\271", nullptr));

        label_5->setText(QCoreApplication::translate("Credit", "\320\225\320\266\320\265\320\274\320\265\321\201\321\217\321\207\320\275\321\213\320\271 \320\277\320\273\320\260\321\202\320\265\320\266", nullptr));
        label_6->setText(QCoreApplication::translate("Credit", "\320\237\320\265\321\200\320\265\320\277\320\273\320\260\321\202\320\260 \320\277\320\276 \320\272\321\200\320\265\320\264\320\270\321\202\321\203", nullptr));
        label_7->setText(QCoreApplication::translate("Credit", "\320\236\320\261\321\211\320\260\321\217 \320\262\321\213\320\277\320\273\320\260\321\202\320\260", nullptr));
        pushButton->setText(QCoreApplication::translate("Credit", "\320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Credit: public Ui_Credit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDIT_H
