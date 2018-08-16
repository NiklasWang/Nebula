#ifndef DEVICEMONITOR_H
#define DEVICEMONITOR_H

#include <QThread>

#include "utils/common.h"
#include "utils/Semaphore.h"
#include "core/UiComposer.h"
#include "core/DeviceControl.h"

namespace nebula {

class DeviceMonitor :
    public QThread
{
public:
    int32_t startMonitor();
    int32_t exitMonitor();

public:
    explicit DeviceMonitor(UiComposer *ui);
    ~DeviceMonitor();

private:
    int32_t doTask();
    int32_t doTaskLoop();
    int32_t checkDevices(QString &output);
    int32_t addDevice(QString &name);
    int32_t removeDevice(QString &name);

protected:
    void run() override;

private:
    bool        mExit;
    Semaphore   mExitSem;
    int32_t     mLoopCnt;
    UiComposer *mUi;
    std::list<DeviceControl *> mDevices;
};

}

#endif
