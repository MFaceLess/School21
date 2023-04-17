/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *credit;
    QAction *depozit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *LCD;
    QHBoxLayout *horizontalLayout;
    QPushButton *cos;
    QPushButton *sin;
    QPushButton *tan;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *acos;
    QPushButton *asin;
    QPushButton *atan;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *sqrt;
    QPushButton *ln;
    QPushButton *log;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *X_Left;
    QDoubleSpinBox *X_Right;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *Y_Down;
    QDoubleSpinBox *Y_Hight;
    QPushButton *plotGrapth;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(950, 278);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        credit = new QAction(MainWindow);
        credit->setObjectName(QString::fromUtf8("credit"));
        depozit = new QAction(MainWindow);
        depozit->setObjectName(QString::fromUtf8("depozit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        LCD = new QLineEdit(centralwidget);
        LCD->setObjectName(QString::fromUtf8("LCD"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(LCD->sizePolicy().hasHeightForWidth());
        LCD->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(22);
        LCD->setFont(font);
        LCD->setCursor(QCursor(Qt::IBeamCursor));

        verticalLayout_3->addWidget(LCD);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        cos = new QPushButton(centralwidget);
        cos->setObjectName(QString::fromUtf8("cos"));
        sizePolicy1.setHeightForWidth(cos->sizePolicy().hasHeightForWidth());
        cos->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(cos);

        sin = new QPushButton(centralwidget);
        sin->setObjectName(QString::fromUtf8("sin"));
        sizePolicy1.setHeightForWidth(sin->sizePolicy().hasHeightForWidth());
        sin->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(sin);

        tan = new QPushButton(centralwidget);
        tan->setObjectName(QString::fromUtf8("tan"));
        sizePolicy1.setHeightForWidth(tan->sizePolicy().hasHeightForWidth());
        tan->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(tan);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        acos = new QPushButton(centralwidget);
        acos->setObjectName(QString::fromUtf8("acos"));
        sizePolicy1.setHeightForWidth(acos->sizePolicy().hasHeightForWidth());
        acos->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(acos);

        asin = new QPushButton(centralwidget);
        asin->setObjectName(QString::fromUtf8("asin"));
        sizePolicy1.setHeightForWidth(asin->sizePolicy().hasHeightForWidth());
        asin->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(asin);

        atan = new QPushButton(centralwidget);
        atan->setObjectName(QString::fromUtf8("atan"));
        sizePolicy1.setHeightForWidth(atan->sizePolicy().hasHeightForWidth());
        atan->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(atan);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sqrt = new QPushButton(centralwidget);
        sqrt->setObjectName(QString::fromUtf8("sqrt"));
        sizePolicy1.setHeightForWidth(sqrt->sizePolicy().hasHeightForWidth());
        sqrt->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(sqrt);

        ln = new QPushButton(centralwidget);
        ln->setObjectName(QString::fromUtf8("ln"));
        sizePolicy1.setHeightForWidth(ln->sizePolicy().hasHeightForWidth());
        ln->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(ln);

        log = new QPushButton(centralwidget);
        log->setObjectName(QString::fromUtf8("log"));
        sizePolicy1.setHeightForWidth(log->sizePolicy().hasHeightForWidth());
        log->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(log);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFocusPolicy(Qt::NoFocus);
        label->setTextFormat(Qt::MarkdownText);
        label->setScaledContents(false);

        verticalLayout_2->addWidget(label);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        X_Left = new QDoubleSpinBox(centralwidget);
        X_Left->setObjectName(QString::fromUtf8("X_Left"));
        X_Left->setMinimum(-1000000.000000000000000);
        X_Left->setMaximum(1000000.000000000000000);
        X_Left->setValue(-10.000000000000000);

        horizontalLayout_5->addWidget(X_Left);

        X_Right = new QDoubleSpinBox(centralwidget);
        X_Right->setObjectName(QString::fromUtf8("X_Right"));
        X_Right->setMinimum(-1000000.000000000000000);
        X_Right->setMaximum(1000000.000000000000000);
        X_Right->setValue(10.000000000000000);

        horizontalLayout_5->addWidget(X_Right);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        Y_Down = new QDoubleSpinBox(centralwidget);
        Y_Down->setObjectName(QString::fromUtf8("Y_Down"));
        Y_Down->setMinimum(-1000000.000000000000000);
        Y_Down->setMaximum(1000000.000000000000000);
        Y_Down->setValue(-10.000000000000000);

        horizontalLayout_4->addWidget(Y_Down);

        Y_Hight = new QDoubleSpinBox(centralwidget);
        Y_Hight->setObjectName(QString::fromUtf8("Y_Hight"));
        Y_Hight->setValue(10.000000000000000);

        horizontalLayout_4->addWidget(Y_Hight);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_6->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_6);

        plotGrapth = new QPushButton(centralwidget);
        plotGrapth->setObjectName(QString::fromUtf8("plotGrapth"));
        sizePolicy1.setHeightForWidth(plotGrapth->sizePolicy().hasHeightForWidth());
        plotGrapth->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(plotGrapth);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 950, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menu->addAction(credit);
        menu->addSeparator();
        menu->addAction(depozit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "s21_SmartCalc", nullptr));
        credit->setText(QCoreApplication::translate("MainWindow", "\320\232\321\200\320\265\320\264\320\270\321\202\320\275\321\213\320\271 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200", nullptr));
        depozit->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\277\320\276\320\267\320\270\321\202\320\275\321\213\320\271 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200", nullptr));
        LCD->setText(QString());
        cos->setText(QCoreApplication::translate("MainWindow", "cos(x)", nullptr));
        sin->setText(QCoreApplication::translate("MainWindow", "sin(x)", nullptr));
        tan->setText(QCoreApplication::translate("MainWindow", "tan(x)", nullptr));
        acos->setText(QCoreApplication::translate("MainWindow", "acos(x)", nullptr));
        asin->setText(QCoreApplication::translate("MainWindow", "asin(x)", nullptr));
        atan->setText(QCoreApplication::translate("MainWindow", "atan(x)", nullptr));
        sqrt->setText(QCoreApplication::translate("MainWindow", "sqrt(x)", nullptr));
        ln->setText(QCoreApplication::translate("MainWindow", "ln(x)", nullptr));
        log->setText(QCoreApplication::translate("MainWindow", "log(x)", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X (\320\273\320\265\320\262\320\260\321\217 \320\270 \320\277\321\200\320\260\320\262\321\213\320\265 \320\263\321\200\320\260\320\275\320\270\321\206\321\213)", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Y (\320\275\320\270\320\266\320\275\321\217\321\217 \320\270 \320\262\320\265\321\200\321\205\320\275\320\270\320\265 \320\263\321\200\320\260\320\275\320\270\321\206\321\213)", nullptr));
        plotGrapth->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
