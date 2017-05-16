#ifndef _JIRAK_CORE_ALGORITHM_INSERTION_SORT_H
#define _JIRAK_CORE_ALGORITHM_INSERTION_SORT_H
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
    void insertionSort(T a[], size_t size)
    {
	    for (size_t i = 1; i < size; i++) {
		    T tmp = a[i];
		    size_t j = i - 1;
		    while (j >= 0 && a[j] > tmp) {
			    a[j + 1] = a[j];
			    j--;
		    }
		    a[j + 1] = tmp;
	    }
    }

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_ALGORITHM_INSERTION_SORT_H


// <EOF>


