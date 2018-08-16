#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "core/UiComposer.h"
#include "core/common.h"
#include "core/DeviceMonitor.h"

namespace nebula {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int32_t showDialog(MessageType type, const QString &msg);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int32_t construct();
    int32_t destruct();

signals:
    int32_t showDialogSignal(MessageType type, const QString msg);

private slots:
    int32_t onDialogShow(MessageType type, const QString msg);

private:
    bool mConstructed;
    UiComposer    *mUi;
    DeviceMonitor *mMonitor;
};

}

#endif
