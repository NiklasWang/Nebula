#include "utils/common.h"
#include "ui/MainWindowUi.h"
#include "ui/UiLayout.h"

namespace nebula {

MainWindowUi::MainWindowUi(QMainWindow *window) :
    mMainWindow(window),
    mActionExit(nullptr),
    mActionAbout(nullptr),
    mMenuBar(nullptr),
    mMenuFile(nullptr),
    mMenuHelp(nullptr),
    mStatusBar(nullptr)
{}

MainWindowUi::~MainWindowUi()
{
}

int32_t MainWindowUi::setupUi()
{
    int32_t rc = NO_ERROR;

    if (SUCCEED(rc)) {
        if (mMainWindow->objectName().isEmpty()) {
            mMainWindow->setObjectName(QStringLiteral("MainWindow"));
        }
        mMainWindow->resize(DEFAULT_UI_WIDTH, DEFAULT_UI_HEIGHT);
    }

    if (SUCCEED(rc)) {
        mActionExit = new QAction(mMainWindow);
        mActionExit->setObjectName(QStringLiteral("actionExit"));
        mActionAbout = new QAction(mMainWindow);
        mActionAbout->setObjectName(QStringLiteral("actionAbout"));
    }

    if (SUCCEED(rc)) {
        mMenuBar = new QMenuBar(mMainWindow);
        mMenuBar->setObjectName(QStringLiteral("menuBar"));
        mMenuBar->setGeometry(QRect(0, 0, DEFAULT_UI_WIDTH, DEFAULT_UI_MENU_HEIGHT));
        mMenuFile = new QMenu(mMenuBar);
        mMenuFile->setObjectName(QStringLiteral("menuFile"));
        mMenuHelp = new QMenu(mMenuBar);
        mMenuHelp->setObjectName(QStringLiteral("menuHelp"));
        mMainWindow->setMenuBar(mMenuBar);
    }

    if (SUCCEED(rc)) {
        mStatusBar = new QStatusBar(mMainWindow);
        mStatusBar->setObjectName(QStringLiteral("statusBar"));
        mMainWindow->setStatusBar(mStatusBar);
    }

    if (SUCCEED(rc)) {
        mMenuBar->addAction(mMenuFile->menuAction());
        mMenuBar->addAction(mMenuHelp->menuAction());
        mMenuFile->addAction(mActionExit);
        mMenuHelp->addAction(mActionAbout);
    }

    if (SUCCEED(rc)) {
        rc = retranslateUi();
        QMetaObject::connectSlotsByName(mMainWindow);
    }

    return rc;
}

int32_t MainWindowUi::retranslateUi()
{
    mMainWindow->setWindowTitle(QApplication::translate("MainWindow", PROJNAME VERSION, nullptr));

    mActionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
    mActionAbout->setText(QApplication::translate("MainWindow", "About", nullptr));

    mMenuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    mMenuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));

    return NO_ERROR;
}

int32_t MainWindowUi::resize(QSize &size)
{
    mMainWindow->resize(size.width(), size.height());

    return NO_ERROR;
}

QSize MainWindowUi::getSize()
{
    return QSize(
        mMainWindow->width(),
        mMainWindow->height());
}

}
