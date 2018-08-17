#include <QApplication>

#include "utils/common.h"
#include "core/common.h"
#include "core/MainWindow.h"
#include "ui/DefaultUi.h"
#include "ui/UiLayout.h"

#define DEFAULT_UI_WIDTH  560
#define DEFAULT_UI_HEIGHT 210
#define DEFAULT_UI_MENU_HEIGHT 21

namespace nebula {

DefaultUi::DefaultUi(QWidget *parent) :
    mParent(parent),
    mDefaultLabel(nullptr),
    mDataPathLabel(nullptr),
    mDataPathEdit(nullptr),
    mSelectButton(nullptr)
{
}

DefaultUi::~DefaultUi()
{
    mDefaultLabel->deleteLater();
    mDataPathLabel->deleteLater();
    mDataPathEdit->deleteLater();
    mSelectButton->deleteLater();
}

int32_t DefaultUi::setupUi()
{
    int32_t rc = NO_ERROR;
    QFont fontBig;
    QFont fontSmall;

    if (SUCCEED(rc)) {
        mDefaultLabel = new QLabel(mParent);
        mDefaultLabel->setObjectName(QStringLiteral("defaultLabel"));
        mDefaultLabel->setGeometry(QRect(30, 20, 491, 81));
        fontBig.setFamily(QStringLiteral("Calibri"));
        fontBig.setPointSize(36);
        fontBig.setBold(true);
        fontBig.setWeight(75);
        mDefaultLabel->setFont(fontBig);
    }

    if (SUCCEED(rc)) {
        mDataPathLabel = new QLabel(mParent);
        mDataPathLabel->setObjectName(QStringLiteral("dataPathLabel"));
        mDataPathLabel->setGeometry(QRect(30, 110, 91, 41));
    }

    if (SUCCEED(rc)) {
        fontSmall.setFamily(QStringLiteral("Calibri"));
        fontSmall.setPointSize(16);
        fontSmall.setBold(false);
        fontSmall.setWeight(50);
        mDataPathLabel->setFont(fontSmall);
    }

    if (SUCCEED(rc)) {
        mDataPathEdit = new QLineEdit(mParent);
        mDataPathEdit->setObjectName(QStringLiteral("dataPathEdit"));
        mDataPathEdit->setGeometry(QRect(130, 120, 301, 31));
        mDataPathEdit->setFont(fontSmall);
    }

    if (SUCCEED(rc)) {
        mSelectButton = new QPushButton(mParent);
        mSelectButton->setObjectName(QStringLiteral("selectButton"));
        mSelectButton->setGeometry(QRect(444, 120, 91, 31));
        mSelectButton->setFont(fontSmall);
    }

    if (ISNULL(mDefaultLabel) || ISNULL(mDataPathLabel) ||
        ISNULL(mDataPathEdit) || ISNULL(mSelectButton)) {
        rc = NO_MEMORY;
    } else {
        rc = retranslateUi();
    }

    if (SUCCEED(rc)) {
        gMW->resize(DEFAULT_UI_WIDTH, DEFAULT_UI_HEIGHT);
        gMW->setCentralWidget(mParent);
        QMetaObject::connectSlotsByName(gMW);
    }

    return rc;
}

int32_t DefaultUi::retranslateUi()
{
    mDefaultLabel->setText(QApplication::translate("MainWindow", "Wait for Connection ......", nullptr));
    mDataPathLabel->setText(QApplication::translate("MainWindow", "Data Path:", nullptr));
    mSelectButton->setText(QApplication::translate("MainWindow", "Select...", nullptr));

    return NO_ERROR;
}

QSize DefaultUi::getSize()
{
    return QSize(DEFAULT_UI_WIDTH, DEFAULT_UI_HEIGHT);
}

}
