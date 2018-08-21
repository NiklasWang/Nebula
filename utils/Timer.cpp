#include "core/common.h"
#include "utils/common.h"
#include "utils/Time.h"
#include "utils/Timer.h"

namespace nebula {

Timer::Timer(QString name) :
    mName(name),
    mExit(false),
    mSem(nullptr),
    mMs(0)
{
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
    mSem->signal();

    return NO_ERROR;
}

void Timer::run()
{
    int32_t rc = NO_ERROR;

    if (!mExit) {
        if (mMs != 0) {
            rc = mSem->wait();
        }
    }

    if (!SUCCEED(rc)) {
        mFunc();
    }
}

}
