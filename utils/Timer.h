#ifndef TIMER_H
#define TIMER_H

#include <functional>
#include <QThread>
#include <QString>

#include "utils/Time.h"
#include "utils/SemaphoreTimeout.h"

namespace nebula {

class Timer :
    public QThread
{
public:
    int32_t startNow(Ms ms, std::function<int32_t ()> func);
    int32_t startNow(Sec sec, std::function<int32_t ()> func);
    int32_t stopNow();

public:
    Timer(QString name = "default");

protected:
    void run() override;

private:
    QString mName;
    bool    mExit;
    SemaphoreTimeout *mSem;
    Ms      mMs;
    std::function<int32_t ()> mFunc;
};

}

#endif
