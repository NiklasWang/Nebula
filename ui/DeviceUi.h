#ifndef DEVICEUI_H
#define DEVICEUI_H

#include <QtWidgets/QMainWindow>

namespace nebula {

class DeviceUi
{
public:
    int32_t setupUi();
    int32_t retranslateUi();
    QString getName();
    QSize getSize();

public:
    DeviceUi(QMainWindow *window, QString &name, int32_t id);
    ~DeviceUi();

private:
    QMainWindow *mMainWindow;
    int32_t      mId;
    QString      mName;
};

}

#endif // DEVICEUI_H
