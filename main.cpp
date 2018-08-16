#include <QApplication>

#include "utils/common.h"
#include "core/common.h"
#include "core/MainWindow.h"

int main(int argc, char *argv[])
{
    int32_t rc = NO_ERROR;
    QApplication a(argc, argv);
    nebula::MainWindow w;

    rc = w.construct();
    if (SUCCEED(rc)) {
        w.show();
        rc = a.exec();
    } else {
        nebula::showError("Failed to construct main window, " + rc);
    }

    return rc;
}
