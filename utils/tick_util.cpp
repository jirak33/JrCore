#include "tick_util.hpp"

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <limits>

#if defined(_WIN32)
    #include <windows.h> //< GetTickCount().
#else
    #if defined(__linux__) || defined(ANDROID)
        #include <linux/version.h>
        #if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,0))
            #define _USE_CLOCK_GETTIME
            //int clock_gettime(clockid_t, struct timespec*);
        #endif
    #endif
    #include <sys/times.h> //< times().
#endif

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    /**
     @namespace JrTickUtil
     JrTickUtil namespace.
     */
    namespace JrTickUtil {

        uint32 currentTick()
        {
        #if defined(_WIN32)
            return ::GetTickCount();
        #elif defined(_USE_CLOCK_GETTIME)
            struct timespec tp;
            clock_gettime(CLOCK_MONOTONIC, &tp);
            return static_cast<uint32>(tp.tv_sec) * 1000 + static_cast<uint32>(tp.tv_nsec) / 1000000;
        #elif defined (__APPLE__)
            mach_timebase_info_data_t info;
            uint64_t nAbsTime = mach_absolute_time();
            mach_timebase_info(&info);
            uint64_t nNanoTime = nAbsTime * (info.numer / info.denom);
            return static_cast<uint32>(nNanoTime / 1000000);
        #else
            struct tms t;
            return static_cast<uint32>(times(&t)) * 10;
        #endif
        }

        uint32 diffTick(uint32 t1, uint32 t2)
        {
            return (t1 <= t2) ? t2 - t1 : (std::numeric_limits<uint32>::max() - t1) + t2 + 1;
        }

    }   // end of JrTickUtil

}   // end of Jirak



// <EOF>


