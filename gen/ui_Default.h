/********************************************************************************
** Form generated from reading UI file 'Default.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEFAULT_H
#define UI_DEFAULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *mPathLabel;
    QPushButton *mSelectBtn;
    QLineEdit *mPathEditor;
    QLabel *mNotifyLabel;
    QSpacerItem *mVerticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(540, 185);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 521, 121));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        mPathLabel = new QLabel(gridLayoutWidget);
        mPathLabel->setObjectName(QStringLiteral("mPathLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mPathLabel->sizePolicy().hasHeightForWidth());
        mPathLabel->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        mPathLabel->setFont(font);

        gridLayout->addWidget(mPathLabel, 2, 0, 1, 1);

        mSelectBtn = new QPushButton(gridLayoutWidget);
        mSelectBtn->setObjectName(QStringLiteral("mSelectBtn"));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(18);
        mSelectBtn->setFont(font1);

        gridLayout->addWidget(mSelectBtn, 2, 2, 1, 1);

        mPathEditor = new QLineEdit(gridLayoutWidget);
        mPathEditor->setObjectName(QStringLiteral("mPathEditor"));
        mPathEditor->setFont(font1);

        gridLayout->addWidget(mPathEditor, 2, 1, 1, 1);

        mNotifyLabel = new QLabel(gridLayoutWidget);
        mNotifyLabel->setObjectName(QStringLiteral("mNotifyLabel"));
        QFont font2;
        font2.setFamily(QStringLiteral("Calibri"));
        font2.setPointSize(36);
        font2.setBold(true);
        font2.setWeight(75);
        mNotifyLabel->setFont(font2);

        gridLayout->addWidget(mNotifyLabel, 0, 0, 1, 3);

        mVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(mVerticalSpacer, 1, 0, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 540, 21));
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
        mPathLabel->setText(QApplication::translate("MainWindow", "Data Path:", nullptr));
        mSelectBtn->setText(QApplication::translate("MainWindow", "Select ...", nullptr));
        mNotifyLabel->setText(QApplication::translate("MainWindow", "Wait for Connection ......", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEFAULT_H
