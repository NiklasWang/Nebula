#include <QProcess>

#include "utils/common.h"
#include "utils/Times.h"
#include "core/Common.h"
#include "core/CmdPrefix.h"
#include "core/MainWindow.h"
#include "core/DeviceMonitor.h"

namespace nebula {

DeviceMonitor::DeviceMonitor(UiComposer *ui) :
    mExit(false),
    mLoopCnt(0),
    mUi(ui)
{
    mPath = gMW->getPath();
}

DeviceMonitor::~DeviceMonitor()
{
    if (isRunning()) {
        int32_t rc = exitMonitor();
        if (!SUCCEED(rc)) {
            showError("Failed to exit device monitor.");
        }
    }
    quit();
    wait();
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
        showError("Device monitor already started.");
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
        if (mLoopCnt++) {
            delayMs(CMD_ADB_DELAY_LOOP);
        }

        if (mExit) {
            break;
        }

        int32_t rc = doTask();
        if (!SUCCEED(rc)) {
            showError("Failed to do task in thread loop.");
            final |= rc;
        }
    } while (!mExit);

    mExitSem.signal();

    return final;
}

int32_t DeviceMonitor::doTask()
{
    int32_t rc = NO_ERROR;

    QProcess *process = new QProcess();
    process->start(CMD_ADB_DEVICES);
    process->waitForReadyRead(-1);
    process->waitForFinished(-1);
    QString error = process->readAllStandardError();
    QString output = process->readAllStandardOutput();

    if (error.size()) {
        qDebug() << "Device monitor executin error, " << error;
    } else {
        rc = checkDevices(output);
        if (!SUCCEED(rc)) {
            showError("Failed to check device.\n" + output);
        }
    }

    return rc;
}

int32_t DeviceMonitor::checkDevices(QString &output)
{
    int32_t rc = NO_ERROR;
    QStringList adbDevices;
    QStringList curDevices;

    if (SUCCEED(rc)) {
        for (auto device : mDevices) {
            curDevices.append(device->getName());
        }
    }

    if (SUCCEED(rc)) {
        QStringList lines = output.split("\n");
        foreach (QString line, lines) {
            if (!line.contains(ADB_DEVICE_IGNORE1, Qt::CaseSensitive) &&
                !line.contains(ADB_DEVICE_IGNORE2, Qt::CaseSensitive) &&
                !line.contains(ADB_DEVICE_PREFIX, Qt::CaseSensitive)) {
                QStringList words = line.split(
                    QRegExp("[ \t\r]"), QString::SkipEmptyParts);
                if (words.size()) {
                    adbDevices.append(words.at(0));
                }
            }
        }
    }

    if (SUCCEED(rc)) {
        foreach (QString device, curDevices) {
            if (!adbDevices.contains(device)) {
                rc = removeDevice(device);
                if (!SUCCEED(rc)) {
                    showError("Failed to remove device " + device);
                }
            }
        }
    }

    if (SUCCEED(rc)) {
        foreach (QString device, adbDevices) {
            if (!curDevices.contains(device)) {
                rc = addDevice(device);
                if (!SUCCEED(rc)) {
                    showError("Failed to add new device " + device);
                }
            }
        }
    }

    return rc;
}

int32_t DeviceMonitor::addDevice(QString &name)
{
    int32_t rc = NO_ERROR;
    DeviceControl *device = nullptr;

    if (SUCCEED(rc)) {
        device = new DeviceControl(name, mUi, mUi);
        if (ISNULL(device)) {
            showError("Failed to create device " + name);
        }
    }

    if (SUCCEED(rc)) {
        device->onNewPathSelected(mPath);
        mDevices.push_back(device);
    }

    if (SUCCEED(rc)) {
        rc = mUi->onDeviceAttached(name);
        if (!SUCCEED(rc)) {
            showError("Failed to draw device " + name + " ui.");
        }
    }

    if (SUCCEED(rc)) {
        rc = device->startThread();
        if (!SUCCEED(rc)) {
            showError("Failed to start device thread.");
        }
    }

    return rc;
}

int32_t DeviceMonitor::removeDevice(QString &name)
{
    int32_t rc = NO_ERROR;
    DeviceControl *device = nullptr;

    if (SUCCEED(rc)) {
        rc = NOT_FOUND;
        for (auto iter = mDevices.begin(); iter != mDevices.end(); iter++) {
            if ((*iter)->getName() == name) {
                device = *iter;
                iter = mDevices.erase(iter);
                rc = NO_ERROR;
                break;
            }
        }
    }

    if (SUCCEED(rc)) {
        rc = device->stopThread();
        if (!SUCCEED(rc)) {
            showError("Failed to destruct device " + name);
        }
        SECURE_DELETE(device);
    }

    if (SUCCEED(rc)) {
        rc = mUi->onDeviceRemoved(name);
        if (!SUCCEED(rc)) {
            showError("Failed to remove device " + name + " ui.");
        }
    }

    return rc;
}

void DeviceMonitor::onNewPathSelected(QString path)
{
    mPath = path;
    for (auto iter : mDevices) {
        iter->onNewPathSelected(path);
    }
}

}
