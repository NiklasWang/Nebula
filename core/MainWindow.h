#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>

#include "core/UiComposer.h"
#include "core/Common.h"
#include "core/DeviceMonitor.h"

namespace nebula {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int32_t showDialog(MessageType type, const QString &msg);
    QString getPath();

public:
    explicit MainWindow(QApplication *app = nullptr, QWidget *parent = nullptr);
    ~MainWindow();
    int32_t construct();
    int32_t destruct();

signals:
    int32_t showDialogSignal(MessageType type, const QString msg);
    void newPathSelected(QString path);

private slots:
    int32_t onDialogShow(MessageType type, const QString msg);

private:
    bool mConstructed;
    QApplication  *mApp;
    QWidget       *mParent;
    UiComposer    *mUi;
    DeviceMonitor *mMonitor;
};

}

#endif
