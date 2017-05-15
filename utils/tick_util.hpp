#ifndef _JIRAK_CORE_TICK_UTIL_H
#define _JIRAK_CORE_TICK_UTIL_H
/////////////////////////////////////////////////////////////////////

// MS compatible compilers support #pragma once.
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "../base/type.hpp"

/////////////////////////////////////////////////////////////////////

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    /**
     @namespace JrTickUtil
     RandomUtil namespace.
     */
    namespace JrTickUtil {
    /**
     @defgroup jr_tick_util Tick related.
     */
    //@{

        /**
         Get current system tick.
         @return current system tick
         @see diffTick()
         */
        uint32 currentTick();

        /**
         Get difference tick between @a t1 and @a t2.
         @param t1 previsous tick count.
         @param t2 next tick count.
         @return @a t2 - @a t1.
         t1 should be prior to t2.
         */
        uint32 diffTick(uint32 t1, uint32 t2);

    //@}
    }   // end of JrTickUtil

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_TICK_UTIL_H


// <EOF>


