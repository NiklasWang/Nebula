#include "utils/common.h"
#include "DeviceUi.h"
#include "ui/UiLayout.h"

namespace nebula {

DeviceUi::DeviceUi(QMainWindow *window, QString &name, int32_t id) :
    mId(id),
    mName(name),
    mMainWindow(window),
    mCentralWidget(nullptr),
    mGroupBox(nullptr),
    mGridLayoutWidget(nullptr),
    mGridLayout(nullptr),
    mPictureLabel0(nullptr),
    mTextLabel0(nullptr),
    mPictureLabel1(nullptr),
    mTextLabel1(nullptr),
    mPictureLabel2(nullptr),
    mTextLabel2(nullptr),
    mPictureLabel3(nullptr),
    mTextLabel3(nullptr),
    mResultLabel(nullptr),
    mDebugEditor(nullptr)
{
}

DeviceUi::~DeviceUi()
{
    SECURE_DELETE(mDebugEditor);
    SECURE_DELETE(mResultLabel);
    SECURE_DELETE(mPictureLabel3);
    SECURE_DELETE(mTextLabel3);
    SECURE_DELETE(mPictureLabel2);
    SECURE_DELETE(mTextLabel2);
    SECURE_DELETE(mPictureLabel1);
    SECURE_DELETE(mTextLabel1);
    SECURE_DELETE(mPictureLabel0);
    SECURE_DELETE(mTextLabel0);
    SECURE_DELETE(mGridLayout);
    SECURE_DELETE(mGridLayoutWidget);
    SECURE_DELETE(mGroupBox);
    SECURE_DELETE(mCentralWidget);
}

int32_t DeviceUi::setupUi()
{
    int32_t rc = NO_ERROR;
    QFont fontNormal, fontTextLabel;

    if (SUCCEED(rc)) {
        mCentralWidget = new QWidget(mMainWindow);
        mCentralWidget->setObjectName(QStringLiteral("centralWidget"));
        mGroupBox = new QGroupBox(mCentralWidget);
        mGroupBox->setObjectName(QStringLiteral("mGroupBox"));
        mGroupBox->setEnabled(true);
        mGroupBox->setGeometry(QRect(10, 10, 500, 850));
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

    if (SUCCEED(rc)) {
        rc = retranslateUi();
        QMetaObject::connectSlotsByName(mMainWindow);
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
    mResultLabel->setText(QApplication::translate("MainWindow", "......", nullptr));
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
    return QSize(500, 900);
}

}
