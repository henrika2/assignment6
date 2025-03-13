/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *redButton;
    QPushButton *startButton;
    QPushButton *blueButton;
    QLabel *statusLabel;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(408, 325);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        redButton = new QPushButton(centralwidget);
        redButton->setObjectName("redButton");
        redButton->setGeometry(QRect(30, 120, 75, 24));
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(130, 80, 75, 24));
        blueButton = new QPushButton(centralwidget);
        blueButton->setObjectName("blueButton");
        blueButton->setGeometry(QRect(230, 120, 75, 24));
        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setGeometry(QRect(30, 10, 201, 51));
        QFont font;
        font.setPointSize(14);
        statusLabel->setFont(font);
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(100, 180, 151, 23));
        progressBar->setValue(0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 408, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        redButton->setText(QCoreApplication::translate("MainWindow", "Red", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        blueButton->setText(QCoreApplication::translate("MainWindow", "Blue", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Click Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
