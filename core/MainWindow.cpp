#include <QMessageBox>

#include "utils/common.h"
#include "core/Common.h"
#include "core/MainWindow.h"

namespace nebula {

MainWindow *gMW = nullptr;

MainWindow::MainWindow(QApplication *app, QWidget *parent) :
    QMainWindow(parent),
    mConstructed(false),
    mApp(app),
    mParent(parent),
    mUi(nullptr),
    mMonitor(nullptr)
{
    gMW = this;

    connect(this, SIGNAL(showDialogSignal(MessageType, const QString)),
            this, SLOT(onDialogShow(MessageType, const QString)));
}

MainWindow::~MainWindow()
{
    if (mConstructed) {
        destruct();
    }
}

int32_t MainWindow::construct()
{
    int32_t rc = NO_ERROR;

    if (mConstructed) {
        rc = ALREADY_INITED;
    }

    if (SUCCEED(rc)) {
        mUi = new UiComposer(this);
        if (ISNULL(mUi)) {
            showError("Failed to create ui composer.");
        }
    }

    if (SUCCEED(rc)) {
        rc = mUi->construct();
        if (rc != NO_ERROR) {
            showError("Failed to construct composer, " + rc);
        }
    }

    if (SUCCEED(rc)) {
        mMonitor = new DeviceMonitor(mUi);
        if (ISNULL(mMonitor)) {
            showError("Failed to create ui composer.");
        } else {
            connect(this,     SIGNAL(newPathSelected(QString)),
                    mMonitor, SLOT(onNewPathSelected(QString)));
        }
    }

    if (SUCCEED(rc)) {
        rc = mMonitor->startMonitor();
        if (rc != NO_ERROR) {
            showError("Failed to start monitor, " + rc);
        }
    }

    if (SUCCEED(rc)) {
        mConstructed = true;
    }

    return rc;
}

int32_t MainWindow::destruct()
{
    int32_t rc = NO_ERROR;

    if (!mConstructed) {
        rc = NOT_INITED;
    } else {
        mConstructed = false;
    }

    if (SUCCEED(rc)) {
        rc = mUi->destruct();
        if (rc != NO_ERROR) {
            showError("Failed to destruct ui composer, " + rc);
        }
        SECURE_DELETE(mUi);
    }

    if (SUCCEED(rc)) {
        rc = mMonitor->exitMonitor();
        if (!SUCCEED(rc)) {
            showError("Failed to stop monitor, " + rc);
        }
        SECURE_DELETE(mMonitor);
    }

    return rc;
}

int32_t MainWindow::showDialog(MessageType type, const QString &msg)
{
    return showDialogSignal(type, msg);
}

int32_t MainWindow::onDialogShow(MessageType type, const QString msg)
{
    QMessageBox::StandardButton btn =
        QMessageBox::StandardButton::NoButton;

    switch (type) {
        case MESSAGE_TYPE_INFORMATION: {
            btn = QMessageBox::information(this, nullptr, msg);
        }; break;
        case MESSAGE_TYPE_QUESTION: {
            btn = QMessageBox::question(this, nullptr, msg);
        }; break;
        case MESSAGE_TYPE_WARNING: {
            btn = QMessageBox::warning(this, nullptr, msg);
        }; break;
        case MESSAGE_TYPE_ERROR: {
            btn = QMessageBox::warning(this, nullptr, msg);
        }; break;
        case MESSAGE_TYPE_CRITICAL: {
            btn = QMessageBox::critical(this, nullptr, msg);
        }; break;
        case MESSAGE_TYPE_MAX_INVALID:
        default: {
            btn = QMessageBox::critical(this, nullptr, msg);
        }; break;
    }

    return btn;
}

QString MainWindow::getPath()
{
    QString result = "";

    if (NOTNULL(mApp)) {
        result = mApp->applicationDirPath();
    }

    return result;
}

}
