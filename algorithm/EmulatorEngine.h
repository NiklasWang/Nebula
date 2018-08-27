#ifndef EMULATORENGINE_H
#define EMULATORENGINE_H

#include <QString>

#include "algorithm/Interface.h"

namespace nebula {

class EmulatorEngine :
    public AlgorithmInterface
{
public:
    int32_t init() override;
    int32_t deinit() override;
    int32_t process() override;
    int32_t set(void *parm) override;

public:
    EmulatorEngine(QString path);

private:
    QString mPath;
};

}

#endif
