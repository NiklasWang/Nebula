#ifndef DEVICEMONITOR_H
#define DEVICEMONITOR_H

#include <QThread>
#include <QWidget>

#include "utils/common.h"
#include "utils/Semaphore.h"
#include "core/UiComposer.h"

namespace nebula {

class DeviceMonitor :
    public QThread
{
public:
    int32_t startMonitor();
    int32_t exitMonitor();

public:
    explicit DeviceMonitor(UiComposer *ui, QWidget *widget);
    ~DeviceMonitor();

private:
    int32_t doTask();
    int32_t doTaskLoop();

protected:
    void run() override;

private:
    bool        mExit;
    Semaphore   mExitSem;
    UiComposer *mUi;
    QWidget    *mWidget;
};

}

#endif
