#include <assert.h>

#include "utils/common.h"
#include "algorithm/AlgorithmHelper.h"

namespace nebula {

#define MAX_ALIGN_SIZE    4096
#define FRAME_PAD_SIZE    4096

#define ALIGN_WITH_NUM(num, stride) \
    (((num) + (stride) - 1) & (~((stride) - 1)))

size_t PadToNum(int32_t base, int32_t num)
{
    return (num > 1) ? ALIGN_WITH_NUM(base, num) : base;
}

size_t getAlignedStride(int32_t num, int32_t stride)
{
    return (stride > 1) ? ALIGN_WITH_NUM(num, stride) : num;
}

size_t getFrameLen(int32_t w, int32_t h, int32_t stride)
{
    return getFrameLen(w, h, stride, stride);
}

size_t getFrameLen(int32_t w, int32_t h, int32_t stride, int32_t scanline)
{
    int32_t width = getAlignedStride(w, stride);
    int32_t height = getAlignedStride(h, scanline);
    return ALIGN_WITH_NUM(width * height * 3 / 2, FRAME_PAD_SIZE);
}

size_t getFrameLen2(int32_t w, int32_t h, int32_t stride)
{
    return getFrameLen2(w, h, stride, stride);
}

size_t getFrameLen2(int32_t w, int32_t h, int32_t stride, int32_t scanline)
{
    int32_t width = getAlignedStride(w, stride);
    int32_t height = getAlignedStride(h, scanline);
    return width * height * 3 / 2;
}

size_t getMinimumBufSize(int32_t w, int32_t h)
{
    return getFrameLen(w, h);
}

size_t getMinimumBufSize(int32_t w, int32_t h, int32_t scanline)
{
    return getFrameLen(w, getAlignedStride(h, scanline));
}

size_t getMaximumFrameLen(int32_t w, int32_t h, int32_t stride, int32_t scanline)
{
    // Consider frame rotation issue, may need bigger buffer if rotate 90 or 270
    size_t size1 = getFrameLen(w, h, stride, scanline);
    size_t size2 = getFrameLen(h, w, stride, scanline);
    return size1 > size2 ? size1 : size2;
}

bool haveStride(int32_t w, int32_t h, size_t frame_len)
{
    return !(getMinimumBufSize(w, h) == frame_len);
}

bool haveStride(int32_t w, int32_t h, size_t frame_len, int32_t scanline)
{
    return !(getMinimumBufSize(w, h, scanline) == frame_len);
}

int32_t getStride(int32_t w, int32_t h, size_t frame_len)
{
    int32_t result = 1;

    do {
        if (getFrameLen(w, h, result) == frame_len) {
            break;
        }
        result *= 2;
    } while (result < (MAX_ALIGN_SIZE + 1));

    return (result > MAX_ALIGN_SIZE) ? 0 : result ;
}

int32_t getStride(int32_t w, int32_t h, size_t frame_len, int32_t scanline)
{
    int32_t result = 1;

    do {
        if (getFrameLen(w, h, result, scanline) == frame_len) {
            break;
        }
        result *= 2;
    } while (result < (MAX_ALIGN_SIZE + 1));

    return (result > MAX_ALIGN_SIZE) ? 0 : result ;
}

int32_t NV21RemoveStride(uint8_t* dst, uint8_t* src,
    int32_t w, int32_t h, int32_t stride)
{
    return NV21RemoveStride(dst, src, w, h, stride, stride);
}

int32_t NV21RemoveStride(uint8_t* dst, uint8_t* src,
    int32_t w, int32_t h, int32_t stride, int32_t scanline)
{
    assert(NOTNULL(src));
    assert(NOTNULL(dst));

    uint32_t offset_src = 0;
    uint32_t offset_dst = 0;

    for (int32_t i = 0; i < h; i++) {
        memcpy(dst + offset_dst, src + offset_src, w);
        offset_dst += w;
        offset_src += ALIGN_WITH_NUM(w, stride);
    }

    offset_src = ALIGN_WITH_NUM(w, stride) * ALIGN_WITH_NUM(h, scanline);
    for (int32_t i = 0; i < (h / 2); i++) {
        memcpy(dst + offset_dst, src + offset_src, w);
        offset_dst += w;
        offset_src += ALIGN_WITH_NUM(w, stride);
    }

    return NO_ERROR;
}

int32_t NV21AddStride(uint8_t* dst, uint8_t* src,
    int32_t w, int32_t h, int32_t stride)
{
    return NV21AddStride(dst, src, w, h, stride, stride);
}

int32_t NV21AddStride(uint8_t* dst, uint8_t* src,
    int32_t w, int32_t h, int32_t stride, int32_t scanline)
{
    assert(NOTNULL(src));
    assert(NOTNULL(dst));

    uint32_t offset_src = 0;
    uint32_t offset_dst = 0;

    for (int32_t i = 0; i < h; i++) {
        memcpy(dst + offset_dst, src + offset_src, w);
        offset_dst += ALIGN_WITH_NUM(w, stride);
        offset_src += w;
    }

    offset_dst = ALIGN_WITH_NUM(w, stride) * ALIGN_WITH_NUM(h, scanline);
    for (int32_t i = 0; i < (h / 2); i++) {
        memcpy(dst + offset_dst, src + offset_src, w);
        offset_dst += ALIGN_WITH_NUM(w, stride);
        offset_src += w;
    }

    return NO_ERROR;
}

uint8_t *getNV21YData(uint8_t* frame,
    int32_t /*w*/, int32_t /*h*/, int32_t /*stride*/)
{
    assert(NOTNULL(frame));
    return frame;
}

uint8_t *getNV21YData(uint8_t* frame,
    int32_t /*w*/, int32_t /*h*/, int32_t /*stride*/, int32_t /*scanline*/)
{
    assert(NOTNULL(frame));
    return frame;
}

uint8_t *getNV21UVData(uint8_t* frame,
    int32_t w, int32_t h, int32_t stride)
{
    return getNV21UVData(frame, w, h, stride, stride);
}

uint8_t *getNV21UVData(uint8_t* frame,
    int32_t w, int32_t h, int32_t stride, int32_t scanline)
{
    assert(NOTNULL(frame));
    int32_t width = getAlignedStride(w, stride);
    int32_t height = getAlignedStride(h, scanline);
    return getNV21YData(frame, w, h, stride) + width * height;
}

uint8_t *getI420YData(uint8_t *frame,
    int32_t /*w*/, int32_t /*h*/,
    int32_t /*ystride*/, int32_t /*ustride*/, int32_t /*vstride*/)
{
    assert(NOTNULL(frame));
    return frame;
}

uint8_t *getI420UData(uint8_t *frame,
    int32_t w, int32_t h,
    int32_t ystride, int32_t ustride, int32_t vstride)
{
    return getI420YData(frame, w, h, ystride, ustride, vstride) +
        ALIGN_WITH_NUM(w, ystride) * h;
}

uint8_t *getI420VData(uint8_t *frame,
    int32_t w, int32_t h,
    int32_t ystride, int32_t ustride, int32_t vstride)
{
    return getI420UData(frame, w, h, ystride, ustride, vstride) +
        ALIGN_WITH_NUM(w, ustride) * h / 4;
}

int32_t yuv420spToYuv420p(uint8_t *yuv420sp, uint8_t *yuv420p,
    int32_t width, int32_t height)
{
    int32_t i, j;
    int32_t y_size = width * height;

    uint8_t *y = yuv420sp;
    uint8_t *uv = yuv420sp + y_size;

    uint8_t *y_tmp = yuv420p;
    uint8_t *u_tmp = yuv420p + y_size;
    uint8_t *v_tmp = yuv420p + y_size * 5 / 4;

    memcpy(y_tmp, y, y_size);
    y_tmp = y;

    for (j = 0, i = 0; j < y_size / 2; j += 2, i++) {
        v_tmp[i] = uv[j];
        u_tmp[i] = uv[j+1];
    }

    return NO_ERROR;
}

int32_t convertNV12ToNV21(uint8_t* dat,
    int32_t w, int32_t h, int32_t stride, int32_t scanline)
{
    uint8_t t;
    uint8_t *uv = getNV21UVData(dat, w, h, stride, scanline);

    size_t len = getAlignedStride(w, stride) *
        getAlignedStride(h, scanline) / 2;
    for (uint32_t i = 0; i < len; i += 2) {
        t = *(uv + i);
        *(uv + i) = *(uv + i + 1);
        *(uv + i + 1) = t;
    }

    return NO_ERROR;
}

int32_t convertNV21ToNV12(uint8_t* dat,
    int32_t w, int32_t h, int32_t stride, int32_t scanline)
{
    return convertNV12ToNV21(dat, w, h, stride, scanline);
}

};

