#ifndef DEVICEUI_H
#define DEVICEUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

namespace nebula {

class DeviceUi
{
public:
    int32_t setupUi();
    int32_t retranslateUi();
    QString getName();
    QSize getSize();

public:
    explicit DeviceUi(QWidget *parent, QString &name, int32_t id);
    ~DeviceUi();

private:
    int32_t mId;
    QString mName;

private:
    QWidget     *mParent;
    static int32_t kCount;
    static QWidget     *kHorizontalLayoutWidget;
    static QHBoxLayout *kHorizontalLayout;

private:
    QGroupBox   *mGroupBox;
    QWidget     *mGridLayoutWidget;
    QGridLayout *mGridLayout;
    QLabel      *mPicture0;
    QLabel      *mText0;
    QLabel      *mPicture1;
    QLabel      *mText1;
    QLabel      *mPicture2;
    QLabel      *mText2;
    QLabel      *mPicture3;
    QLabel      *mText3;
    QLabel      *mResult;
    QTextEdit   *mDebugEditor;
};

}

#endif // DEVICEUI_H
