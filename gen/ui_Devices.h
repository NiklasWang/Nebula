/********************************************************************************
** Form generated from reading UI file 'devices.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICES_H
#define UI_DEVICES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *kHorizontalLayout;
    QGroupBox *mGroupBox_0;
    QWidget *gridLayoutWidget;
    QGridLayout *mGridLayout_0;
    QLabel *mPicture0_0;
    QLabel *mText0_0;
    QLabel *mText1_0;
    QLabel *mPicture2_0;
    QLabel *mText2_0;
    QLabel *mPicture3_0;
    QLabel *mPicture1_0;
    QLabel *mResult_0;
    QLabel *mText3_0;
    QTextEdit *mDebugEditor_0;
    QGroupBox *mGroupBox_1;
    QWidget *gridLayoutWidget_2;
    QGridLayout *mGridLayout_1;
    QLabel *mPicture0_1;
    QLabel *mText0_1;
    QLabel *mText1_1;
    QLabel *mPicture2_1;
    QLabel *mText2_1;
    QLabel *mPicture3_1;
    QLabel *mPicture1_1;
    QLabel *mResult_1;
    QLabel *mText3_1;
    QTextEdit *mDebugEditor_1;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(950, 900);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 931, 841));
        kHorizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        kHorizontalLayout->setObjectName(QStringLiteral("kHorizontalLayout"));
        kHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        mGroupBox_0 = new QGroupBox(horizontalLayoutWidget);
        mGroupBox_0->setObjectName(QStringLiteral("mGroupBox_0"));
        gridLayoutWidget = new QWidget(mGroupBox_0);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 19, 441, 811));
        mGridLayout_0 = new QGridLayout(gridLayoutWidget);
        mGridLayout_0->setObjectName(QStringLiteral("mGridLayout_0"));
        mGridLayout_0->setContentsMargins(0, 0, 0, 0);
        mPicture0_0 = new QLabel(gridLayoutWidget);
        mPicture0_0->setObjectName(QStringLiteral("mPicture0_0"));
        mPicture0_0->setMinimumSize(QSize(100, 100));

        mGridLayout_0->addWidget(mPicture0_0, 0, 0, 1, 1);

        mText0_0 = new QLabel(gridLayoutWidget);
        mText0_0->setObjectName(QStringLiteral("mText0_0"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mText0_0->sizePolicy().hasHeightForWidth());
        mText0_0->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(26);
        font.setBold(true);
        font.setWeight(75);
        mText0_0->setFont(font);

        mGridLayout_0->addWidget(mText0_0, 0, 1, 1, 1);

        mText1_0 = new QLabel(gridLayoutWidget);
        mText1_0->setObjectName(QStringLiteral("mText1_0"));
        sizePolicy.setHeightForWidth(mText1_0->sizePolicy().hasHeightForWidth());
        mText1_0->setSizePolicy(sizePolicy);
        mText1_0->setFont(font);

        mGridLayout_0->addWidget(mText1_0, 1, 1, 1, 1);

        mPicture2_0 = new QLabel(gridLayoutWidget);
        mPicture2_0->setObjectName(QStringLiteral("mPicture2_0"));
        mPicture2_0->setMinimumSize(QSize(100, 100));

        mGridLayout_0->addWidget(mPicture2_0, 2, 0, 1, 1);

        mText2_0 = new QLabel(gridLayoutWidget);
        mText2_0->setObjectName(QStringLiteral("mText2_0"));
        sizePolicy.setHeightForWidth(mText2_0->sizePolicy().hasHeightForWidth());
        mText2_0->setSizePolicy(sizePolicy);
        mText2_0->setFont(font);

        mGridLayout_0->addWidget(mText2_0, 2, 1, 1, 1);

        mPicture3_0 = new QLabel(gridLayoutWidget);
        mPicture3_0->setObjectName(QStringLiteral("mPicture3_0"));

        mGridLayout_0->addWidget(mPicture3_0, 3, 0, 1, 1);

        mPicture1_0 = new QLabel(gridLayoutWidget);
        mPicture1_0->setObjectName(QStringLiteral("mPicture1_0"));
        mPicture1_0->setMinimumSize(QSize(100, 100));

        mGridLayout_0->addWidget(mPicture1_0, 1, 0, 1, 1);

        mResult_0 = new QLabel(gridLayoutWidget);
        mResult_0->setObjectName(QStringLiteral("mResult_0"));
        QFont font1;
        font1.setFamily(QStringLiteral("Courier New"));
        font1.setPointSize(60);
        font1.setBold(true);
        font1.setWeight(75);
        mResult_0->setFont(font1);
        mResult_0->setAlignment(Qt::AlignCenter);

        mGridLayout_0->addWidget(mResult_0, 4, 0, 1, 2);

        mText3_0 = new QLabel(gridLayoutWidget);
        mText3_0->setObjectName(QStringLiteral("mText3_0"));
        sizePolicy.setHeightForWidth(mText3_0->sizePolicy().hasHeightForWidth());
        mText3_0->setSizePolicy(sizePolicy);
        mText3_0->setFont(font);

        mGridLayout_0->addWidget(mText3_0, 3, 1, 1, 1);

        mDebugEditor_0 = new QTextEdit(gridLayoutWidget);
        mDebugEditor_0->setObjectName(QStringLiteral("mDebugEditor_0"));
        sizePolicy.setHeightForWidth(mDebugEditor_0->sizePolicy().hasHeightForWidth());
        mDebugEditor_0->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QStringLiteral("Courier New"));
        mDebugEditor_0->setFont(font2);

        mGridLayout_0->addWidget(mDebugEditor_0, 5, 0, 1, 2);


        kHorizontalLayout->addWidget(mGroupBox_0);

        mGroupBox_1 = new QGroupBox(horizontalLayoutWidget);
        mGroupBox_1->setObjectName(QStringLiteral("mGroupBox_1"));
        gridLayoutWidget_2 = new QWidget(mGroupBox_1);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(9, 19, 441, 811));
        mGridLayout_1 = new QGridLayout(gridLayoutWidget_2);
        mGridLayout_1->setObjectName(QStringLiteral("mGridLayout_1"));
        mGridLayout_1->setContentsMargins(0, 0, 0, 0);
        mPicture0_1 = new QLabel(gridLayoutWidget_2);
        mPicture0_1->setObjectName(QStringLiteral("mPicture0_1"));
        mPicture0_1->setMinimumSize(QSize(100, 100));

        mGridLayout_1->addWidget(mPicture0_1, 0, 0, 1, 1);

        mText0_1 = new QLabel(gridLayoutWidget_2);
        mText0_1->setObjectName(QStringLiteral("mText0_1"));
        sizePolicy.setHeightForWidth(mText0_1->sizePolicy().hasHeightForWidth());
        mText0_1->setSizePolicy(sizePolicy);
        mText0_1->setFont(font);

        mGridLayout_1->addWidget(mText0_1, 0, 1, 1, 1);

        mText1_1 = new QLabel(gridLayoutWidget_2);
        mText1_1->setObjectName(QStringLiteral("mText1_1"));
        sizePolicy.setHeightForWidth(mText1_1->sizePolicy().hasHeightForWidth());
        mText1_1->setSizePolicy(sizePolicy);
        mText1_1->setFont(font);

        mGridLayout_1->addWidget(mText1_1, 1, 1, 1, 1);

        mPicture2_1 = new QLabel(gridLayoutWidget_2);
        mPicture2_1->setObjectName(QStringLiteral("mPicture2_1"));
        mPicture2_1->setMinimumSize(QSize(100, 100));

        mGridLayout_1->addWidget(mPicture2_1, 2, 0, 1, 1);

        mText2_1 = new QLabel(gridLayoutWidget_2);
        mText2_1->setObjectName(QStringLiteral("mText2_1"));
        sizePolicy.setHeightForWidth(mText2_1->sizePolicy().hasHeightForWidth());
        mText2_1->setSizePolicy(sizePolicy);
        mText2_1->setFont(font);

        mGridLayout_1->addWidget(mText2_1, 2, 1, 1, 1);

        mPicture3_1 = new QLabel(gridLayoutWidget_2);
        mPicture3_1->setObjectName(QStringLiteral("mPicture3_1"));

        mGridLayout_1->addWidget(mPicture3_1, 3, 0, 1, 1);

        mPicture1_1 = new QLabel(gridLayoutWidget_2);
        mPicture1_1->setObjectName(QStringLiteral("mPicture1_1"));
        mPicture1_1->setMinimumSize(QSize(100, 100));

        mGridLayout_1->addWidget(mPicture1_1, 1, 0, 1, 1);

        mResult_1 = new QLabel(gridLayoutWidget_2);
        mResult_1->setObjectName(QStringLiteral("mResult_1"));
        mResult_1->setFont(font1);
        mResult_1->setAlignment(Qt::AlignCenter);

        mGridLayout_1->addWidget(mResult_1, 4, 0, 1, 2);

        mText3_1 = new QLabel(gridLayoutWidget_2);
        mText3_1->setObjectName(QStringLiteral("mText3_1"));
        sizePolicy.setHeightForWidth(mText3_1->sizePolicy().hasHeightForWidth());
        mText3_1->setSizePolicy(sizePolicy);
        mText3_1->setFont(font);

        mGridLayout_1->addWidget(mText3_1, 3, 1, 1, 1);

        mDebugEditor_1 = new QTextEdit(gridLayoutWidget_2);
        mDebugEditor_1->setObjectName(QStringLiteral("mDebugEditor_1"));
        sizePolicy.setHeightForWidth(mDebugEditor_1->sizePolicy().hasHeightForWidth());
        mDebugEditor_1->setSizePolicy(sizePolicy);
        mDebugEditor_1->setFont(font2);

        mGridLayout_1->addWidget(mDebugEditor_1, 5, 0, 1, 2);


        kHorizontalLayout->addWidget(mGroupBox_1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 950, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        mGroupBox_0->setTitle(QApplication::translate("MainWindow", "Deivce 0, 12345", nullptr));
        mPicture0_0->setText(QString());
        mText0_0->setText(QApplication::translate("MainWindow", "Wait for Connection", nullptr));
        mText1_0->setText(QApplication::translate("MainWindow", "Remote Controlling", nullptr));
        mPicture2_0->setText(QString());
        mText2_0->setText(QApplication::translate("MainWindow", "Running Algorithm", nullptr));
        mPicture3_0->setText(QString());
        mPicture1_0->setText(QString());
        mResult_0->setText(QApplication::translate("MainWindow", "SUCCEED", nullptr));
        mText3_0->setText(QApplication::translate("MainWindow", "Saving Record", nullptr));
        mDebugEditor_0->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&gt; Wish you have a pleasant day. :)</p></body></html>", nullptr));
        mGroupBox_1->setTitle(QApplication::translate("MainWindow", "Deivce 1, 67890", nullptr));
        mPicture0_1->setText(QString());
        mText0_1->setText(QApplication::translate("MainWindow", "Wait for Connection", nullptr));
        mText1_1->setText(QApplication::translate("MainWindow", "Remote Controlling", nullptr));
        mPicture2_1->setText(QString());
        mText2_1->setText(QApplication::translate("MainWindow", "Running Algorithm", nullptr));
        mPicture3_1->setText(QString());
        mPicture1_1->setText(QString());
        mResult_1->setText(QApplication::translate("MainWindow", "FAILED", nullptr));
        mText3_1->setText(QApplication::translate("MainWindow", "Saving Record", nullptr));
        mDebugEditor_1->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Courier New'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">&gt; Wish you have a pleasant day. :)</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICES_H
