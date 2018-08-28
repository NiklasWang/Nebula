#ifndef DEVICEUI_H
#define DEVICEUI_H

#include <QObject>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

#include "ui/Common.h"
#include "ui/AnimationDrawIntf.h"
#include "ui/Animation.h"

namespace nebula {

class DeviceUi :
    public QObject
{
    Q_OBJECT

public:
    int32_t setupUi();
    int32_t removeUi();
    int32_t update(DeviceUiType type, bool result);
    int32_t debug(QString &str);
    int32_t drawAnimation(int32_t frameId);

    QString getName();
    QSize getSize();

public:
    explicit DeviceUi(QWidget *parent, QString &name, int32_t id);
    virtual ~DeviceUi();

private:
    int32_t retranslateUi();

private:
    bool    mConstructed;
    int32_t mId;
    QString mName;
    int32_t mStep;

private:
    QWidget     *mParent;
    static int32_t kCount;
    static QWidget     *kHorizontalLayoutWidget;
    static QHBoxLayout *kHorizontalLayout;
    static int32_t kPictureOpacityRange[];
    static int32_t kTextOpacityRange[];

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

#endif
