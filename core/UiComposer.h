#ifndef UICOMPOSER_H
#define UICOMPOSER_H

#include <list>

#include "utils/common.h"
#include "ui/MainWindowUi.h"
#include "ui/DefaultUi.h"
#include "ui/DeviceUi.h"

namespace nebula {

class UiComposer
{
public:
    int32_t onDeviceAttached(QString &name);
    int32_t onDeviceRemoved(QString &name);

public:
    UiComposer(QMainWindow *window);
    ~UiComposer();
    int32_t construct();
    int32_t destruct();

private:
    bool          mConstructed;
    QMainWindow  *mMainWindow;
    MainWindowUi *mMainWindowUi;
    DefaultUi    *mDefaultUi;
    std::list<DeviceUi *> mDeviceUi;
};

}

#endif
