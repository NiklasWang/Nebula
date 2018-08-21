#include "utils/common.h"
#include "core/common.h"
#include "Animation.h"

namespace nebula {

int32_t Animation::start()
{
    return mTimer.startNow(
        Ms(ANIMATION_EVERY_FRAME_TIME),
        [this]() -> int32_t {
            int32_t _rc = draw();
            if (!SUCCEED(_rc)) {
                showError(QString() + "Failed to start timer, " +
                    ANIMATION_EVERY_FRAME_TIME + " ms.");
            }
            return _rc;
        }
    );
}

int32_t Animation::stop()
{
    return mTimer.stopNow();
}

int32_t Animation::draw()
{
    int32_t rc = NO_ERROR;

    if (SUCCEED(rc)) {
        if (ISNULL(mIntf)) {
            showError("Invalid animation drawer ");
            rc = PARAM_INVALID;
        }
    }

    if (SUCCEED(rc)) {
        rc = mIntf->drawAnimation(mFrameId++);
        if (!SUCCEED(rc)) {
            showError("Failed to draw animation.");
        }
    }

    return rc;
}

Animation::Animation(AnimationDrawIntf *intf, QString name) :
    mName(name),
    mTimer(name),
    mFrameId(0),
    mIntf(intf)
{
}

}
