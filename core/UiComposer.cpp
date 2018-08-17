#include <QMainWindow>

#include "utils/common.h"
#include "core/common.h"
#include "core/UiComposer.h"

namespace nebula {

UiComposer::UiComposer(QMainWindow *window) :
    mConstructed(false),
    mMainWindow(window),
    mMainWindowUi(nullptr),
    mDefaultUi(nullptr)
{
    qRegisterMetaType<MessageType>("MessageType");
    qRegisterMetaType<std::function<int32_t ()> >("std::function<int32_t ()>");

    connect(this, SIGNAL(drawUi(std::function<int32_t ()>)),
            this, SLOT(onDrawUi(std::function<int32_t ()>)),
            Qt::BlockingQueuedConnection);
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

    if (SUCCEED(rc)) {
        if (!mDeviceUi.size()) {
            removeDefaultUi = true;
        }
    }

    if (SUCCEED(rc)) {
        for (auto &device : mDeviceUi) {
            if (device->getName() == name) {
                showError("Device UI already exists.");
                rc = ALREADY_EXISTS;
            }
        }
    }

    if (SUCCEED(rc)) {
        ui = new DeviceUi(
            mMainWindow, name, mDeviceUi.size());
        if (ISNULL(ui)) {
            showError("Failed to create device ui.");
        }
    }

    if (SUCCEED(rc)) {
        rc = drawUi(
            [removeDefaultUi, this]() -> int32_t {
                if (removeDefaultUi) {
                    SECURE_DELETE(mDefaultUi);
                }
                return NO_ERROR;
            }
        );
        if (!SUCCEED(rc)) {
            showError("Failed to remove default ui.");
        }
    }

    if (SUCCEED(rc)) {
        rc = drawUi(
            [&]() -> int32_t {
                int32_t _rc = ui->setupUi();
                if (!SUCCEED(_rc)) {
                    showError("Failed to setup device ui.");
                    SECURE_DELETE(ui);
                }
                return _rc;
            }
        );
        if (SUCCEED(rc)) {
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
            showError("Not found device ui.");
            rc = NOT_FOUND;
        }
    }

    if (SUCCEED(rc)) {
        if (!mDeviceUi.size()) {
            defaultUi = true;
            mDefaultUi = new DefaultUi(mMainWindow);
            if (ISNULL(mDefaultUi)) {
                showError("Failed to create default ui.");
            }
        }
    }

    if (SUCCEED(rc)) {
        rc = drawUi(
            [&]() -> int32_t {
                SECURE_DELETE(ui);
                return NO_ERROR;
            }
        );
        if (!SUCCEED(rc)) {
            showError("Failed to remove default ui.");
        }
        ui = nullptr;
    }

    if (SUCCEED(rc)) {
        rc = drawUi(
            [defaultUi, this]() -> int32_t {
                int32_t _rc = NO_ERROR;
                if (defaultUi) {
                    _rc = mDefaultUi->setupUi();
                    if (!SUCCEED(_rc)) {
                        showError("Failed to setup default ui.");
                        SECURE_DELETE(mDefaultUi);
                    }
                }
                return _rc;
            }
        );
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
            showError("Failed to create main window.");
        } else {
            rc = mMainWindowUi->setupUi();
            if (!SUCCEED(rc)) {
                showError("Failed to setup main window.");
                SECURE_DELETE(mMainWindowUi);
            }
        }
    }

    if (SUCCEED(rc)) {
        mDefaultUi = new DefaultUi(mMainWindow);
        if (ISNULL(mDefaultUi)) {
            showError("Failed to new default ui.");
        } else {
            rc = mDefaultUi->setupUi();
            if (!SUCCEED(rc)) {
                showError("Failed to setup default ui.");
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
        showError("Failed to destruct ui composer.");
    }

    return rc;
}

int32_t UiComposer::onDrawUi(std::function<int32_t ()> func)
{
    return func();
}

}
