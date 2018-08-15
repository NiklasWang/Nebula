#include <QApplication>

#include "core/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    nebula::MainWindow w;
    w.show();

    return a.exec();
}
