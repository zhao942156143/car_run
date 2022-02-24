/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *push_start;
    QPushButton *push_stop;
    QLabel *label;
    QCustomPlot *plot_che;
    QCustomPlot *plot_UTM;
    QLabel *label_2;
    QLineEdit *setCar_lat;
    QTextBrowser *text_steertho;
    QTextBrowser *text_cheti;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QTextBrowser *text_GPSIMU;
    QLineEdit *setCar_lon;
    QLineEdit *setCar_h;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLineEdit *kp1;
    QLineEdit *kd2;
    QLineEdit *kd1;
    QLineEdit *kp2;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLineEdit *kpt;
    QLineEdit *kdt;
    QLineEdit *kpb;
    QLineEdit *kdb;
    QTextBrowser *text_CLOG;
    QLabel *label_13;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(960, 639);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        push_start = new QPushButton(centralWidget);
        push_start->setObjectName(QStringLiteral("push_start"));
        push_start->setGeometry(QRect(750, 260, 81, 31));
        push_stop = new QPushButton(centralWidget);
        push_stop->setObjectName(QStringLiteral("push_stop"));
        push_stop->setGeometry(QRect(860, 260, 81, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(210, 290, 71, 16));
        plot_che = new QCustomPlot(centralWidget);
        plot_che->setObjectName(QStringLiteral("plot_che"));
        plot_che->setGeometry(QRect(10, 10, 481, 271));
        plot_UTM = new QCustomPlot(centralWidget);
        plot_UTM->setObjectName(QStringLiteral("plot_UTM"));
        plot_UTM->setGeometry(QRect(10, 310, 481, 241));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 560, 81, 16));
        setCar_lat = new QLineEdit(centralWidget);
        setCar_lat->setObjectName(QStringLiteral("setCar_lat"));
        setCar_lat->setGeometry(QRect(600, 10, 131, 20));
        text_steertho = new QTextBrowser(centralWidget);
        text_steertho->setObjectName(QStringLiteral("text_steertho"));
        text_steertho->setGeometry(QRect(520, 430, 191, 121));
        text_cheti = new QTextBrowser(centralWidget);
        text_cheti->setObjectName(QStringLiteral("text_cheti"));
        text_cheti->setGeometry(QRect(740, 430, 201, 121));
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(790, 560, 101, 16));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(670, 400, 91, 16));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(560, 560, 131, 20));
        text_GPSIMU = new QTextBrowser(centralWidget);
        text_GPSIMU->setObjectName(QStringLiteral("text_GPSIMU"));
        text_GPSIMU->setGeometry(QRect(520, 310, 421, 81));
        setCar_lon = new QLineEdit(centralWidget);
        setCar_lon->setObjectName(QStringLiteral("setCar_lon"));
        setCar_lon->setGeometry(QRect(600, 40, 131, 20));
        setCar_h = new QLineEdit(centralWidget);
        setCar_h->setObjectName(QStringLiteral("setCar_h"));
        setCar_h->setGeometry(QRect(600, 70, 131, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(510, 10, 71, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(510, 40, 54, 12));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(510, 70, 71, 20));
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(760, 10, 54, 12));
        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(760, 40, 54, 12));
        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(760, 70, 54, 12));
        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(760, 100, 54, 12));
        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(760, 130, 54, 12));
        kp1 = new QLineEdit(centralWidget);
        kp1->setObjectName(QStringLiteral("kp1"));
        kp1->setGeometry(QRect(790, 10, 131, 20));
        kd2 = new QLineEdit(centralWidget);
        kd2->setObjectName(QStringLiteral("kd2"));
        kd2->setGeometry(QRect(790, 100, 131, 20));
        kd1 = new QLineEdit(centralWidget);
        kd1->setObjectName(QStringLiteral("kd1"));
        kd1->setGeometry(QRect(790, 70, 131, 20));
        kp2 = new QLineEdit(centralWidget);
        kp2->setObjectName(QStringLiteral("kp2"));
        kp2->setGeometry(QRect(790, 40, 131, 20));
        label_22 = new QLabel(centralWidget);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(760, 160, 54, 12));
        label_23 = new QLabel(centralWidget);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(760, 190, 54, 12));
        label_24 = new QLabel(centralWidget);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(760, 220, 54, 12));
        kpt = new QLineEdit(centralWidget);
        kpt->setObjectName(QStringLiteral("kpt"));
        kpt->setGeometry(QRect(790, 130, 131, 20));
        kdt = new QLineEdit(centralWidget);
        kdt->setObjectName(QStringLiteral("kdt"));
        kdt->setGeometry(QRect(790, 160, 131, 20));
        kpb = new QLineEdit(centralWidget);
        kpb->setObjectName(QStringLiteral("kpb"));
        kpb->setGeometry(QRect(790, 190, 131, 20));
        kdb = new QLineEdit(centralWidget);
        kdb->setObjectName(QStringLiteral("kdb"));
        kdb->setGeometry(QRect(790, 220, 131, 20));
        text_CLOG = new QTextBrowser(centralWidget);
        text_CLOG->setObjectName(QStringLiteral("text_CLOG"));
        text_CLOG->setGeometry(QRect(500, 100, 241, 181));
        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(550, 280, 141, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        push_start->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", 0));
        push_stop->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237", 0));
        label->setText(QApplication::translate("MainWindow", "\350\275\246\344\275\223\345\235\220\346\240\207\347\263\273", 0));
        label_2->setText(QApplication::translate("MainWindow", "UTM\345\235\220\346\240\207\347\263\273", 0));
        setCar_lat->setText(QApplication::translate("MainWindow", "31.1293645", 0));
        label_10->setText(QApplication::translate("MainWindow", "\350\275\246\344\275\223\344\275\215\345\247\277\344\277\241\346\201\257", 0));
        label_11->setText(QApplication::translate("MainWindow", "GPS/IMU\344\277\241\346\201\257", 0));
        label_12->setText(QApplication::translate("MainWindow", "\346\226\271\345\220\221\347\233\230/\346\262\271\351\227\250/\345\210\266\345\212\250\344\277\241\346\201\257", 0));
        setCar_lon->setText(QApplication::translate("MainWindow", "120.66194331", 0));
        setCar_h->setText(QApplication::translate("MainWindow", "270", 0));
        label_3->setText(QApplication::translate("MainWindow", "\346\250\241\346\213\237\347\202\271Lat", 0));
        label_7->setText(QApplication::translate("MainWindow", "\346\250\241\346\213\237\347\202\271Lon", 0));
        label_9->setText(QApplication::translate("MainWindow", "\346\250\241\346\213\237\347\202\271\350\210\252\345\220\221\350\247\222", 0));
        label_17->setText(QApplication::translate("MainWindow", "kp1", 0));
        label_18->setText(QApplication::translate("MainWindow", "kp2", 0));
        label_19->setText(QApplication::translate("MainWindow", "kd1", 0));
        label_20->setText(QApplication::translate("MainWindow", "kd2", 0));
        label_21->setText(QApplication::translate("MainWindow", "kpt", 0));
        kp1->setText(QApplication::translate("MainWindow", "20", 0));
        kd2->setText(QApplication::translate("MainWindow", "0", 0));
        kd1->setText(QApplication::translate("MainWindow", "0", 0));
        kp2->setText(QApplication::translate("MainWindow", "12", 0));
        label_22->setText(QApplication::translate("MainWindow", "kdt", 0));
        label_23->setText(QApplication::translate("MainWindow", "kpb", 0));
        label_24->setText(QApplication::translate("MainWindow", "kdb", 0));
        kpt->setText(QApplication::translate("MainWindow", "10", 0));
        kdt->setText(QApplication::translate("MainWindow", "0", 0));
        kpb->setText(QApplication::translate("MainWindow", "10", 0));
        kdb->setText(QApplication::translate("MainWindow", "0", 0));
        label_13->setText(QApplication::translate("MainWindow", "\344\276\247\345\220\221\345\201\217\345\267\256\345\222\214\350\210\252\345\220\221\345\201\217\345\267\256\344\277\241\346\201\257", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
