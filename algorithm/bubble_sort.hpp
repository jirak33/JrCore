#ifndef _JIRAK_CORE_ALGORITHM_BUBBLE_SORT_H
#define _JIRAK_CORE_ALGORITHM_BUBBLE_SORT_H
/////////////////////////////////////////////////////////////////////

// MS compatible compilers support #pragma once.
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "../base/type.hpp"
#include "../utils/all.hpp"

/////////////////////////////////////////////////////////////////////

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    template<typename T, typename INDEX>
    void bubbleSort(T a[], INDEX size)
    {
        for (INDEX i = 0; i < size; i++) {
            for (INDEX j = i + 1; j < size; j++) {
                if (a[i] > a[j]) {
                    JrDataUtil::swap<T>(a[i], a[j]);
                }
            }
        }
    }

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_ALGORITHM_BUBBLE_SORT_H


// <EOF>


