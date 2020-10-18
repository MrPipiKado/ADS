/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *input;
    QTableWidget *output;
    QSpinBox *row;
    QSpinBox *column;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *textEdit;
    QPushButton *enter;
    QPushButton *sort;
    QPushButton *ramdom;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1032, 594);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        input = new QTableWidget(centralwidget);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(20, 30, 411, 192));
        output = new QTableWidget(centralwidget);
        output->setObjectName(QString::fromUtf8("output"));
        output->setGeometry(QRect(10, 321, 421, 221));
        row = new QSpinBox(centralwidget);
        row->setObjectName(QString::fromUtf8("row"));
        row->setGeometry(QRect(30, 250, 42, 26));
        row->setMinimum(1);
        column = new QSpinBox(centralwidget);
        column->setObjectName(QString::fromUtf8("column"));
        column->setGeometry(QRect(100, 250, 42, 26));
        column->setMinimum(1);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 230, 67, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 230, 67, 17));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(460, 30, 541, 511));
        enter = new QPushButton(centralwidget);
        enter->setObjectName(QString::fromUtf8("enter"));
        enter->setGeometry(QRect(250, 250, 89, 25));
        sort = new QPushButton(centralwidget);
        sort->setObjectName(QString::fromUtf8("sort"));
        sort->setGeometry(QRect(340, 250, 89, 25));
        ramdom = new QPushButton(centralwidget);
        ramdom->setObjectName(QString::fromUtf8("ramdom"));
        ramdom->setGeometry(QRect(160, 250, 89, 25));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(460, 10, 67, 17));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 300, 101, 17));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1032, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Row", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Column", nullptr));
        enter->setText(QCoreApplication::translate("MainWindow", "ENTER", nullptr));
        sort->setText(QCoreApplication::translate("MainWindow", "SORT", nullptr));
        ramdom->setText(QCoreApplication::translate("MainWindow", "RANDOM", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Shell", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "OUTPUT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
