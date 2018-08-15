#include "utils/common.h"
#include "DeviceUi.h"
#include "ui/UiLayout.h"

namespace nebula {

DeviceUi::DeviceUi(QMainWindow *window, QString &name, int32_t id) :
    mMainWindow(window),
    mId(id),
    mName(name)
{}

DeviceUi::~DeviceUi()
{
}

int32_t DeviceUi::setupUi()
{
    return retranslateUi();
}

int32_t DeviceUi::retranslateUi()
{
    return NO_ERROR;
}

QString DeviceUi::getName()
{
    return mName;
}

QSize DeviceUi::getSize()
{
    return QSize(500, 900);
}

}
