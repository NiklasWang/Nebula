#include "utils/common.h"
#include "core/common.h"
#include "DeviceControl.h"
#include "algorithm/Algorithm.h"

namespace nebula {

int32_t DeviceControl::doTask()
{
    int32_t rc = NO_ERROR;
    Semaphore sem;

    if (SUCCEED(rc)) {
        mCtl = new RemoteControl(mPath, mName);
        if (ISNULL(mCtl)) {
            showError("Failed to create remote controller");
            rc = NO_MEMORY;
        }
    }

    if (SUCCEED(rc)) {
        rc = mCtl->setCb(
            [&sem]() -> int32_t {
                sem.signal();
                return NO_ERROR;
            }
        );
        if (!SUCCEED(rc)) {
            showError("Failed to set remote controller cb");
        }
    }

    if (SUCCEED(rc)) {
        sem.wait();
        rc = mCtl->exitController();
        if (!SUCCEED(rc)) {
            showError("Failed to exit remote controller");
        } else {
            SECURE_DELETE(mCtl);
        }
    }

    if (SUCCEED(rc)) {
        mAlg = new Algorithm(mPath, mName);
        if (ISNULL(mAlg)) {
            showError("Failed to create algorithm");
            rc = NO_MEMORY;
        }
    }

    if (SUCCEED(rc)) {
        rc = mAlg->init();
        if (!SUCCEED(rc)) {
            showError("Failed to init algorithm");
        }
    }

    if (SUCCEED(rc)) {
        rc = mAlg->process();
        if (!SUCCEED(rc)) {
            showError("Failed to process algorithm");
        }
    }

    if (SUCCEED(rc)) {
        rc = mAlg->deinit();
        if (!SUCCEED(rc)) {
            showError("Failed to deinit algorithm");
        }
    }

    if (SUCCEED(rc)) {
        SECURE_DELETE(mAlg);
    }

    return rc;
}

void DeviceControl::run()
{
    doTask();
}

QString DeviceControl::getName()
{
    return mName;
}

DeviceControl::DeviceControl(QString &name) :
    mExit(false),
    mName(name),
    mCtl(nullptr),
    mAlg(nullptr)
{
}

DeviceControl::~DeviceControl()
{
    if (isRunning()) {
        int32_t rc = stopThread();
        if (!SUCCEED(rc)) {
            showError("Failed to destruct device controller.");
        }
    }
    quit();
    wait();
}

int32_t DeviceControl::startThread()
{
    int32_t rc = NO_ERROR;

    if (!isRunning()) {
        start();
    } else {
        showError("Device controller already started.");
    }

    return rc;
}

int32_t DeviceControl::stopThread()
{
    mExit = true;
    mExitSem.wait();

    return NO_ERROR;
}

void DeviceControl::onNewPathSelected(QString path)
{
    mPath = path;
}

}
