#include "QMessageBox"

#include "utils/common.h"
#include "MainWindow.h"

namespace nebula {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mUi(nullptr)
{
    int32_t rc = NO_ERROR;

    mUi = new nebula::UiComposer(this);
    if (ISNULL(mUi)) {
        QMessageBox::critical(this, NULL,
            "Failed to create ui composer.");
    }

    if (SUCCEED(rc)) {
        rc = mUi->construct();
        if (rc != NO_ERROR) {
            QMessageBox::warning(this, NULL,
                "Failed to construct composer, "
                + rc);
        }
    }
}

MainWindow::~MainWindow()
{
    int32_t rc = mUi->destruct();
    if (rc != NO_ERROR) {
        QMessageBox::warning(this, NULL,
            "Failed to destruct composer, "
            + rc);
    }
    SECURE_DELETE(mUi);
}

}
