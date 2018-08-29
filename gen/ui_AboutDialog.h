/********************************************************************************
** Form generated from reading UI file 'AboutDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *mGridLayout;
    QLabel *mSupportLabel;
    QLabel *mPictureLabel;
    QPushButton *mOkButton;
    QLabel *mContactLabel;
    QSpacerItem *mVerticalSpacer;
    QLabel *mCopyrightLabel;
    QLabel *mVersionLabel;
    QLabel *mTitleLabel;
    QSpacerItem *mMiddleHorizontalSpacer;
    QSpacerItem *mLeftHorizontalSpacer;
    QSpacerItem *mRightHorizontalSpacer;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QStringLiteral("AboutDialog"));
        AboutDialog->resize(350, 266);
        gridLayoutWidget = new QWidget(AboutDialog);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 331, 241));
        mGridLayout = new QGridLayout(gridLayoutWidget);
        mGridLayout->setObjectName(QStringLiteral("mGridLayout"));
        mGridLayout->setContentsMargins(0, 0, 0, 0);
        mSupportLabel = new QLabel(gridLayoutWidget);
        mSupportLabel->setObjectName(QStringLiteral("mSupportLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mSupportLabel->sizePolicy().hasHeightForWidth());
        mSupportLabel->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(10);
        mSupportLabel->setFont(font);

        mGridLayout->addWidget(mSupportLabel, 4, 3, 1, 1);

        mPictureLabel = new QLabel(gridLayoutWidget);
        mPictureLabel->setObjectName(QStringLiteral("mPictureLabel"));
        mPictureLabel->setMinimumSize(QSize(125, 200));

        mGridLayout->addWidget(mPictureLabel, 0, 1, 5, 1);

        mOkButton = new QPushButton(gridLayoutWidget);
        mOkButton->setObjectName(QStringLiteral("mOkButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mOkButton->sizePolicy().hasHeightForWidth());
        mOkButton->setSizePolicy(sizePolicy1);
        mOkButton->setMinimumSize(QSize(80, 20));
        QFont font1;
        font1.setFamily(QStringLiteral("Courier"));
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setWeight(75);
        mOkButton->setFont(font1);

        mGridLayout->addWidget(mOkButton, 6, 1, 1, 3);

        mContactLabel = new QLabel(gridLayoutWidget);
        mContactLabel->setObjectName(QStringLiteral("mContactLabel"));
        sizePolicy.setHeightForWidth(mContactLabel->sizePolicy().hasHeightForWidth());
        mContactLabel->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QStringLiteral("Calibri"));
        font2.setPointSize(11);
        mContactLabel->setFont(font2);

        mGridLayout->addWidget(mContactLabel, 3, 3, 1, 1);

        mVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        mGridLayout->addItem(mVerticalSpacer, 5, 1, 1, 3);

        mCopyrightLabel = new QLabel(gridLayoutWidget);
        mCopyrightLabel->setObjectName(QStringLiteral("mCopyrightLabel"));
        sizePolicy.setHeightForWidth(mCopyrightLabel->sizePolicy().hasHeightForWidth());
        mCopyrightLabel->setSizePolicy(sizePolicy);
        mCopyrightLabel->setFont(font2);

        mGridLayout->addWidget(mCopyrightLabel, 2, 3, 1, 1);

        mVersionLabel = new QLabel(gridLayoutWidget);
        mVersionLabel->setObjectName(QStringLiteral("mVersionLabel"));
        sizePolicy.setHeightForWidth(mVersionLabel->sizePolicy().hasHeightForWidth());
        mVersionLabel->setSizePolicy(sizePolicy);
        mVersionLabel->setFont(font1);

        mGridLayout->addWidget(mVersionLabel, 1, 3, 1, 1);

        mTitleLabel = new QLabel(gridLayoutWidget);
        mTitleLabel->setObjectName(QStringLiteral("mTitleLabel"));
        sizePolicy.setHeightForWidth(mTitleLabel->sizePolicy().hasHeightForWidth());
        mTitleLabel->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setFamily(QStringLiteral("Courier"));
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setWeight(75);
        mTitleLabel->setFont(font3);

        mGridLayout->addWidget(mTitleLabel, 0, 3, 1, 1);

        mMiddleHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mGridLayout->addItem(mMiddleHorizontalSpacer, 0, 2, 5, 1);

        mLeftHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mGridLayout->addItem(mLeftHorizontalSpacer, 0, 0, 7, 1);

        mRightHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mGridLayout->addItem(mRightHorizontalSpacer, 0, 4, 7, 1);


        retranslateUi(AboutDialog);

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "About Nebula", nullptr));
        mSupportLabel->setText(QApplication::translate("AboutDialog", "Thanks for choosing.\n"
"Please contact Wang Liang\n"
"for technical support.", nullptr));
        mPictureLabel->setText(QApplication::translate("AboutDialog", "Pic", nullptr));
        mOkButton->setText(QApplication::translate("AboutDialog", "OK", nullptr));
        mContactLabel->setText(QApplication::translate("AboutDialog", "Contact:\n"
"+86 186 1153 3741\n"
"wangliang17@lenovo.com\n"
"niklas.wang@outlook.com", nullptr));
        mCopyrightLabel->setText(QApplication::translate("AboutDialog", "Copyright (C) 2018\n"
"by Wang Liang\n"
"Lenovo Corporation", nullptr));
        mVersionLabel->setText(QApplication::translate("AboutDialog", "Version 0.1.2 - 32bit", nullptr));
        mTitleLabel->setText(QApplication::translate("AboutDialog", "Nebula", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
