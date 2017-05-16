#ifndef _JIRAK_CORE_ALGORITHM_RADIX_SORT_H
#define _JIRAK_CORE_ALGORITHM_RADIX_SORT_H
/////////////////////////////////////////////////////////////////////

// MS compatible compilers support #pragma once.
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "../base/type.hpp"
#include "../utils/all.hpp"

#include <cstring>

/////////////////////////////////////////////////////////////////////

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    // a utility function to get maximum value in a[].
    template<typename T>
    inline T getMax(T a[], size_t n)
    {
        T m = a[0];
        for (size_t i = 1; i < n; i++) {
            if (a[i] > m) {
                m = a[i];
            }
        }
        return m;
    }

    // a function to do counting sort of a[] according to the digit represented by exp.
    template<typename T>
    inline void countSort(T a[], size_t n, size_t exp)
    {
        T* output = new T[n]; // output array.
        size_t countArray[10] = { 0 };

        // store count of occurrences in countArray[].
        for (size_t i = 0; i < n; i++) {
            countArray[(a[i] / exp) % 10]++;
        }

        // change count[i] so that countArray[i] now contains actual position of this digit in output[].
        for (size_t i = 1; i < 10; i++) {
            countArray[i] += countArray[i - 1];
        }

        // build the output array.
        for (int32 i = n - 1; i >= 0; i--) {
            output[countArray[(a[i] / exp) % 10] - 1] = a[i];
            countArray[(a[i] / exp) % 10]--;
        }

        ::memcpy(a, output, sizeof(T) * n);
        delete output;
    }

    template<typename T>
    void radixSort(T a[], size_t n)
    {
        // find the maximum number to know number of digits.
        T m = getMax(a, n);

        // do counting sort for every digit. Note that instead of passing digit number, exp is passed. exp is 10^i.
        // where i is current digit number.
        for (size_t exp = 1; m / exp > 0; exp *= 10) {
            countSort<T>(a, n, exp);
        }
    }

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_ALGORITHM_RADIX_SORT_H


// <EOF>


