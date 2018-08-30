#include <QDir>

#include "utils/common.h"
#include "core/Common.h"
#include "algorithm/Config.h"
#include "remote/config.h"
#include "core/DeviceControl.h"
#include "algorithm/Algorithm.h"

namespace nebula {

int32_t DeviceControl::doTask()
{
    int32_t rc = NO_ERROR;
    int32_t result = TEST_FAILED;
    Semaphore sem;

    if (SUCCEED(rc)) {
        rc = mUi->updateUiResult(mName, DEVICE_UI_TYPE_1, true);
        if (!SUCCEED(rc)) {
            showError("Failed to update ui, 1");
        }
    }

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
        rc = mCtl->startController();
        if (!SUCCEED(rc)) {
            showError("Failed to start remote controller");
        }
    }

    if (SUCCEED(rc)) {
        sem.wait();
        rc = mCtl->exitController();
        int32_t _rc = mUi->updateUiResult(
            mName, DEVICE_UI_TYPE_2, SUCCEED(rc));
        if (!SUCCEED(_rc)) {
            mDebug->debug(mName, "Remote control FAILED.");
            showError("Failed to update ui, 2");
            rc |= _rc;
        } else {
            mDebug->debug(mName, "Remote control succeed.");
        }
        SECURE_DELETE(mCtl);
    }

    if (SUCCEED(rc)) {
        mAlg = new Algorithm(mPath, mName);
        if (ISNULL(mAlg)) {
            showError("Failed to create algorithm");
            rc = NO_MEMORY;
        }
    }

    if (SUCCEED(rc)) {
        int32_t rc = mAlg->init();
        if (!SUCCEED(rc)) {
            mDebug->debug(mName, "Rules checking FAILED.");
        }
    }

    if (SUCCEED(rc)) {
        result = mAlg->process();
        rc = mUi->updateUiResult(mName,
            DEVICE_UI_TYPE_3, SUCCEED(result));
        if (!SUCCEED(rc)) {
            showError("Failed to update ui, 3");
        }
        if (!SUCCEED(result)) {
            mDebug->debug(mName, mAlg->query());
            mDebug->debug(mName, "Run calibration FAILED.");
        } else {
            mDebug->debug(mName, mAlg->query());
            mDebug->debug(mName, "Run calibration succeed.");
        }
    }

    if (SUCCEED(rc)) {
        rc = mAlg->deinit();
        if (!SUCCEED(rc)) {
            mDebug->debug(mName, "Destruct algorithm FAILED.");
        }
        SECURE_DELETE(mAlg);
    }

    if (SUCCEED(rc) || !SUCCEED(rc)) {
        rc = mUi->updateUiResult(mName, DEVICE_UI_TYPE_4, true);
        if (!SUCCEED(rc)) {
            showError("Failed to update ui, 4");
        }
    }

    if (SUCCEED(rc) || !SUCCEED(rc)) {
        rc = mUi->updateUiResult(mName,
            DEVICE_UI_TYPE_RESULT, SUCCEED(result));
        if (!SUCCEED(rc)) {
            showError("Failed to update ui, result");
        }
        if (!SUCCEED(result)) {
            mDebug->debug(mName, "Total result: FAILED.");
        } else {
            mDebug->debug(mName, "Total result: SUCCEED.");
        }
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

DeviceControl::DeviceControl(QString &name,
    UpdateUiIntf *ui, DebugIntf *debug) :
    mExit(false),
    mName(name),
    mUi(ui),
    mDebug(debug),
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
    mPath.append("/");
    mPath.append(DATA_PATH_BASE);

    QDir dir1(mPath);
    if (!dir1.exists()) {
        dir1.mkdir(mPath);
    }

    mPath.append("/");
    mPath.append(mName);

    QDir dir(mPath);
    if (dir.exists()) {
        dir.rmdir(mPath);
    }
    if (!dir.exists()) {
        dir.mkdir(mPath);
    }

    mPath = dir.toNativeSeparators(mPath);
}

}
