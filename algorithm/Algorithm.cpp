#include <QDir>
#include <QFile>
#include <QList>
#include <QFileInfoList>

#include "utils/common.h"
#include "core/Common.h"
#include "algorithm/Config.h"
#include "algorithm/Algorithm.h"
#include "algorithm/EmulatorEngine.h"
#include "algorithm/VerificationEngine.h"

namespace nebula {

Algorithm::Algorithm(QString path, QString name) :
    mPath(path),
    mName(name),
    mAlg(nullptr)
{
}

Algorithm::~Algorithm()
{
    deinit();
}

#ifdef USE_ALGORITHM_EMULATOR

int32_t Algorithm::init()
{
    int32_t rc = NO_ERROR;
    QFileInfoList list;
    VerificationEngine::ParmType parm;

    if (ISNULL(mAlg)) {
        mAlg = new VerificationEngine();
        if (ISNULL(mAlg)) {
            showError("Failed to create algorithm.");
            rc = NO_MEMORY;
        }
    }

    if (SUCCEED(rc)) {
        rc = mAlg->init();
        if (!SUCCEED(rc)) {
            showError("Failed to init algorithm");
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
            QString name = iter.fileName();
            QStringList words = name.split("_", QString::SkipEmptyParts);
            QString ws = words.at(FILENAME_W_POSITION);
            QString hs = words.at(FILENAME_H_POSITION);
            QString strides = words.at(FILENAME_STRIDE_POSITION);
            QString scanlines = words.at(FILENAME_SCANLINE_POSITION);

            if (name.contains(
                MAIN_CAM_PIC_PREFIX, Qt::CaseSensitive)) {
                mFiles[FILE_TYPE_MAIN] = new QFile(iter.absoluteFilePath());
                if (ISNULL(mFiles[FILE_TYPE_MAIN])) {
                    showError("Failed to create main qfile.");
                    rc = NO_MEMORY;
                } else {
                    parm.main.w = ws.toInt();
                    parm.main.h = hs.toInt();
                    parm.main.stride   = strides.toInt();
                    parm.main.scanline = scanlines.toInt();
                }
            } else if (name.contains(
                SUB_CAM_PIC_PREFIX, Qt::CaseSensitive)) {
                mFiles[FILE_TYPE_SUB] = new QFile(iter.absoluteFilePath());
                if (ISNULL(mFiles[FILE_TYPE_SUB])) {
                    showError("Failed to create sub qfile.");
                    rc = NO_MEMORY;
                } else {
                    parm.sub.w = ws.toInt();
                    parm.sub.h = hs.toInt();
                    parm.sub.stride   = strides.toInt();
                    parm.sub.scanline = scanlines.toInt();
                }
            }  else if (name.contains(
                OTP_DUAL_CAM_CALIB, Qt::CaseSensitive)) {
                mFiles[FILE_TYPE_OTP] = new QFile(iter.absoluteFilePath());
                if (ISNULL(mFiles[FILE_TYPE_OTP])) {
                    showError("Failed to create otp qfile.");
                    rc = NO_MEMORY;
                }
            } else {
                showError("Unknown file type " + iter.fileName());
                rc = INVALID_FORMAT;
            }
            if (!SUCCEED(rc)) {
                break;
            }
        }
    }

    if (SUCCEED(rc)) {
        if (!mFiles[FILE_TYPE_OTP]->exists() ||
            !mFiles[FILE_TYPE_MAIN]->exists() ||
            !mFiles[FILE_TYPE_SUB]->exists()) {
            showError("Some files are not exists.");
            rc = NOT_FOUND;
        }
    }

    if (SUCCEED(rc)) {
        rc = mFiles[0]->open(QFile::ReadOnly);
        if (!SUCCEED(rc)) {
            showError("Failed to open otp file");
        }
    }

    if (SUCCEED(rc)) {
        uint8_t *dat = mFiles[FILE_TYPE_OTP]->map(
            0, mFiles[FILE_TYPE_OTP]->size());
        if (ISNULL(dat)) {
            showError("Failed to load otp file");
            rc = NOT_READY;
        } else {
            parm.otp = mMemMap[FILE_TYPE_OTP].dat = dat;
            parm.size = mFiles[FILE_TYPE_OTP]->size();
            mMemMap[FILE_TYPE_OTP].size = parm.size;
        }
    }


    if (SUCCEED(rc)) {
        rc = mFiles[FILE_TYPE_MAIN]->open(QFile::ReadOnly);
        if (!SUCCEED(rc)) {
            showError("Failed to open main file");
        }
    }

    if (SUCCEED(rc)) {
        uint8_t *dat = mFiles[FILE_TYPE_MAIN]->map(
            0, mFiles[FILE_TYPE_MAIN]->size());
        if (ISNULL(dat)) {
            showError("Failed to load main file");
            rc = NOT_READY;
        } else {
            parm.main.yuv = mMemMap[FILE_TYPE_MAIN].dat = dat;
            parm.main.size = mFiles[FILE_TYPE_MAIN]->size();
            mMemMap[FILE_TYPE_MAIN].size = parm.main.size;
        }
    }

    if (SUCCEED(rc)) {
        rc = mFiles[FILE_TYPE_SUB]->open(QFile::ReadOnly);
        if (!SUCCEED(rc)) {
            showError("Failed to open sub file");
        }
    }

    if (SUCCEED(rc)) {
        uint8_t *dat = mFiles[FILE_TYPE_SUB]->map(
            0, mFiles[FILE_TYPE_SUB]->size());
        if (ISNULL(dat)) {
            showError("Failed to load sub file");
            rc = NOT_READY;
        } else {
            parm.sub.yuv = mMemMap[FILE_TYPE_SUB].dat = dat;
            parm.sub.size = mFiles[FILE_TYPE_SUB]->size();
            mMemMap[FILE_TYPE_SUB].size = parm.sub.size;
        }
    }

    if (SUCCEED(rc)) {
        parm.name = mName;
        rc = mAlg->set(&parm);
        if (!SUCCEED(rc)) {
            showError("Failed to set parm to algorithm");
        }
    }

    return rc;
}

int32_t Algorithm::deinit()
{
    if (NOTNULL(mMemMap[FILE_TYPE_OTP].dat)) {
        mFiles[FILE_TYPE_OTP]->unmap(mMemMap[FILE_TYPE_OTP].dat);
        mMemMap[FILE_TYPE_OTP].dat = nullptr;
        mFiles[FILE_TYPE_OTP]->close();
        SECURE_DELETE(mFiles[FILE_TYPE_OTP]);
        mFiles[FILE_TYPE_OTP] = nullptr;
    }

    if (NOTNULL(mMemMap[FILE_TYPE_MAIN].dat)) {
        mFiles[FILE_TYPE_MAIN]->unmap(mMemMap[FILE_TYPE_MAIN].dat);
        mMemMap[FILE_TYPE_MAIN].dat = nullptr;
        mFiles[FILE_TYPE_MAIN]->close();
        SECURE_DELETE(mFiles[FILE_TYPE_MAIN]);
        mFiles[FILE_TYPE_MAIN] = nullptr;
    }

    if (NOTNULL(mMemMap[FILE_TYPE_SUB].dat)) {
        mFiles[FILE_TYPE_SUB]->unmap(mMemMap[FILE_TYPE_SUB].dat);
        mMemMap[FILE_TYPE_SUB].dat = nullptr;
        mFiles[FILE_TYPE_SUB]->close();
        SECURE_DELETE(mFiles[FILE_TYPE_SUB]);
        mFiles[FILE_TYPE_SUB] = nullptr;
    }

    return NO_ERROR;
}

int32_t Algorithm::process()
{
    int32_t rc = NOT_INITED;

    if (NOTNULL(mAlg)) {
        rc = mAlg->process();
        if (!SUCCEED(rc)) {
            showError("Failed to process algorithm.");
        }
    }

    return rc;
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
