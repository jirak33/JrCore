#ifndef _JIRAK_CORE_RANDOM_UTILS_H
#define _JIRAK_CORE_RANDOM_UTILS_H
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
     @namespace JrRandomUtil
     RandomUtil namespace.
     */
    namespace JrRandomUtil {
    /**
     @defgroup jr_random_util rand related.
     */
    //@{

        void init();

        uint32 platform_rand_func();

        template<typename T>
        T genNumber()
        {
            return static_cast<T>((uint32)(platform_rand_func() * 745631) % 100000);
        }

    //@}
    }   // end of JrRandomUtil

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_RANDOM_UTILS_H


// <EOF>


