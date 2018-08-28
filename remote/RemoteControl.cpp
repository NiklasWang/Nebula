#include <QFile>
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
        QFile script(SCRIPT_PATH);
        if (!script.exists()) {
            showError(QString("Script not "
                "exists, ") + SCRIPT_PATH);
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
        args << mName << mPath;
        process->start(script, args);
    }

    if (SUCCEED(rc)) {
        process->waitForReadyRead();
        process->waitForFinished();
        QString result = process->readAll();
        QStringList lines = result.split("\n");
        QString lastLine = lines.at(lines.size() - 1);
        if (!lastLine.contains(SCRIPT_LAST_LINE_SUCCEED_MARK),
            Qt::CaseInsensitive) {
            showError("Script running failed, no succeed mark found.");
            rc = TEST_FAILED;
        }
    }

    if (SUCCEED(rc)) {
        if (NOTNULL(mCbFunc)) {
            mCbFunc();
        }
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

    return NO_ERROR;
}

int32_t RemoteControl::setCb(std::function<int32_t ()> func)
{
    mCbFunc = func;
    return NO_ERROR;
}

RemoteControl::RemoteControl(QString path, QString name) :
    mExit(false),
    mPath(path),
    mName(name)
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
