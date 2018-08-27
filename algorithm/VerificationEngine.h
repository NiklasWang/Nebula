#ifndef VERIFICATIONENGINE_H
#define VERIFICATIONENGINE_H

#include "algorithm/Interface.h"

namespace nebula {

struct VerificationEngineParm {
public:
    struct Yuv420sp {
        uint8_t *yuv;
        int32_t w;
        int32_t h;
        int32_t stride;
        int32_t scanline;
    };

public:
    Yuv420sp *main;
    Yuv420sp *sub;
    int8_t *otp;
    int32_t size;
};

class VerificationEngine :
    public AlgorithmInterface
{
public:
    typedef VerificationEngineParm ParmType;

public:
    int32_t init() override;
    int32_t deinit() override;
    int32_t process() override;
    int32_t set(void *parm) override;

public:
    VerificationEngine();
    virtual ~VerificationEngine();
};

}

#endif
