#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#include <QString>

namespace nebula {

class DeviceControl
{
public:
    QString getName();

public:
    explicit DeviceControl(QString &name);
    ~DeviceControl();
    int32_t construct();
    int32_t destruct();

private:
    QString mName;
};

}

#endif
