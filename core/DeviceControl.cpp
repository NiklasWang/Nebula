#include "utils/common.h"
#include "DeviceControl.h"

namespace nebula {

QString DeviceControl::getName()
{
    return mName;
}

DeviceControl::DeviceControl(QString &name) :
    mName(name)
{
}

DeviceControl::~DeviceControl()
{
}

int32_t DeviceControl::construct()
{
    int32_t rc = NO_ERROR;

    return rc;
}

int32_t DeviceControl::destruct()
{
    int32_t rc = NO_ERROR;

    return rc;
}

}
