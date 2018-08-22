#include <QDateTime>
#include <QDebug>

#include "core/common.h"
#include "utils/common.h"
#include "utils/Time.h"
#include "utils/Timer.h"

#define DEBUG_MODE_ON 1

namespace nebula {

Timer::Timer(QString name) :
    mName(name),
    mExit(false),
    mDebug(!!(DEBUG_MODE_ON)),
    mSem(nullptr),
    mMs(0)
{
}

Timer::~Timer()
{
    stopNow();
    quit();
    wait();
}

int32_t Timer::startNow(Ms ms, std::function<int32_t ()> func)
{
    int32_t rc = NO_ERROR;

    if (SUCCEED(rc)) {
        if (ms() <= 0) {
            showError("Invalid ms" + ms());
            rc = PARAM_INVALID;
        }
    }

    if (SUCCEED(rc)) {
        mMs = ms;
        mFunc = func;
        mSem = new SemaphoreTimeout(ms());
        if (ISNULL(mSem)) {
            showError("Failed to create semaphore timed.");
            rc = NO_MEMORY;
        }
    }

    if (SUCCEED(rc)) {
        if (!isRunning()) {
            start();
        } else {
            showError("Timer " + mName + " already started.");
        }
    }

    return NO_ERROR;
}

int32_t Timer::startNow(Sec sec, std::function<int32_t ()> func)
{
    return startNow(Ms(sec() * 1000), func);
}

int32_t Timer::stopNow()
{
    mExit = true;
    if (NOTNULL(mSem)) {
        mSem->signal();
    }

    return NO_ERROR;
}

void Timer::run()
{
    int32_t rc = NO_ERROR;

    if (!mExit) {
        if (mMs != 0 && NOTNULL(mSem)) {
            if (mDebug) {
                QDateTime dataTime = QDateTime::currentDateTime();
                QString time = dataTime.toString("hh:mm:ss.zzz");
                qDebug() << "Timer debug, start wait for "
                          << mMs() << "ms, "
                          << "current time is " << time;
            }
            delayMs(30);
            rc = mSem->wait();
            if (mDebug) {
                QDateTime dataTime = QDateTime::currentDateTime();
                QString time = dataTime.toString("hh:mm:ss.zzz");
                qDebug() << "Timer debug, finished wait for "
                          << mMs() << "ms, " << rc << ", "
                          << "current time is " << time;
            }
        }
    }

    if (!SUCCEED(rc)) {
        SECURE_DELETE(mSem);
        mSem = nullptr;
        mFunc();
    }
}

}
