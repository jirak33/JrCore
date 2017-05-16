#ifndef _JIRAK_CORE_ALGORITHM_HEAP_SORT_H
#define _JIRAK_CORE_ALGORITHM_HEAP_SORT_H
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
    void satisfyHeap(T a[], size_t index, size_t heapSize)
    {
        if (index < 0 || heapSize < 0 || index > heapSize) {
            return;
        }

        size_t left = 2 * index;
        size_t right = 2 * index + 1;
        size_t largest;

        if (left <= heapSize && a[left] > a[index]) {
            largest = left;
        }
        else {
            largest = index;
        }

        if (right <= heapSize && a[right] > a[largest]) {
            largest = right;
        }

        if (largest != index) {
            JrDataUtil::swap(a[index], a[largest]);
            satisfyHeap<T>(a, largest, heapSize);
        }
    }

    template<typename T>
    void buildHeap(T a[], size_t length)
    {
        size_t heapSize = length;
        size_t i = static_cast<size_t>(length / 2);
        for (; i > 0; i--) {
            satisfyHeap<T>(a, i, heapSize);
        }
    }

    template<typename T>
    void heapSort(T a[], size_t length)
    {
        buildHeap(a, length);
        size_t heapSize = length;
        for (size_t i = heapSize; i > 0; i--) {
            JrDataUtil::swap(a[0], a[heapSize--]);
            satisfyHeap<T>(a, 0, heapSize);
        }
    }

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_ALGORITHM_HEAP_SORT_H


// <EOF>


