#include "QMessageBox"

#include "utils/common.h"
#include "core/common.h"
#include "core/MainWindow.h"

namespace nebula {

QMainWindow *gMW = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mConstructed(false),
    mUi(nullptr),
    mMonitor(nullptr)
{
    gMW = this;
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
            QMessageBox::critical(this, NULL,
                "Failed to create ui composer.");
        }
    }

    if (SUCCEED(rc)) {
        rc = mUi->construct();
        if (rc != NO_ERROR) {
            QMessageBox::warning(this, NULL,
                "Failed to construct composer, "
                + rc);
        }
    }

    if (SUCCEED(rc)) {
        mMonitor = new DeviceMonitor(mUi);
        if (ISNULL(mMonitor)) {
            QMessageBox::critical(this, NULL,
                "Failed to create ui composer.");
        }
    }

    if (SUCCEED(rc)) {
        rc = mMonitor->startMonitor();
        if (rc != NO_ERROR) {
            QMessageBox::warning(this, NULL,
                "Failed to start monitor, "
                + rc);
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
            QMessageBox::warning(this, NULL,
                "Failed to destruct ui composer, "
                + rc);
        }
        SECURE_DELETE(mUi);
    }

    if (SUCCEED(rc)) {
        rc = mMonitor->exitMonitor();
        if (!SUCCEED(rc)) {
            QMessageBox::warning(this, NULL,
                "Failed to stop monitor, " + rc);
        }
        SECURE_DELETE(mMonitor);
    }

    return rc;
}

}
