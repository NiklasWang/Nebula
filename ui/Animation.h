#ifndef ANIMATION_H
#define ANIMATION_H

#define ANIMATION_EVERY_FRAME_TIME 30 // ms

#include "utils/Timer.h"
#include "ui/AnimationDrawIntf.h"

namespace nebula {

class Animation
{
public:
    int32_t start();
    int32_t stop();
    int32_t draw();
    QString name();

public:
    Animation(AnimationDrawIntf *intf, QString name);

private:
    QString mName;
    Timer   mTimer;
    int32_t mFrameId;
    AnimationDrawIntf *mIntf;
};

}

#endif
