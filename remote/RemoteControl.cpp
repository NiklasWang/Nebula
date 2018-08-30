#include <QFile>
#include <QDir>
#include <QProcess>

#include "utils/common.h"
#include "utils/Time.h"
#include "core/Common.h"
#include "algorithm/Config.h"
#include "remote/config.h"
#include "remote/RemoteControl.h"

namespace nebula {

void RemoteControl::run()
{
    int32_t rc = NO_ERROR;
    QProcess *process;

    if (SUCCEED(rc)) {
        QDir path(SCRIPT_PATH);
        QFile script(path.absolutePath());
        if (!script.exists()) {
            showError("Script not exists, " +
                path.absolutePath());
            rc = NOT_EXIST;
        }
    }

    if (SUCCEED(rc)) {
        process = new QProcess();
        if (ISNULL(process)) {
            showError("Failed to create process.");
            rc = NO_MEMORY;
        }
    }

    if (SUCCEED(rc)) {
        QString script = SCRIPT_PATH;
        QStringList args;
        args << mName << "2" << mPath;
        process->start(script, args);
    }

    if (SUCCEED(rc)) {
        process->waitForReadyRead();
        process->waitForFinished();
        QString result = process->readAll();
        QStringList lines = result.split("\r\n");
        for (int32_t i = 0; i < SCRIPT_LINE_COUNT_FOR_MARK &&
             i < lines.size(); i++) {
            QString curLine = *(lines.end() - i - 1);
            if (curLine.contains(SCRIPT_LAST_LINE_SUCCEED_MARK,
                Qt::CaseInsensitive)) {
                mResult = true;
                break;
            }
        }
    }

    if (SUCCEED(rc)) {
        rc = checkRules();
        if (!SUCCEED(rc)) {
            showError("Failed to check rules on remote device");
        }
    }

    if (SUCCEED(rc) || !SUCCEED(rc)) {
        if (NOTNULL(mCbFunc)) {
            mCbFunc();
        }
    }

    if (SUCCEED(rc) || !SUCCEED(rc)) {
        mExitSem.signal();
    }

    return;
}

int32_t RemoteControl::checkRules()
{
    int32_t rc = NO_ERROR;
    int32_t count = 0;
    QFileInfoList list;

    if (SUCCEED(rc)) {
        QDir dir(mPath);
        dir.setFilter(QDir::Files | QDir::Hidden |
                      QDir::NoSymLinks | QDir::AllDirs);
        dir.setSorting(QDir::Size | QDir::Reversed);

        list = dir.entryInfoList();
        if (list.size() != DIR_FILE_NUM + DIR_DEFAULT_NUM) {
            rc = TEST_FAILED;
        }
    }

    if (SUCCEED(rc)) {
        for (auto iter : list) {
            QString name = iter.fileName();
            if (name.contains(
                MAIN_CAM_PIC_PREFIX, Qt::CaseSensitive)) {
                count++;
            } else if (name.contains(
                SUB_CAM_PIC_PREFIX, Qt::CaseSensitive)) {
                count++;
            }  else if (name.contains(
                OTP_DUAL_CAM_CALIB, Qt::CaseSensitive)) {
                count++;
            }
        }
    }

    if (SUCCEED(rc)) {
        if (count != DIR_FILE_NUM) {
            rc  = TEST_FAILED;
        }
    }

    return rc;
}

int32_t RemoteControl::startController()
{
    int32_t rc = NO_ERROR;

    if (!isRunning()) {
        start();
    } else {
        showError("Device controller already started.");
    }

    return rc;
}

int32_t RemoteControl::exitController()
{
    int32_t rc = NO_ERROR;

    mExit = true;
    mExitSem.wait();

    if (!mResult) {
        rc = TEST_FAILED;
    }

    return rc;
}

int32_t RemoteControl::setCb(std::function<int32_t ()> func)
{
    mCbFunc = func;
    return NO_ERROR;
}

RemoteControl::RemoteControl(QString path, QString name) :
    mExit(false),
    mPath(path),
    mName(name),
    mResult(false)
{
}

RemoteControl::~RemoteControl()
{
    if (isRunning()) {
        int32_t rc = exitController();
        if (!SUCCEED(rc)) {
            showError("Failed to exit device controller.");
        }
    }
    quit();
    wait();
}

}
