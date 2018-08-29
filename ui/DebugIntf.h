#ifndef DEBUGINTF_H
#define DEBUGINTF_H

#include <stdint.h>

#include <QString>

namespace nebula {

class DebugIntf
{
public:
    virtual void debug(QString text, QString name) = 0;
    virtual ~DebugIntf() {}
};

}

#endif
