#ifndef _JIRAK_CORE_ALGORITHM_RADIX_SORT_H
#define _JIRAK_CORE_ALGORITHM_RADIX_SORT_H
/////////////////////////////////////////////////////////////////////

// MS compatible compilers support #pragma once.
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "../base/type.hpp"
#include "../utils/all.hpp"

#include <algorithm>
#include <iterator>
#include <queue>

/////////////////////////////////////////////////////////////////////

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    // radix sort using base-10 radix.
    template <typename InputIterator, typename OutputIterator>
    void radixSort(InputIterator start, InputIterator end, OutputIterator output)
    {
        const int32 BASE = 10;
        std::queue< typename std::iterator_traits<OutputIterator>::value_type > bucket[BASE];
        uint32 size = end - start;
        typename std::iterator_traits<InputIterator>::value_type max = *std::max_element(start, end);

        std::copy(start, end, output);

        for (uint32 power = 1; max != 0; max /= BASE, power *= BASE) {
            for (OutputIterator it = output; it != output + size; it++) {
                uint32 bucketNumber = (uint32)((*it / power) % BASE);
                bucket[bucketNumber].push(*it);
            }

            OutputIterator it = output;
            for (int32 i = 0; i < BASE; i++) {
                int32 bucketSize = bucket[i].size();
                for (int32 j = 0; j < bucketSize; j++) {
                    *it = bucket[i].front();
                    bucket[i].pop();
                    it++;
                }
            }
        }
    }

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_ALGORITHM_RADIX_SORT_H


// <EOF>


