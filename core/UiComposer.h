#ifndef UICOMPOSER_H
#define UICOMPOSER_H

#include <list>
#include <functional>

#include <QObject>

#include "utils/common.h"
#include "ui/MainWindowUi.h"
#include "ui/DefaultUi.h"
#include "ui/DeviceUi.h"

namespace nebula {

class UiComposer :
    public QObject
{
    Q_OBJECT

public:
    int32_t onDeviceAttached(QString &name);
    int32_t onDeviceRemoved(QString &name);

public:
    explicit UiComposer(QMainWindow *window);
    ~UiComposer();
    int32_t construct();
    int32_t destruct();

private:
    struct DrawUiFunc {
        std::function<int32_t ()> mFunc;
        DrawUiFunc(std::function<int32_t ()> func);
        DrawUiFunc();
        int32_t operator()();
    };

signals:
    int32_t drawUi(DrawUiFunc func);

private slots:
    int32_t onDrawUi(DrawUiFunc func);

private:
    bool          mConstructed;
    QMainWindow  *mMainWindow;
    MainWindowUi *mMainWindowUi;
    DefaultUi    *mDefaultUi;
    std::list<DeviceUi *> mDeviceUi;
};

}

#endif
