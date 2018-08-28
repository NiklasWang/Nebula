#ifndef UPDATEUIINTF_H
#define UPDATEUIINTF_H

#include <stdint.h>

#include <QString>

#include "ui/Common.h"

namespace nebula {

class UpdateUiIntf
{
public:
    virtual int32_t updateUiResult(QString name, DeviceUiType type, bool result) = 0;

public:
    virtual ~UpdateUiIntf() {}
};

}

#endif
