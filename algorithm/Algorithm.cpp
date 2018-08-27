#include <QDir>
#include <QList>
#include <QFileInfoList>

#include "utils/common.h"
#include "core/common.h"
#include "algorithm/Config.h"
#include "algorithm/Algorithm.h"
#include "algorithm/EmulatorEngine.h"
#include "algorithm/VerificationEngine.h"

namespace nebula {

Algorithm::Algorithm(QString path) :
    mPath(path),
    mAlg(nullptr)
{
}

#ifdef USE_ALGORITHM_EMULATOR

int32_t Algorithm::init()
{
    int32_t rc = NO_ERROR;
    QFileInfoList list;

    if (ISNULL(mAlg)) {
        mAlg = new VerificationEngine(mPath);
        if (ISNULL(mAlg)) {
            showError("Failed to create algorithm.");
            rc = NO_MEMORY;
        }
    }

    if (SUCCEED(rc)) {
        QDir dir(mPath);
        dir.setFilter(QDir::Files | QDir::Hidden |
                      QDir::NoSymLinks | QDir::AllDirs);
        dir.setSorting(QDir::Size | QDir::Reversed);
        list = dir.entryInfoList();
        if (list.size() != DIR_FILE_NUM) {
            showError("Invalid file number in " + mPath);
            rc = PARAM_INVALID;
        }
    }

    if (SUCCEED(rc)) {
        for (auto iter : list) {
            if (iter.fileName().contains(
                MAIN_CAM_PIC_PREFIX, Qt::CaseSensitive)) {
                // main
            } else if (iter.fileName().contains(
               SUB_CAM_PIC_PREFIX, Qt::CaseSensitive)) {
                // main
            }  else if (iter.fileName().contains(
                SUB_CAM_PIC_PREFIX, Qt::CaseSensitive)) {
                // main
            } else {
                showError("Unknown file type " + iter.fileName());
                rc = INVALID_FORMAT;
            }
        }
    }

    return rc;
}

int32_t Algorithm::deinit()
{

}

int32_t Algorithm::process()
{

}

int32_t Algorithm::set(void * /*parm*/)
{
    return NOT_REQUIRED;
}

#else

int32_t Algorithm::init()
{
    int32_t rc = NO_ERROR;

    if (ISNULL(mAlg)) {
        mAlg = new EmulatorEngine(mPath);
        if (ISNULL(mAlg)) {
            showError("Failed to create emulator.");
            rc = NO_MEMORY;
        }
    }

    if (SUCCEED(rc)) {
        rc = mAlg->init();
        if (!SUCCEED(rc)) {
            showError("Failed to init emulator.");
        }
    }

    return rc;
}

int32_t Algorithm::deinit()
{
    int32_t rc = NO_ERROR;

    if (NOTNULL(mAlg)) {
        rc = mAlg->deinit();
        SECURE_DELETE(mAlg);
    }

    return rc;
}

int32_t Algorithm::process()
{
    int32_t rc = NO_ERROR;

    if (NOTNULL(mAlg)) {
        rc = mAlg->process();
        if (!SUCCEED(rc)) {
            showError("Failed to process emulator.");
        }
    }

    return rc;
}

int32_t Algorithm::set(void * /*parm*/)
{
    return NOT_REQUIRED;
}

#endif

}
