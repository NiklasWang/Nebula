#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QString>
#include <QFile>

#include "algorithm/Config.h"
#include "algorithm/Interface.h"

namespace nebula {

class Algorithm :
    public AlgorithmInterface
{
public:
    int32_t init() override;
    int32_t deinit() override;
    int32_t process() override;
    int32_t set(void *parm) override;

public:
    explicit Algorithm(QString path, QString name);
    virtual ~Algorithm();

private:
    enum FileType {
        FILE_TYPE_OTP,
        FILE_TYPE_MAIN,
        FILE_TYPE_SUB,
        FILE_TYPE_MAX_INVALID
    };

    struct MemoryMap {
        uint8_t *dat;
        int32_t size;
    };

private:
    QString    mPath;
    QString    mName;
    AlgorithmInterface *mAlg;
    QFile     *mFiles[FILE_TYPE_MAX_INVALID];
    MemoryMap mMemMap[FILE_TYPE_MAX_INVALID];
};

}

#endif
