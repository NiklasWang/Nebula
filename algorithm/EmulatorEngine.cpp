#include <QtGlobal>
#include <QTime>

#include "utils/common.h"
#include "utils/Times.h"
#include "algorithm/EmulatorEngine.h"

#define EMULATOR_DELAY_TIME_BASE_MS 3000
#define EMULATOR_DELAY_TIME_RANDOM  1500

namespace nebula {

int32_t EmulatorEngine::init()
{
    return NO_ERROR;
}

int32_t EmulatorEngine::deinit()
{
    return NO_ERROR;
}

int32_t EmulatorEngine::process()
{
    qsrand(QTime(0, 0).secsTo(QTime::currentTime()));

    delayMs(EMULATOR_DELAY_TIME_BASE_MS +
            qrand() % EMULATOR_DELAY_TIME_RANDOM);

    qDebug() << "Current data path is: " << mPath;

    return NO_ERROR;
}

QString EmulatorEngine::query()
{
    return "emulator query test";
}

int32_t EmulatorEngine::set(void * /*parm*/)
{
    return NO_ERROR;
}

EmulatorEngine::EmulatorEngine(QString path) :
    mPath(path)
{
}

}
