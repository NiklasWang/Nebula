#include "utils/common.h"
#include "core/common.h"
#include "DeviceUi.h"
#include "ui/UiLayout.h"

#define DEFAULT_UI_WIDTH  931
#define DEFAULT_UI_HEIGHT 841
#define DEFAULT_UI_LEFT_MARGIN 10
#define DEFAULT_UI_TOP_MARGIN  10

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
    QFont fontNormal, fontTextLabel;
    int32_t x = gMW->width();
    int32_t y = gMW->height();
    int32_t width = 0;
    int32_t height = 0;

    if (SUCCEED(rc)) {
        QSize size = getSize();
        if (!mId) {
            width = size.width();
            height = size.height();
            x = y = 0;
        } else {
            width = x + size.width();
            height = y > size.height() ? y : size.height();
        }
    }

    if (SUCCEED(rc)) {
        mGroupBox = new QGroupBox(mParent);
        mGroupBox->setObjectName(QStringLiteral("groupBox_") + mId);
        mGroupBox->setEnabled(true);
        mGroupBox->setGeometry(QRect(x + GROUP_BOX_WIDTH_MARGIN,
            y + GROUP_BOX_HEIGHT_MARGIN, GROUP_BOX_WIDTH, GROUP_BOX_HEIGHT));
        fontNormal.setFamily(QStringLiteral("Courier New"));
        fontNormal.setPointSize(10);
        mGroupBox->setFont(fontNormal);
    }

    if (SUCCEED(rc)) {
        mGridLayoutWidget = new QWidget(mGroupBox);
        mGridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        mGridLayoutWidget->setGeometry(QRect(10, 20, 481, 501));
    }

    if (SUCCEED(rc)) {
        mGridLayout = new QGridLayout(mGridLayoutWidget);
        mGridLayout->setSpacing(6);
        mGridLayout->setContentsMargins(11, 11, 11, 11);
        mGridLayout->setObjectName(QStringLiteral("gridLayout"));
        mGridLayout->setHorizontalSpacing(20);
        mGridLayout->setVerticalSpacing(6);
        mGridLayout->setContentsMargins(0, 0, 0, 0);
    }

    if (SUCCEED(rc)) {
        mPictureLabel0 = new QLabel(mGridLayoutWidget);
        mPictureLabel0->setObjectName(QStringLiteral("picture0"));
        mGridLayout->addWidget(mPictureLabel0, 0, 0, 1, 1);

        mTextLabel0 = new QLabel(mGridLayoutWidget);
        mTextLabel0->setObjectName(QStringLiteral("text0"));
        fontTextLabel.setFamily(QStringLiteral("Arial"));
        fontTextLabel.setPointSize(28);
        fontTextLabel.setBold(true);
        fontTextLabel.setWeight(75);
        mTextLabel0->setFont(fontTextLabel);
        mGridLayout->addWidget(mTextLabel0, 1, 1, 1, 1);
    }

    if (SUCCEED(rc)) {
        mPictureLabel1 = new QLabel(mGridLayoutWidget);
        mPictureLabel1->setObjectName(QStringLiteral("picture1"));
        mGridLayout->addWidget(mPictureLabel1, 1, 0, 1, 1);

        mTextLabel1 = new QLabel(mGridLayoutWidget);
        mTextLabel1->setObjectName(QStringLiteral("text1"));
        mTextLabel1->setFont(fontTextLabel);
        mGridLayout->addWidget(mTextLabel1, 2, 1, 1, 1);
    }

    if (SUCCEED(rc)) {
        mPictureLabel2 = new QLabel(mGridLayoutWidget);
        mPictureLabel2->setObjectName(QStringLiteral("picture2"));
        mGridLayout->addWidget(mPictureLabel2, 2, 0, 1, 1);

        mTextLabel2 = new QLabel(mGridLayoutWidget);
        mTextLabel2->setObjectName(QStringLiteral("text2"));
        mTextLabel2->setFont(fontTextLabel);
        mGridLayout->addWidget(mTextLabel2, 0, 1, 1, 1);
    }

    if (SUCCEED(rc)) {
        mPictureLabel3 = new QLabel(mGridLayoutWidget);
        mPictureLabel3->setObjectName(QStringLiteral("picture3"));
        mGridLayout->addWidget(mPictureLabel3, 3, 0, 1, 1);

        mTextLabel3 = new QLabel(mGridLayoutWidget);
        mTextLabel3->setObjectName(QStringLiteral("text3"));
        mTextLabel3->setFont(fontTextLabel);
        mGridLayout->addWidget(mTextLabel3, 3, 1, 1, 1);
    }

    if (SUCCEED(rc)) {
        mGridLayout->setColumnStretch(0, 120);
        mGridLayout->setColumnStretch(1, 338);
    }

    if (SUCCEED(rc)) {
        mResultLabel = new QLabel(mGroupBox);
        mResultLabel->setObjectName(QStringLiteral("result"));
        mResultLabel->setGeometry(QRect(10, 530, 480, 100));
        QFont font;
        font.setFamily(QStringLiteral("Arial Black"));
        font.setPointSize(48);
        font.setBold(true);
        font.setWeight(75);
        mResultLabel->setFont(font);
        mResultLabel->setAlignment(Qt::AlignCenter);
    }

    if (SUCCEED(rc)) {
        mDebugEditor = new QTextEdit(mGroupBox);
        mDebugEditor->setObjectName(QStringLiteral("debug"));
        mDebugEditor->setGeometry(QRect(10, 640, 480, 200));
        mDebugEditor->setFont(fontNormal);
    }

    if (ISNULL(mGroupBox)   || ISNULL(mGridLayoutWidget) ||
        ISNULL(mGridLayout) || ISNULL(mPictureLabel0) ||
        ISNULL(mTextLabel0) || ISNULL(mPictureLabel1) ||
        ISNULL(mTextLabel1) || ISNULL(mPictureLabel2) ||
        ISNULL(mTextLabel2) || ISNULL(mPictureLabel3) ||
        ISNULL(mTextLabel3) || ISNULL(mResultLabel) ||
        ISNULL(mDebugEditor)) {
        rc = NO_MEMORY;
    } else {
        rc = retranslateUi();
    }

    if (SUCCEED(rc)) {
        gMW->resize(width, height);
        mGroupBox->show();
        gMW->setCentralWidget(mParent);
        QMetaObject::connectSlotsByName(gMW);
    }

    return rc;
}

int32_t DeviceUi::retranslateUi()
{
    QString title = QString("Deivce ID: ") + QString::number(mId) + " " + getName();
    mGroupBox->setTitle(QApplication::translate("MainWindow", title.toLocal8Bit().data(), nullptr));
    mPictureLabel0->setText(QString());
    mTextLabel0->setText(QApplication::translate("MainWindow", "Remote Control", nullptr));
    mPictureLabel1->setText(QString());
    mTextLabel1->setText(QApplication::translate("MainWindow", "Analysising", nullptr));
    mPictureLabel2->setText(QString());
    mTextLabel2->setText(QApplication::translate("MainWindow", "Device Detected", nullptr));
    mPictureLabel3->setText(QString());
    mTextLabel3->setText(QApplication::translate("MainWindow", "Saving Record", nullptr));
    mResultLabel->setText(QApplication::translate("MainWindow", mName.toLocal8Bit().data(), nullptr));
    mDebugEditor->setHtml(QApplication::translate("MainWindow",
        "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
        "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
        "p, li { white-space: pre-wrap; }\n"
        "</style></head><body style=\" font-family:'Courier New'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; "
        "text-indent:0px;\">&gt; How are you today? :)</p></body></html>", nullptr));

    return NO_ERROR;
}

QString DeviceUi::getName()
{
    return mName;
}

QSize DeviceUi::getSize()
{
    return QSize(
        GROUP_BOX_WIDTH  + 2 * GROUP_BOX_WIDTH_MARGIN,
        GROUP_BOX_HEIGHT + 2 * GROUP_BOX_HEIGHT_MARGIN);
}

}
