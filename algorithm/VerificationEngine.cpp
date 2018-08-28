#include "utils/common.h"
#include "core/common.h"
#include "algorithm/AlgorithmHelper.h"
#include "algorithm/VerificationEngine.h"
#include "external/inc/arcsoft_verification.h"

namespace nebula {

int32_t VerificationEngine::process()
{
    int32_t rc = NO_ERROR;
    ASVLOFFSCREEN vleftoffscreen;
    ASVLOFFSCREEN vrightoffscreen;
    ArcStereoImageData imagedata;

    if (SUCCEED(rc)) {
        int32_t w = getAlignedStride(mParm.main.w, mParm.main.stride);
        uint8_t *y = getNV21YData(mParm.main.yuv, mParm.main.w,
            mParm.main.h, mParm.main.stride, mParm.main.scanline);
        uint8_t *uv = getNV21YData(mParm.main.yuv, mParm.main.w,
            mParm.main.h, mParm.main.stride, mParm.main.scanline);

        memset(&vleftoffscreen, 0, sizeof(ASVLOFFSCREEN));
        vleftoffscreen.i32Width  = mParm.main.w;
        vleftoffscreen.i32Height = mParm.main.h;
        vleftoffscreen.u32PixelArrayFormat = ASVL_PAF_NV21;
        vleftoffscreen.pi32Pitch[0] = w;
        vleftoffscreen.pi32Pitch[1] = w;
        vleftoffscreen.ppu8Plane[0] = y;
        vleftoffscreen.ppu8Plane[1] = uv;
    }

    if (SUCCEED(rc)) {
        int32_t w = getAlignedStride(mParm.sub.w, mParm.sub.stride);
        uint8_t *y = getNV21YData(mParm.sub.yuv, mParm.sub.w,
            mParm.sub.h, mParm.sub.stride, mParm.sub.scanline);
        uint8_t *uv = getNV21YData(mParm.sub.yuv, mParm.sub.w,
            mParm.sub.h, mParm.sub.stride, mParm.sub.scanline);

        memset(&vrightoffscreen, 0, sizeof(ASVLOFFSCREEN));
        vrightoffscreen.i32Width = mParm.sub.w;
        vrightoffscreen.i32Height = mParm.sub.h;
        vrightoffscreen.u32PixelArrayFormat = ASVL_PAF_NV21;
        vrightoffscreen.pi32Pitch[0] = w;
        vrightoffscreen.pi32Pitch[1] = w;
        vrightoffscreen.ppu8Plane[0] = y;
        vrightoffscreen.ppu8Plane[1] = uv;
    }

    if (SUCCEED(rc)) {
        memset(&imagedata, 0, sizeof(ArcStereoImageData));
        imagedata.chessboardWidth = 19;
        imagedata.chessboardHeight = 14;
        imagedata.leftImg  = &vleftoffscreen;
        imagedata.rightImg = &vrightoffscreen;
    }

    if (SUCCEED(rc)) {
        MDouble errs[VERIFY_RES_SIZE] = { 0 };
        rc = MC_ModuleVerification(mEngine,
            &imagedata, mParm.otp, errs,
            mParm.name.toLocal8Bit().data());
        if (!SUCCEED(rc)) {
            qDebug() << "Device " << mParm.name
                     << " verification failed, " << rc
                     << " details ["
                     << errs[0] << " / "
                     << errs[1] << " / "
                     << errs[2] << "].";
        } else {
            qDebug() << "Device " << mParm.name
                     << " verification succeed.";
        }
    }

    return rc;
}

int32_t VerificationEngine::init()
{
    int32_t rc = NO_ERROR;

    if (ISNULL(mEngine)) {
        mEngine = MC_CreateEngine();
        if (ISNULL(mEngine)) {
            showError("Failed to create engine.");
            rc = NO_ERROR;
        }
    }

    return rc;
}

int32_t VerificationEngine::deinit()
{
    if (NOTNULL(mEngine)) {
        MC_DestroyEngine(mEngine);
        mEngine = nullptr;
    }

    return NO_ERROR;
}

int32_t VerificationEngine::set(void *parm)
{
    ParmType *p = static_cast<ParmType *>(parm);
    mParm = *p;

    return NO_ERROR;
}

VerificationEngine::VerificationEngine() :
    mEngine(nullptr)
{
}

VerificationEngine::~VerificationEngine()
{
    if (NOTNULL(mEngine)) {
        deinit();
    }
}

}
