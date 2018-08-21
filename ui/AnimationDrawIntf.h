#ifndef ANIMATIONDRAWINTF_H
#define ANIMATIONDRAWINTF_H

#include <stdint.h>

namespace nebula {

class AnimationDrawIntf
{
public:
    virtual drawAnimation(int32_t frameId) = 0;
    virtual ~AnimationDrawIntf() {}
};

}

#endif
