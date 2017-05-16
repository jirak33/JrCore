#ifndef _JIRAK_CORE_UTILS_DATA_H
#define _JIRAK_CORE_UTILS_DATA_H
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
     @namespace JrDataUtil
     JrStringUtil namespace.
     */
    namespace JrDataUtil {
    /**
     @defgroup jr_data_util data related.
     */
    //@{

        template<class T>
        inline T absDiff(const T& a, const T& b)
        {
            return (a < b) ? (b - a) : (a - b);
        }


        template<typename T>
        inline void swap(T& v1,T& v2)
        {
            T tmp = v2;
            v2 = v1;
            v1 = tmp;
        }


        template<typename T, typename INDEX>
        inline bool checkSortedArray(T a[], INDEX n)
        {
            for (INDEX i = 0; i < n - 1; i++) {
                if (a[i] > a[i + 1]) {
                    return false;
                }
            }

            return true;
        }

    //@}
    }   // end of JrDataUtil

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_UTILS_DATA_H


// <EOF>


