#include <QApplication>

#include "utils/common.h"
#include "core/common.h"
#include "core/MainWindow.h"
#include "ui/DefaultUi.h"
#include "ui/UiLayout.h"

#define DEFAULT_UI_WIDTH  521
#define DEFAULT_UI_HEIGHT 121
#define DEFAULT_UI_MENU_STATUS_HEIGHT 40
#define DEFAULT_UI_LEFT_MARGIN 10
#define DEFAULT_UI_TOP_MARGIN  10
#define DEFAULT_UI_MENU_HEIGHT 21

namespace nebula {

DefaultUi::DefaultUi(QWidget *parent) :
    mParent(parent),
    mGridLayoutWidget(nullptr),
    mGridLayout(nullptr),
    mNotifyLabel(nullptr),
    mVerticalSpacer(nullptr),
    mPathLabel(nullptr),
    mPathEditor(nullptr),
    mSelectBtn(nullptr),
{
}

DefaultUi::~DefaultUi()
{
    mGridLayoutWidget->setParent(nullptr);
    mGridLayoutWidget->deleteLater();
}

int32_t DefaultUi::setupUi()
{
    int32_t rc = NO_ERROR;

    if (SUCCEED(rc)) {
        gMW->resize(DEFAULT_UI_WIDTH + 2 * DEFAULT_UI_LEFT_MARGIN,
            DEFAULT_UI_HEIGHT + 2 * DEFAULT_UI_TOP_MARGIN + DEFAULT_UI_MENU_STATUS_HEIGHT);
    }

    if (SUCCEED(rc)) {
        mGridLayoutWidget = new QWidget(parent);
        mGridLayoutWidget->setObjectName(QStringLiteral("mGridLayoutWidget"));
        mGridLayoutWidget->setGeometry(QRect(
            DEFAULT_UI_LEFT_MARGIN, DEFAULT_UI_TOP_MARGIN,
            DEFAULT_UI_WIDTH, DEFAULT_UI_HEIGHT));
        mGridLayout = new QGridLayout(mGridLayoutWidget);
        mGridLayout->setObjectName(QStringLiteral("mGridLayout"));
        mGridLayout->setContentsMargins(0, 0, 0, 0);
    }

    if (SUCCEED(rc)) {
        mPathLabel = new QLabel(mGridLayoutWidget);
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
        mGridLayout->addWidget(mPathLabel, 2, 0, 1, 1);
    }

    if (SUCCEED(rc)) {
        mSelectBtn = new QPushButton(mGridLayoutWidget);
        mSelectBtn->setObjectName(QStringLiteral("mSelectBtn"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(18);
        mSelectBtn->setFont(font);
        mGridLayout->addWidget(mSelectBtn, 2, 2, 1, 1);
    }

    if (SUCCEED(rc)) {
        mPathEditor = new QLineEdit(mGridLayoutWidget);
        mPathEditor->setObjectName(QStringLiteral("mPathEditor"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(18);
        mPathEditor->setFont(font);
        mGridLayout->addWidget(mPathEditor, 2, 1, 1, 1);
    }

    if (SUCCEED(rc)) {
        mNotifyLabel = new QLabel(mGridLayoutWidget);
        mNotifyLabel->setObjectName(QStringLiteral("mNotifyLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        mNotifyLabel->setFont(font);
        mGridLayout->addWidget(mNotifyLabel, 0, 0, 1, 3);
    }

    if (SUCCEED(rc)) {
        mVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        mGridLayout->addItem(mVerticalSpacer, 1, 0, 1, 3);
    }

    if (ISNULL(mNotifyLabel) || ISNULL(mVerticalSpacer) ||
        ISNULL(mPathLabel) || ISNULL(mPathEditor) ||
        ISNULL(mSelectBtn) || ISNULL(mGridLayoutWidget) ||
        ISNULL(mGridLayout)) {
        rc = NO_MEMORY;
    } else {
        rc = retranslateUi();
    }

    if (SUCCEED(rc)) {
        gMW->setCentralWidget(mParent);
        QMetaObject::connectSlotsByName(gMW);
    }

    return rc;
}

int32_t DefaultUi::retranslateUi()
{
    mPathLabel->setText(QApplication::translate("MainWindow", "Data Path:", nullptr));
    mSelectBtn->setText(QApplication::translate("MainWindow", "Select ...", nullptr));
    mNotifyLabel->setText(QApplication::translate("MainWindow", "Wait for Connection ......", nullptr));

    return NO_ERROR;
}

QSize DefaultUi::getSize()
{
    return QSize(DEFAULT_UI_WIDTH + 2 * DEFAULT_UI_LEFT_MARGIN,
        DEFAULT_UI_HEIGHT + 2 * DEFAULT_UI_TOP_MARGIN);
}

}
