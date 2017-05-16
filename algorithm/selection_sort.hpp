#ifndef _JIRAK_CORE_ALGORITHM_SELECTION_SORT_H
#define _JIRAK_CORE_ALGORITHM_SELECTION_SORT_H
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

    template<typename T>
    void selectionSort(T a[], size_t size)
    {
        size_t minIndex = 0;
        for (size_t i = 0; i < size; i++) {
            minIndex = i;
            for (size_t j = i + 1; j < size; j++) {
                if (a[j] < a[minIndex]) {
                    minIndex = j;
                }
            }
            JrDataUtil::swap(a[i], a[minIndex]);
        }
    }

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_ALGORITHM_SELECTION_SORT_H


// <EOF>


