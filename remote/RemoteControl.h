#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <functional>

#include <QString>
#include <QThread>

#include "utils/Semaphore.h"

namespace nebula {

class RemoteControl :
    public QThread
{
public:
    int32_t startController();
    int32_t exitController();
    int32_t setCb(std::function<int32_t ()> func);

public:
    explicit RemoteControl(QString path, QString name);
    virtual ~RemoteControl();

protected:
    void run() override;

private:
    bool      mExit;
    Semaphore mExitSem;
    QString   mPath;
    QString   mName;
    bool      mResult;
    std::function<int32_t ()> mCbFunc;
};

}

#endif
