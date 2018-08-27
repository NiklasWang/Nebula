#ifndef VERIFICATION_H
#define VERIFICATION_H

#include <QString>

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
    explicit Algorithm(QString path);
    virtual ~Algorithm();

private:
    QString mPath;
    AlgorithmInterface *mAlg;
    QList<QFile  *>     mFiles;
};

}

#endif
