#include <QMainWindow>

#include "utils/common.h"
#include "core/Common.h"
#include "core/UiComposer.h"

namespace nebula {

UiComposer::UiComposer(QMainWindow *window) :
    mConstructed(false),
    mMainWindow(window),
    mBaseWidget(nullptr),
    mMainWindowUi(nullptr),
    mDefaultUi(nullptr)
{
    qRegisterMetaType<MessageType>("MessageType");
    qRegisterMetaType<std::function<int32_t ()> >("std::function<int32_t ()>");
    qRegisterMetaType<DeviceUiType>("DeviceUiType");

    connect(this, SIGNAL(drawUi(std::function<int32_t ()>)),
            this, SLOT(onDrawUi(std::function<int32_t ()>)),
            Qt::BlockingQueuedConnection);

    connect(this, SIGNAL(drawAnimationFrame(QString, int32_t)),
            this, SLOT(onDrawAnimationFrame(QString, int32_t)),
            Qt::BlockingQueuedConnection);

    connect(this, SIGNAL(updateUi(DeviceUi *, DeviceUiType, bool)),
            this, SLOT(onUpdateUi(DeviceUi *, DeviceUiType, bool)),
            Qt::BlockingQueuedConnection);

    connect(this, SIGNAL(showDebug(DeviceUi *, QString)),
            this, SLOT(onShowDebug(DeviceUi *, QString)));
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
    Animation *animation = nullptr;
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
            mBaseWidget, name, mDeviceUi.size());
        if (ISNULL(ui)) {
            showError("Failed to create device ui.");
            rc = NO_MEMORY;
        }
    }

    if (SUCCEED(rc)) {
        animation = new Animation(this, name);
        if (ISNULL(animation)) {
            showError("Failed to create device animation.");
            rc = NO_MEMORY;
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
            animation->start();
            mAnimation.push_back(animation);
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
        for (auto iter = mAnimation.begin();
             iter != mAnimation.end(); iter++) {
            if ((*iter)->name() == name) {
                Animation *animation = *iter;
                animation->stop();
                SECURE_DELETE(animation);
                iter = mAnimation.erase(iter);
                break;
            }
        }
    }

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
            mDefaultUi = new DefaultUi(mBaseWidget);
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

int32_t UiComposer::drawAnimation(QString name, int32_t frameId)
{
    int32_t rc = NO_ERROR;

    if (SUCCEED(rc)) {
        rc = drawAnimationFrame(name, frameId);
        if (!SUCCEED(rc)) {
            showError("Failed to draw animation frame");
        }
    }

    if (SUCCEED(rc)) {
        for (auto iter = mAnimation.begin();
             iter != mAnimation.end(); iter++) {
            if ((*iter)->name() == name) {
                Animation *animation = *iter;
                animation->start();
                break;
            }
        }
    }

    return rc;
}

int32_t UiComposer::onDrawAnimationFrame(QString name, int32_t frameId)
{
    int32_t rc = NO_ERROR;
    DeviceUi *ui = nullptr;

    if (SUCCEED(rc)) {
        for (auto iter = mDeviceUi.begin();
             iter != mDeviceUi.end(); iter++) {
            if ((*iter)->getName() == name) {
                ui = *iter;
                break;
            }
        }
    }

    if (SUCCEED(rc)) {
        if (NOTNULL(ui)) {
            rc = ui->drawAnimation(frameId);
            if (!SUCCEED(rc)) {
                showError("Failed to draw animation");
            }
        } else {
            showError("Failed to find animation painter");
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
        mBaseWidget = new QWidget(mMainWindow);
        if (ISNULL(mBaseWidget)) {
            showError("Failed to create base widget.");
            rc = NO_MEMORY;
        } else {
            mBaseWidget->setObjectName(
                QStringLiteral("centralWidget"));
        }
    }

    if (SUCCEED(rc)) {
        mMainWindowUi = new MainWindowUi(mMainWindow);
        if (ISNULL(mMainWindowUi)) {
            showError("Failed to create main window.");
        } else {
            connect(mMainWindowUi, SIGNAL(quit()),
                    this, SIGNAL(quit()));
        }
    }

    if (SUCCEED(rc)) {
        rc = mMainWindowUi->setupUi();
        if (!SUCCEED(rc)) {
            showError("Failed to setup main window.");
            SECURE_DELETE(mMainWindowUi);
        }
    }

    if (SUCCEED(rc)) {
        mDefaultUi = new DefaultUi(mBaseWidget);
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
        while (mAnimation.begin() != mAnimation.end()) {
            Animation *animation = *mAnimation.begin();
            animation->stop();
            SECURE_DELETE(animation);
            mAnimation.erase(mAnimation.begin());
        }
    }

    if (SUCCEED(rc)) {
        while (mDeviceUi.begin() != mDeviceUi.end()) {
            DeviceUi *ui = *mDeviceUi.begin();
            SECURE_DELETE(ui);
            mDeviceUi.erase(mDeviceUi.begin());
        }
    }

    if (SUCCEED(rc)) {
        SECURE_DELETE(mDefaultUi);
        SECURE_DELETE(mMainWindowUi);
    }

    if (SUCCEED(rc)) {
        if (NOTNULL(mBaseWidget)) {
            mBaseWidget->setParent(nullptr);
            mBaseWidget->deleteLater();
            mBaseWidget = nullptr;
        }
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

int32_t UiComposer::updateUiResult(QString name, DeviceUiType type, bool result)
{
    int32_t rc = NO_ERROR;
    DeviceUi *ui = nullptr;

    if (SUCCEED(rc)) {
        for (auto iter = mDeviceUi.begin();
             iter != mDeviceUi.end(); iter++) {
            if ((*iter)->getName() == name) {
                ui = *iter;
                break;
            }
        }
    }

    if (SUCCEED(rc)) {
        if (NOTNULL(ui)) {
            rc = updateUi(ui, type, result);
            if (!SUCCEED(rc)) {
                showError("Failed to send update ui signal");
            }
        }
    }

    return rc;
}

int32_t UiComposer::onUpdateUi(DeviceUi *ui, DeviceUiType type, bool result)
{
    int32_t rc = NO_ERROR;

    if (NOTNULL(ui)) {
        rc = ui->update(type, result);
    }

    return rc;
}

void UiComposer::debug(QString name, QString text)
{
    int32_t rc = NO_ERROR;
    DeviceUi *ui = nullptr;

    if (SUCCEED(rc)) {
        for (auto iter = mDeviceUi.begin();
             iter != mDeviceUi.end(); iter++) {
            if ((*iter)->getName() == name) {
                ui = *iter;
                break;
            }
        }
    }

    if (SUCCEED(rc)) {
        if (NOTNULL(ui)) {
            showDebug(ui, text);
        }
    }

    return;
}

int32_t UiComposer::onShowDebug(DeviceUi *ui, QString text)
{
    int32_t rc = NO_ERROR;

    if (NOTNULL(ui)) {
        rc = ui->debug(text);
    }

    return rc;
}

}
