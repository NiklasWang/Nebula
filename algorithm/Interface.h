#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdint.h>

#include <QString>

namespace nebula {

class AlgorithmInterface
{
public:
    virtual int32_t init() = 0;
    virtual int32_t deinit() = 0;
    virtual int32_t process() = 0;
    virtual int32_t set(void *parm) = 0;
    virtual QString query() = 0;

public:
    virtual ~AlgorithmInterface() {}
};

}

#endif
