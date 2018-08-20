#include "utils/common.h"
#include "core/common.h"
#include "ui/DeviceUi.h"
#include "ui/UiLayout.h"
#include "core/MainWindow.h"

namespace nebula {

int32_t      DeviceUi::kCount = 0;
QWidget     *DeviceUi::kHorizontalLayoutWidget = nullptr;
QHBoxLayout *DeviceUi::kHorizontalLayout = nullptr;

DeviceUi::DeviceUi(QWidget *parent, QString &name, int32_t id) :
    mId(id),
    mName(name),
    mParent(parent),
    mGroupBox(nullptr),
    mGridLayoutWidget(nullptr),
    mGridLayout(nullptr),
    mPicture0(nullptr),
    mText0(nullptr),
    mPicture1(nullptr),
    mText1(nullptr),
    mPicture2(nullptr),
    mText2(nullptr),
    mPicture3(nullptr),
    mText3(nullptr),
    mResult(nullptr),
    mDebugEditor(nullptr)
{
    kCount++;
}

DeviceUi::~DeviceUi()
{
    kCount--;
    mGroupBox->setParent(nullptr);
    mGroupBox->deleteLater();
    if (kCount == 0) {
        kHorizontalLayoutWidget->setParent(nullptr);
        kHorizontalLayoutWidget->deleteLater();
        kHorizontalLayoutWidget = nullptr;
        kHorizontalLayout = nullptr;
    }
}

int32_t DeviceUi::setupUi()
{
    int32_t rc = NO_ERROR;
    int32_t x = gMW->width();
    int32_t y = gMW->height();
    QFont font;
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    if (SUCCEED(rc)) {
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(26);
        font.setBold(true);
        font.setWeight(75);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
    }

    if (SUCCEED(rc)) {
        int32_t width = 0;
        int32_t height = 0;
        QSize size = getSize();
        if (kCount == 1) {
            width = size.width() + 2 * DEVICE_UI_LEFT_MARGIN;
            height = size.height() + 2 * DEVICE_UI_TOP_MARGIN;
            x = y = 0;
        } else {
            width = x + size.width();
            height = y > size.height() ? y : size.height();
        }
        gMW->resize(width, height);
    }

    if (SUCCEED(rc)) {
        if (ISNULL(kHorizontalLayoutWidget)) {
            kHorizontalLayoutWidget = new QWidget(mParent);
            kHorizontalLayoutWidget->setObjectName(QStringLiteral("kHorizontalLayoutWidget"));
            kHorizontalLayoutWidget->setGeometry(QRect(
                DEVICE_UI_LEFT_MARGIN, DEVICE_UI_TOP_MARGIN,
                DEVICE_UI_WIDTH, DEVICE_UI_HEIGHT));

            kHorizontalLayout = new QHBoxLayout(kHorizontalLayoutWidget);
            kHorizontalLayout->setObjectName(QStringLiteral("kHorizontalLayout"));
            kHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        } else {
            QRect rect = kHorizontalLayoutWidget->geometry();
            kHorizontalLayoutWidget->setGeometry(QRect(
                DEVICE_UI_LEFT_MARGIN, DEVICE_UI_TOP_MARGIN,
                DEVICE_UI_WIDTH + rect.width(), DEVICE_UI_HEIGHT));
            kHorizontalLayoutWidget->updateGeometry();
        }
    }

    if (SUCCEED(rc)) {
        mGroupBox = new QGroupBox(kHorizontalLayoutWidget);
        mGroupBox->setObjectName("mGroupBox_" + mId);
    }

    if (SUCCEED(rc)) {
        mGridLayoutWidget = new QWidget(mGroupBox);
        mGridLayoutWidget->setObjectName("mGridLayoutWidget_" + mId);
        mGridLayoutWidget->setGeometry(QRect(
            GROUP_BOX_LEFT_MARGIN, GROUP_BOX_TOP_MARGIN,
            GROUP_BOX_WIDTH, GROUP_BOX_HEIGHT));

        mGridLayout = new QGridLayout(mGridLayoutWidget);
        mGridLayout->setObjectName("mGridLayout_" + mId);
        mGridLayout->setContentsMargins(0, 0, 0, 0);
    }

    if (SUCCEED(rc)) {
        mPicture0 = new QLabel(mGridLayoutWidget);
        mPicture0->setObjectName("mPicture0_" + mId);
        mPicture0->setMinimumSize(QSize(100, 100));
        mGridLayout->addWidget(mPicture0, 0, 0, 1, 1);

        mText0 = new QLabel(mGridLayoutWidget);
        mText0->setObjectName("mText0_" + mId);
        sizePolicy.setHeightForWidth(mText0->sizePolicy().hasHeightForWidth());
        mText0->setSizePolicy(sizePolicy);
        mText0->setFont(font);
        mGridLayout->addWidget(mText0, 0, 1, 1, 1);
    }

    if (SUCCEED(rc)) {
        mPicture1 = new QLabel(mGridLayoutWidget);
        mPicture1->setObjectName("mPicture1_" + mId);
        mPicture1->setMinimumSize(QSize(100, 100));
        mGridLayout->addWidget(mPicture1, 1, 0, 1, 1);

        mText1 = new QLabel(mGridLayoutWidget);
        mText1->setObjectName("mText1_" + mId);
        sizePolicy.setHeightForWidth(mText1->sizePolicy().hasHeightForWidth());
        mText1->setSizePolicy(sizePolicy);
        mText1->setFont(font);
        mGridLayout->addWidget(mText1, 1, 1, 1, 1);
    }

    if (SUCCEED(rc)) {
        mPicture2 = new QLabel(mGridLayoutWidget);
        mPicture2->setObjectName("mPicture2_" + mId);
        mPicture2->setMinimumSize(QSize(100, 100));
        mGridLayout->addWidget(mPicture2, 2, 0, 1, 1);

        mText2 = new QLabel(mGridLayoutWidget);
        mText2->setObjectName("mText2_" + mId);
        sizePolicy.setHeightForWidth(mText2->sizePolicy().hasHeightForWidth());
        mText2->setSizePolicy(sizePolicy);
        mText2->setFont(font);
        mGridLayout->addWidget(mText2, 2, 1, 1, 1);
    }

    if (SUCCEED(rc)) {
        mPicture3 = new QLabel(mGridLayoutWidget);
        mPicture3->setObjectName("mPicture3_" + mId);
        mGridLayout->addWidget(mPicture3, 3, 0, 1, 1);

        mText3 = new QLabel(mGridLayoutWidget);
        mText3->setObjectName("mText3_" + mId);
        sizePolicy.setHeightForWidth(mText3->sizePolicy().hasHeightForWidth());
        mText3->setSizePolicy(sizePolicy);
        mText3->setFont(font);
        mGridLayout->addWidget(mText3, 3, 1, 1, 1);
    }

    if (SUCCEED(rc)) {
        mResult = new QLabel(mGridLayoutWidget);
        mResult->setObjectName("mResult_" + mId);
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        font.setPointSize(60);
        font.setBold(true);
        font.setWeight(75);
        mResult->setFont(font);
        mResult->setAlignment(Qt::AlignCenter);
        mGridLayout->addWidget(mResult, 4, 0, 1, 2);
    }

    if (SUCCEED(rc)) {
        mDebugEditor = new QTextEdit(mGridLayoutWidget);
        mDebugEditor->setObjectName("mDebugEditor_" + mId);
        sizePolicy.setHeightForWidth(mDebugEditor->sizePolicy().hasHeightForWidth());
        mDebugEditor->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Courier New"));
        mDebugEditor->setFont(font);
        mGridLayout->addWidget(mDebugEditor, 5, 0, 1, 2);

    }

    if (ISNULL(mGroupBox) || ISNULL(mGridLayoutWidget) ||
        ISNULL(mGridLayout) || ISNULL(mPicture0) ||
        ISNULL(mText0) || ISNULL(mPicture1) ||
        ISNULL(mText1) || ISNULL(mPicture2) ||
        ISNULL(mText2) || ISNULL(mPicture3) ||
        ISNULL(mText3) || ISNULL(mResult) ||
        ISNULL(mDebugEditor) || ISNULL(kHorizontalLayout) ||
        ISNULL(kHorizontalLayoutWidget)) {
        rc = NO_MEMORY;
    } else {
        rc = retranslateUi();
    }

    if (SUCCEED(rc)) {
        kHorizontalLayout->addWidget(mGroupBox);
        gMW->setCentralWidget(mParent);
        kHorizontalLayoutWidget->show();
        QMetaObject::connectSlotsByName(gMW);
    }

    return rc;
}

int32_t DeviceUi::retranslateUi()
{
    QString title = QString("Deivce ") + QString::number(mId) + ", " + getName();
    mGroupBox->setTitle(QApplication::translate("MainWindow", title.toLocal8Bit().data(), nullptr));
    mPicture0->setText(QString());
    mText0->setText(QApplication::translate("MainWindow", "Wait for Connection", nullptr));
    mText1->setText(QApplication::translate("MainWindow", "Remote Controlling", nullptr));
    mPicture2->setText(QString());
    mText2->setText(QApplication::translate("MainWindow", "Running Algorithm", nullptr));
    mPicture3->setText(QString());
    mPicture1->setText(QString());
    mResult->setText(QApplication::translate("MainWindow", "......", nullptr));
    mText3->setText(QApplication::translate("MainWindow", "Saving Record", nullptr));
    mDebugEditor->setHtml(QApplication::translate("MainWindow",
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:'Courier New'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; "
        "text-indent:0px;\">&gt; Wish you have a pleasant day. :)</p></body></html>", nullptr));

    return NO_ERROR;
}

QString DeviceUi::getName()
{
    return mName;
}

QSize DeviceUi::getSize()
{
    return QSize(DEVICE_UI_WIDTH, DEVICE_UI_HEIGHT);
}

}
