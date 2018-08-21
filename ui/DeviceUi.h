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

#include "ui/AnimationDrawIntf.h"
#include "ui/Animation.h"

namespace nebula {

enum DeviceUiType {
    DEVICE_UI_TYPE_1,
    DEVICE_UI_TYPE_2,
    DEVICE_UI_TYPE_3,
    DEVICE_UI_TYPE_4,
    DEVICE_UI_TYPE_RESULT,
    DEVICE_UI_TYPE_MAX_INVALID,
};

class DeviceUi :
    public QObject,
    public AnimationDrawIntf
{
    Q_OBJECT

public:
    int32_t setupUi();
    int32_t removeUi();
    int32_t update(DeviceUiType type, bool result);
    int32_t debug(QString &str);
    int32_t retranslateUi();

    QString getName();
    QSize getSize();

public:
    explicit DeviceUi(QWidget *parent, QString &name, int32_t id);
    virtual ~DeviceUi();

protected:
    int32_t drawAnimation(int32_t frameId) override;
    int32_t drawAnimationUi(int32_t frameId);

signals:
    int32_t drawUi(std::function<int32_t (int32_t)> func, int32_t id);

private slots:
    int32_t onDrawUi(std::function<int32_t (int32_t)> func, int32_t id);

private:
    bool    mConstructed;
    int32_t mId;
    QString mName;
    int32_t mStep;
    Animation mAnimation;

private:
    QWidget     *mParent;
    static int32_t kCount;
    static QWidget     *kHorizontalLayoutWidget;
    static QHBoxLayout *kHorizontalLayout;
    static int32_t kOpacityRange[];

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
