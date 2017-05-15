#include "random_util.hpp"

#include <cstdlib>
#include <ctime>

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    /**
     @namespace JrRandomUtil
     JrRandomUtil namespace.
     */
    namespace JrRandomUtil {

        void init()
        {
            ::srand(::time((time_t)0));
        }

        uint32 platform_rand_func()
        {
            return static_cast<uint32>(::rand());
        }

    }   // end of JrRandomUtil

}   // end of Jirak



// <EOF>


