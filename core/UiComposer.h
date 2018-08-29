#ifndef UICOMPOSER_H
#define UICOMPOSER_H

#include <list>
#include <functional>

#include <QObject>

#include "utils/common.h"
#include "ui/Common.h"
#include "ui/MainWindowUi.h"
#include "ui/DefaultUi.h"
#include "ui/DeviceUi.h"
#include "ui/Animation.h"
#include "ui/AnimationDrawIntf.h"
#include "ui/UpdateUiIntf.h"
#include "ui/DebugIntf.h"

namespace nebula {

class UiComposer :
    public QObject,
    public AnimationDrawIntf,
    public UpdateUiIntf,
    public DebugIntf
{
    Q_OBJECT

public:
    int32_t onDeviceAttached(QString &name);
    int32_t onDeviceRemoved(QString &name);
    int32_t drawAnimation(QString name, int32_t frameId) override;
    int32_t updateUiResult(QString name, DeviceUiType type, bool result) override;
    void debug(QString text, QString name) override;

public:
    explicit UiComposer(QMainWindow *window);
    virtual ~UiComposer();
    int32_t construct();
    int32_t destruct();

signals:
    int32_t drawUi(std::function<int32_t ()> func);
    int32_t drawAnimationFrame(QString name, int32_t frameId);
    int32_t updateUi(DeviceUi *ui, DeviceUiType type, bool result);
    void showDebug(DeviceUi *ui, QString text);
    void quit();

private slots:
    int32_t onDrawUi(std::function<int32_t ()> func);
    int32_t onDrawAnimationFrame(QString name, int32_t frameId);
    int32_t onUpdateUi(DeviceUi *ui, DeviceUiType type, bool result);
    int32_t onShowDebug(DeviceUi *ui, QString text);

private:
    bool          mConstructed;
    QMainWindow  *mMainWindow;
    QWidget      *mBaseWidget;
    MainWindowUi *mMainWindowUi;
    DefaultUi    *mDefaultUi;
    std::list<DeviceUi *> mDeviceUi;
    std::list<Animation *> mAnimation;
};

}

#endif
