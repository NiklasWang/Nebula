/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QLabel *defaultLabel;
    QLabel *dataPathLabel;
    QLineEdit *dataPathEdit;
    QPushButton *selectButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(556, 208);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        defaultLabel = new QLabel(centralWidget);
        defaultLabel->setObjectName(QStringLiteral("defaultLabel"));
        defaultLabel->setGeometry(QRect(30, 20, 491, 81));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        defaultLabel->setFont(font);
        dataPathLabel = new QLabel(centralWidget);
        dataPathLabel->setObjectName(QStringLiteral("dataPathLabel"));
        dataPathLabel->setGeometry(QRect(30, 110, 91, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(16);
        font1.setBold(false);
        font1.setWeight(50);
        dataPathLabel->setFont(font1);
        dataPathEdit = new QLineEdit(centralWidget);
        dataPathEdit->setObjectName(QStringLiteral("dataPathEdit"));
        dataPathEdit->setGeometry(QRect(130, 120, 301, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Calibri"));
        font2.setPointSize(18);
        dataPathEdit->setFont(font2);
        selectButton = new QPushButton(centralWidget);
        selectButton->setObjectName(QStringLiteral("selectButton"));
        selectButton->setGeometry(QRect(444, 120, 91, 31));
        QFont font3;
        font3.setFamily(QStringLiteral("Calibri"));
        font3.setPointSize(16);
        selectButton->setFont(font3);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 556, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Nebula v0.0.1", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));
        defaultLabel->setText(QApplication::translate("MainWindow", "Wait for Connection ......", nullptr));
        dataPathLabel->setText(QApplication::translate("MainWindow", "Data Path:", nullptr));
        selectButton->setText(QApplication::translate("MainWindow", "Select...", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
