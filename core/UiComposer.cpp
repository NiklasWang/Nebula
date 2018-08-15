#include <QMainWindow>
#include <QMessageBox>

#include "utils/common.h"
#include "core/UiComposer.h"

namespace nebula {

UiComposer::UiComposer(QMainWindow *window) :
    mConstructed(false),
    mMainWindow(window),
    mMainWindowUi(nullptr),
    mDefaultUi(nullptr)
{
}

UiComposer::~UiComposer()
{
    if (mConstructed) {
        destruct();
    }
}

int32_t UiComposer::onDeviceAttached(QString &name)
{
    int32_t rc = NO_ERROR;
    DeviceUi *ui = nullptr;
    bool removeDefaultUi = false;
    QSize windowSize;
    QSize deviceSize;

    if (SUCCEED(rc)) {
        if (!mDeviceUi.size()) {
            removeDefaultUi = true;
            QSize size = mDefaultUi->getSize();
            SECURE_DELETE(mDefaultUi);
            mMainWindow->resize(size);
        }
    }

    if (SUCCEED(rc)) {
        for (auto &device : mDeviceUi) {
            if (device->getName() == name) {
                QMessageBox::warning(mMainWindow, NULL,
                    "Device UI already exists.");
                rc = ALREADY_EXISTS;
            }
        }
    }

    if (SUCCEED(rc)) {
        DeviceUi *ui = new DeviceUi(
            mMainWindow, name, mDeviceUi.size() - 1);
        if (ISNULL(ui)) {
            QMessageBox::warning(mMainWindow, NULL,
                "Failed to create device ui.");
        }
    }

    if (SUCCEED(rc)) {
        deviceSize = ui->getSize();
        int32_t width = 0;
        int32_t height = 0;
        if (removeDefaultUi) {
            width = deviceSize.width();
            height = deviceSize.height();
        } else {
            width = mMainWindow->width() + deviceSize.width();
            height = mMainWindow->height() > deviceSize.height() ?
                mMainWindow->height() : deviceSize.height();
        }
        mMainWindow->resize(width, height);
    }

    if (SUCCEED(rc)) {
        rc = ui->setupUi();
        if (!SUCCEED(rc)) {
            QMessageBox::warning(mMainWindow, NULL,
                "Failed to setup device ui.");
            SECURE_DELETE(ui);
        } else {
            mDeviceUi.push_back(ui);
        }
    }

    return rc;
}

int32_t UiComposer::onDeviceRemoved(QString &name)
{
    int32_t rc = NO_ERROR;
    DeviceUi *ui = nullptr;
    bool defaultUi = false;
    QSize deviceSize;

    if (SUCCEED(rc)) {
        for (auto iter = mDeviceUi.begin();
             iter != mDeviceUi.end(); iter++) {
            if ((*iter)->getName() == name) {
                ui = *iter;
                iter = mDeviceUi.erase(iter);
                break;
            }
        }
    }

    if (SUCCEED(rc)) {
        if (ISNULL(ui)) {
            QMessageBox::warning(mMainWindow, NULL,
                "Not found device ui.");
            rc = NOT_FOUND;
        }
    }

    if (SUCCEED(rc)) {
        if (!mDeviceUi.size()) {
            defaultUi = true;
            mDefaultUi = new DefaultUi(mMainWindow);
            if (ISNULL(mDefaultUi)) {
                QMessageBox::critical(mMainWindow, NULL,
                    "Failed to create default ui.");
            }
        }
    }

    if (SUCCEED(rc)) {
        deviceSize = ui->getSize();
        SECURE_DELETE(ui);
    }

    if (SUCCEED(rc)) {
        int32_t width = 0;
        int32_t height = 0;
        if (defaultUi) {
            QSize size = mDefaultUi->getSize();
            width = size.width();
            height = size.height();
        } else {
            width = mMainWindow->width() - deviceSize.width();
            height = mMainWindow->width() - (
                mMainWindow->width() - deviceSize.height());
        }
        mMainWindow->resize(width, height);
    }

    if (SUCCEED(rc)) {
        if (defaultUi) {
            rc = mDefaultUi->setupUi();
            if (!SUCCEED(rc)) {
                QMessageBox::warning(mMainWindow, NULL,
                    "Failed to setup default ui.");
                SECURE_DELETE(mDefaultUi);
            }
        }
    }

    return rc;
}

int32_t UiComposer::construct()
{
    int32_t rc = NO_ERROR;

    if (mConstructed) {
        rc = ALREADY_INITED;
    }

    if (SUCCEED(rc)) {
        mMainWindowUi = new MainWindowUi(mMainWindow);
        if (ISNULL(mMainWindowUi)) {
            QMessageBox::critical(mMainWindow, NULL,
                "Failed to create main window.");
        } else {
            rc = mMainWindowUi->setupUi();
            if (!SUCCEED(rc)) {
                QMessageBox::warning(mMainWindow, NULL,
                    "Failed to setup main window.");
                SECURE_DELETE(mMainWindowUi);
            }
        }
    }

    if (SUCCEED(rc)) {
        mDefaultUi = new DefaultUi(mMainWindow);
        if (ISNULL(mDefaultUi)) {
            QMessageBox::critical(mMainWindow, NULL,
                "Failed to new default ui.");
        } else {
            rc = mDefaultUi->setupUi();
            if (!SUCCEED(rc)) {
                QMessageBox::warning(mMainWindow, NULL,
                    "Failed to setup default ui.");
                SECURE_DELETE(mDefaultUi);
            }
        }
    }

    if (SUCCEED(rc)) {
        mConstructed = true;
    }

    return rc;
}

int32_t UiComposer::destruct()
{
    int32_t rc = NO_ERROR;

    if (!mConstructed) {
        rc = NOT_INITED;
    } else {
        mConstructed = false;
    }

    if (SUCCEED(rc)) {
        while(mDeviceUi.begin() != mDeviceUi.end()) {
            DeviceUi *ui = *mDeviceUi.begin();
            SECURE_DELETE(ui);
            mDeviceUi.erase(mDeviceUi.begin());
        }
    }

    if (SUCCEED(rc)) {
        SECURE_DELETE(mDefaultUi);
        SECURE_DELETE(mMainWindowUi);
    }

    if (!SUCCEED(rc)) {
        QMessageBox::warning(mMainWindow, NULL,
            "Failed to destruct ui composer.");
    }

    return rc;
}

}
