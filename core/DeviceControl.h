#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#include <QString>

#include "algorithm/Interface.h"
#include "remote/RemoteControl.h"
#include "ui/UpdateUiIntf.h"

namespace nebula {

class DeviceControl :
    public QThread
{
    Q_OBJECT

public:
    int32_t startThread();
    int32_t stopThread();

    QString getName();
    void onNewPathSelected(QString path);

public:
    explicit DeviceControl(QString &name, UpdateUiIntf *ui);
    ~DeviceControl();

protected:
    void run() override;

private:
    int32_t doTask();

private:
    bool      mExit;
    Semaphore mExitSem;
    QString   mName;
    QString   mPath;
    UpdateUiIntf       *mUi;
    RemoteControl      *mCtl;
    AlgorithmInterface *mAlg;
};

}

#endif
