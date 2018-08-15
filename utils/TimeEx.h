#ifndef _TIME_EX_H_
#define _TIME_EX_H_

#include <sys/time.h>
#include <windows.h>

namespace nebula {

inline int64_t currentUs()
{
    int64_t t = 0;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    t = (int64_t)tv.tv_usec + tv.tv_sec * 1000000ll;

    return t;
}

inline void delayMs(int32_t ms)
{
    if (ms > 0) {
        Sleep(ms);
    }
}

inline void delaySec(int32_t sec)
{
    delayMs(sec * 1000);
}

}

#endif
