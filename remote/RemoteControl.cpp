#include <QFile>
#include <QDir>
#include <QProcess>

#include "utils/common.h"
#include "core/Common.h"
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
        if (NOTNULL(mCbFunc)) {
            mCbFunc();
        }
    }

    if (SUCCEED(rc) || !SUCCEED(rc)) {
        mExitSem.signal();
    }

    return;
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
    mExit = true;
    mExitSem.wait();

    return mResult ? NO_ERROR : TEST_FAILED;
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
