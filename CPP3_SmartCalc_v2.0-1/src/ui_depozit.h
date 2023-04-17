/********************************************************************************
** Form generated from reading UI file 'depozit.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPOZIT_H
#define UI_DEPOZIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Depozit
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QDoubleSpinBox *depositAmount;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QSpinBox *depositPeriod;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QDoubleSpinBox *interestRate;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QDoubleSpinBox *taxRate;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_2;
    QSpinBox *paymentFrequency;
    QCheckBox *compoundInterest;
    QHBoxLayout *horizontalLayout_4;
    QTableView *tableView;
    QVBoxLayout *verticalLayout_12;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_13;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_9;
    QSpinBox *spinBox;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBox;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_14;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_11;
    QSpinBox *spinBox_2;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_12;
    QDoubleSpinBox *doubleSpinBox_2;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_6;
    QDoubleSpinBox *interestAccrued;
    QVBoxLayout *verticalLayout_14;
    QLabel *label_7;
    QDoubleSpinBox *totalTax;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_8;
    QDoubleSpinBox *finalDepositAmount;
    QPushButton *pushButton_3;

    void setupUi(QWidget *Depozit)
    {
        if (Depozit->objectName().isEmpty())
            Depozit->setObjectName(QString::fromUtf8("Depozit"));
        Depozit->resize(1200, 550);
        gridLayout = new QGridLayout(Depozit);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(Depozit);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        depositAmount = new QDoubleSpinBox(Depozit);
        depositAmount->setObjectName(QString::fromUtf8("depositAmount"));
        depositAmount->setMaximum(10000000000.000000000000000);

        verticalLayout->addWidget(depositAmount);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(Depozit);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        depositPeriod = new QSpinBox(Depozit);
        depositPeriod->setObjectName(QString::fromUtf8("depositPeriod"));
        depositPeriod->setMaximum(1000000000);

        verticalLayout_2->addWidget(depositPeriod);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(Depozit);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        interestRate = new QDoubleSpinBox(Depozit);
        interestRate->setObjectName(QString::fromUtf8("interestRate"));
        interestRate->setMaximum(10000000000.000000000000000);

        verticalLayout_3->addWidget(interestRate);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(Depozit);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_4->addWidget(label);

        taxRate = new QDoubleSpinBox(Depozit);
        taxRate->setObjectName(QString::fromUtf8("taxRate"));
        taxRate->setMaximum(10000000000.000000000000000);

        verticalLayout_4->addWidget(taxRate);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_2 = new QLabel(Depozit);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_5->addWidget(label_2);

        paymentFrequency = new QSpinBox(Depozit);
        paymentFrequency->setObjectName(QString::fromUtf8("paymentFrequency"));
        paymentFrequency->setMaximum(100000000);

        verticalLayout_5->addWidget(paymentFrequency);


        horizontalLayout->addLayout(verticalLayout_5);

        compoundInterest = new QCheckBox(Depozit);
        compoundInterest->setObjectName(QString::fromUtf8("compoundInterest"));

        horizontalLayout->addWidget(compoundInterest);


        verticalLayout_16->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        tableView = new QTableView(Depozit);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        horizontalLayout_4->addWidget(tableView);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_13 = new QLabel(Depozit);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_2->addWidget(label_13);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_9 = new QLabel(Depozit);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_6->addWidget(label_9);

        spinBox = new QSpinBox(Depozit);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(100);

        verticalLayout_6->addWidget(spinBox);


        horizontalLayout_2->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_10 = new QLabel(Depozit);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_7->addWidget(label_10);

        doubleSpinBox = new QDoubleSpinBox(Depozit);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setMaximum(10000000000.000000000000000);

        verticalLayout_7->addWidget(doubleSpinBox);


        horizontalLayout_2->addLayout(verticalLayout_7);


        verticalLayout_8->addLayout(horizontalLayout_2);

        pushButton = new QPushButton(Depozit);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_8->addWidget(pushButton);


        verticalLayout_12->addLayout(verticalLayout_8);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_14 = new QLabel(Depozit);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_3->addWidget(label_14);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        label_11 = new QLabel(Depozit);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_9->addWidget(label_11);

        spinBox_2 = new QSpinBox(Depozit);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setMaximum(100);

        verticalLayout_9->addWidget(spinBox_2);


        horizontalLayout_3->addLayout(verticalLayout_9);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_12 = new QLabel(Depozit);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_10->addWidget(label_12);

        doubleSpinBox_2 = new QDoubleSpinBox(Depozit);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setMaximum(10000000000.000000000000000);

        verticalLayout_10->addWidget(doubleSpinBox_2);


        horizontalLayout_3->addLayout(verticalLayout_10);


        verticalLayout_11->addLayout(horizontalLayout_3);

        pushButton_2 = new QPushButton(Depozit);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_11->addWidget(pushButton_2);


        verticalLayout_12->addLayout(verticalLayout_11);


        horizontalLayout_4->addLayout(verticalLayout_12);


        verticalLayout_16->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        label_6 = new QLabel(Depozit);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_13->addWidget(label_6);

        interestAccrued = new QDoubleSpinBox(Depozit);
        interestAccrued->setObjectName(QString::fromUtf8("interestAccrued"));
        interestAccrued->setMaximum(10000000000.000000000000000);

        verticalLayout_13->addWidget(interestAccrued);


        horizontalLayout_5->addLayout(verticalLayout_13);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        label_7 = new QLabel(Depozit);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_14->addWidget(label_7);

        totalTax = new QDoubleSpinBox(Depozit);
        totalTax->setObjectName(QString::fromUtf8("totalTax"));
        totalTax->setMaximum(10000000000.000000000000000);

        verticalLayout_14->addWidget(totalTax);


        horizontalLayout_5->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        label_8 = new QLabel(Depozit);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_15->addWidget(label_8);

        finalDepositAmount = new QDoubleSpinBox(Depozit);
        finalDepositAmount->setObjectName(QString::fromUtf8("finalDepositAmount"));
        finalDepositAmount->setMaximum(10000000000.000000000000000);

        verticalLayout_15->addWidget(finalDepositAmount);


        horizontalLayout_5->addLayout(verticalLayout_15);


        verticalLayout_16->addLayout(horizontalLayout_5);

        pushButton_3 = new QPushButton(Depozit);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout_16->addWidget(pushButton_3);


        gridLayout->addLayout(verticalLayout_16, 0, 0, 1, 1);


        retranslateUi(Depozit);

        QMetaObject::connectSlotsByName(Depozit);
    } // setupUi

    void retranslateUi(QWidget *Depozit)
    {
        Depozit->setWindowTitle(QCoreApplication::translate("Depozit", "Depozit", nullptr));
        label_5->setText(QCoreApplication::translate("Depozit", "\320\241\321\203\320\274\320\274\320\260 \320\262\320\272\320\273\320\260\320\264\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("Depozit", "\320\241\321\200\320\276\320\272 \321\200\320\260\320\267\320\274\320\265\321\211\320\265\320\275\320\270\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("Depozit", "\320\237\321\200\320\276\321\206\320\265\320\275\321\202\320\275\320\260\321\217 \321\201\321\202\320\260\320\262\320\272\320\260", nullptr));
        label->setText(QCoreApplication::translate("Depozit", "\320\235\320\260\320\273\320\276\320\263\320\276\320\262\320\260\321\217 \321\201\321\202\320\260\320\262\320\272\320\260", nullptr));
        label_2->setText(QCoreApplication::translate("Depozit", "\320\237\320\265\321\200\320\270\320\276\320\264\320\270\321\207\320\275\320\276\321\201\321\202\321\214 \320\262\321\213\320\277\320\273\320\260\321\202", nullptr));
        compoundInterest->setText(QCoreApplication::translate("Depozit", "\320\232\320\260\320\277\320\270\321\202\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        label_13->setText(QCoreApplication::translate("Depozit", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\277\320\276\320\277\320\276\320\273\320\275\320\265\320\275\320\270\320\271", nullptr));
        label_9->setText(QCoreApplication::translate("Depozit", "\320\222\321\200\320\265\320\274\321\217 \321\202\321\200\320\260\320\275\320\267.", nullptr));
        label_10->setText(QCoreApplication::translate("Depozit", "\320\241\321\203\320\274\320\274\320\260 \321\202\321\200\320\260\320\275\320\267.", nullptr));
        pushButton->setText(QCoreApplication::translate("Depozit", "\320\222\320\275\320\265\321\201\321\202\320\270 \320\262 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        label_14->setText(QCoreApplication::translate("Depozit", "\320\241\320\277\320\270\321\201\320\276\320\272 \321\201\320\275\321\217\321\202\320\270\320\271", nullptr));
        label_11->setText(QCoreApplication::translate("Depozit", "\320\222\321\200\320\265\320\274\321\217 \321\202\321\200\320\260\320\275\320\267.", nullptr));
        label_12->setText(QCoreApplication::translate("Depozit", "\320\241\321\203\320\274\320\274\320\260 \321\202\321\200\320\260\320\275\320\267.", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Depozit", "\320\222\320\275\320\265\321\201\321\202\320\270 \320\262 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        label_6->setText(QCoreApplication::translate("Depozit", "\320\235\320\260\321\207\320\270\321\201\320\273\320\265\320\275\320\275\321\213\320\265 \320\277\321\200\320\276\321\206\320\265\320\275\321\202\321\213", nullptr));
        label_7->setText(QCoreApplication::translate("Depozit", "\320\241\321\203\320\274\320\274\320\260 \320\275\320\260\320\273\320\276\320\263\320\260", nullptr));
        label_8->setText(QCoreApplication::translate("Depozit", "\320\241\321\203\320\274\320\274\320\260 \320\262\320\272\320\273\320\260\320\264\320\260 \320\272 \320\272\320\276\320\275\321\206\321\203 \321\201\321\200\320\276\320\272\320\260", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Depozit", "\320\240\320\260\321\201\321\201\321\207\320\270\321\202\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Depozit: public Ui_Depozit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPOZIT_H
