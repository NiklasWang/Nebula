#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

namespace nebula {

class MainWindowUi
{
public:
    int32_t setupUi();
    int32_t retranslateUi();
    int32_t resize(QSize &size);
    QSize getSize();

public:
    MainWindowUi(QMainWindow *window);
    ~MainWindowUi();

private:
    QMainWindow *mMainWindow;
    QAction     *mActionExit;
    QAction     *mActionAbout;
    QMenuBar    *mMenuBar;
    QMenu       *mMenuFile;
    QMenu       *mMenuHelp;
    QStatusBar  *mStatusBar;
};

}

#endif
