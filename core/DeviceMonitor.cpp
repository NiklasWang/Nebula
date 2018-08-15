#include <QMessageBox>

#include "utils/common.h"
#include "utils/TimeEx.h"
#include "DeviceMonitor.h"

namespace nebula {

DeviceMonitor::DeviceMonitor(UiComposer *ui, QWidget *widget) :
    mExit(false),
    mUi(ui),
    mWidget(widget)
{
}

DeviceMonitor::~DeviceMonitor()
{
    if (isRunning()) {
        int32_t rc = exitMonitor();
        if (!SUCCEED(rc)) {
            QMessageBox::warning(mWidget, NULL,
                "Failed to exit device monitor.");
        }
    }
}

void DeviceMonitor::run()
{
    doTaskLoop();
}

int32_t DeviceMonitor::startMonitor()
{
    int32_t rc = NO_ERROR;

    if (!isRunning()) {
        start();
    } else {
        QMessageBox::warning(mWidget, NULL,
            "Device monitor already started.");
    }

    return rc;
}

int32_t DeviceMonitor::exitMonitor()
{
    mExit = true;
    mExitSem.wait();

    return NO_ERROR;
}

int32_t DeviceMonitor::doTaskLoop()
{
    int32_t final = NO_ERROR;

    do {
        int32_t rc = doTask();
        if (!SUCCEED(rc)) {
            QMessageBox::warning(mWidget, NULL,
                "Failed to do task in thread loop.");
            final |= rc;
        }

        delayMs(500);
    } while (!mExit);

    mExitSem.signal();

    return final;
}

int32_t DeviceMonitor::doTask()
{
    int32_t rc = NO_ERROR;

    delayMs(1000);

    return rc;
}

}
