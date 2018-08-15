#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "core/UiComposer.h"
#include "core/DeviceMonitor.h"

namespace nebula {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int32_t construct();
    int32_t destruct();

private:
    bool mConstructed;
    UiComposer    *mUi;
    DeviceMonitor *mMonitor;
};

}

#endif
