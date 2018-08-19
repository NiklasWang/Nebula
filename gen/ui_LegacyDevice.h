/********************************************************************************
** Form generated from reading UI file 'Device.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICE_H
#define UI_DEVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QGroupBox *groupBox0;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *picture0;
    QLabel *text1;
    QLabel *picture1;
    QLabel *text2;
    QLabel *picture2;
    QLabel *text0;
    QLabel *picture3;
    QLabel *text3;
    QLabel *result;
    QTextEdit *debug;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(520, 900);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox0 = new QGroupBox(centralWidget);
        groupBox0->setObjectName(QStringLiteral("groupBox0"));
        groupBox0->setEnabled(true);
        groupBox0->setGeometry(QRect(10, 10, 500, 850));
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(10);
        groupBox0->setFont(font);
        gridLayoutWidget = new QWidget(groupBox0);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 20, 481, 501));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(20);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        picture0 = new QLabel(gridLayoutWidget);
        picture0->setObjectName(QStringLiteral("picture0"));

        gridLayout->addWidget(picture0, 0, 0, 1, 1);

        text1 = new QLabel(gridLayoutWidget);
        text1->setObjectName(QStringLiteral("text1"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(28);
        font1.setBold(true);
        font1.setWeight(75);
        text1->setFont(font1);

        gridLayout->addWidget(text1, 1, 1, 1, 1);

        picture1 = new QLabel(gridLayoutWidget);
        picture1->setObjectName(QStringLiteral("picture1"));

        gridLayout->addWidget(picture1, 1, 0, 1, 1);

        text2 = new QLabel(gridLayoutWidget);
        text2->setObjectName(QStringLiteral("text2"));
        text2->setFont(font1);

        gridLayout->addWidget(text2, 2, 1, 1, 1);

        picture2 = new QLabel(gridLayoutWidget);
        picture2->setObjectName(QStringLiteral("picture2"));

        gridLayout->addWidget(picture2, 2, 0, 1, 1);

        text0 = new QLabel(gridLayoutWidget);
        text0->setObjectName(QStringLiteral("text0"));
        text0->setFont(font1);

        gridLayout->addWidget(text0, 0, 1, 1, 1);

        picture3 = new QLabel(gridLayoutWidget);
        picture3->setObjectName(QStringLiteral("picture3"));

        gridLayout->addWidget(picture3, 3, 0, 1, 1);

        text3 = new QLabel(gridLayoutWidget);
        text3->setObjectName(QStringLiteral("text3"));
        text3->setFont(font1);

        gridLayout->addWidget(text3, 3, 1, 1, 1);

        gridLayout->setColumnStretch(0, 120);
        gridLayout->setColumnStretch(1, 338);
        result = new QLabel(groupBox0);
        result->setObjectName(QStringLiteral("result"));
        result->setGeometry(QRect(10, 530, 480, 100));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial Black"));
        font2.setPointSize(48);
        font2.setBold(true);
        font2.setWeight(75);
        result->setFont(font2);
        result->setAlignment(Qt::AlignCenter);
        debug = new QTextEdit(groupBox0);
        debug->setObjectName(QStringLiteral("debug"));
        debug->setGeometry(QRect(10, 640, 480, 200));
        debug->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 520, 21));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));
        groupBox0->setTitle(QApplication::translate("MainWindow", "Deivce ID: NA", nullptr));
        picture0->setText(QString());
        text1->setText(QApplication::translate("MainWindow", "Remote Control", nullptr));
        picture1->setText(QString());
        text2->setText(QApplication::translate("MainWindow", "Analysising", nullptr));
        picture2->setText(QString());
        text0->setText(QApplication::translate("MainWindow", "Device Detected", nullptr));
        picture3->setText(QString());
        text3->setText(QApplication::translate("MainWindow", "Saving Record", nullptr));
        result->setText(QApplication::translate("MainWindow", "......", nullptr));
        debug->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&gt; How are you today? :)</p></body></html>", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICE_H
