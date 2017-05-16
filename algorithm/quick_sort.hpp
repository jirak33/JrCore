#ifndef _JIRAK_CORE_ALGORITHM_QUICK_SORT_H
#define _JIRAK_CORE_ALGORITHM_QUICK_SORT_H
/////////////////////////////////////////////////////////////////////

// MS compatible compilers support #pragma once.
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "../base/type.hpp"
#include "../base/stack.hpp"
#include "../utils/all.hpp"

#include "insertion_sort.hpp"

#include <cassert>
#include <iostream>

/////////////////////////////////////////////////////////////////////

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    template<typename T, typename INDEX>
    INDEX partitionNormal(T a[], INDEX left, INDEX right)
    {
        T pivotValue = a[right];

        INDEX storeIndex = left;

        for (INDEX i = left; i < right; i++) {
            if (a[i] < pivotValue) {
                if (i != storeIndex) {
                    JrDataUtil::swap(a[storeIndex], a[i]);
                }
                storeIndex++;
            }
        }

        if (right != storeIndex) {
            JrDataUtil::swap(a[right], a[storeIndex]);
        }

        return storeIndex;
    }

    template<typename T, typename INDEX>
    void quickSortNormal(JrStack<INDEX>* S, T a[], INDEX left, INDEX right)
    {
        S->init();
        S->push(right);
        S->push(left);

        while (!S->isEmpty()) {
            INDEX l = S->pop();
            INDEX r = S->pop();

            if (l < 0 || l >= std::numeric_limits<INDEX>::max()) {
                continue;
            }

            if (r < 0 || r >= std::numeric_limits<INDEX>::max()) {
                continue;
            }

            if (l < r) {
                INDEX q = partitionNormal(a, l, r);
                if (l < q - 1 && q > 0) {
                    S->push(static_cast<INDEX>(q - 1));
                    S->push(l);
                }

                if (q + 1 < r) {
                    S->push(r);
                    S->push(static_cast<INDEX>(q + 1));
                }
            }
        }
    }


    /////////////////////////////////////////////////////////////////////

    template<typename INDEX>
    struct PivotInfo {
      INDEX left, right;
    };


    template<typename T, typename INDEX>
    T findMedianPivot(T a[], INDEX left, INDEX right)
    {
        INDEX mid = ((left + right) >> 1);

        // a[Left] <= a[cenmidter] <= a[right].
        if (a[left] > a[mid]) {
            JrDataUtil::swap(a[left], a[mid]);
        }

        if (a[left] > a[right]) {
            JrDataUtil::swap(a[left], a[right]);
        }

        if (a[mid] > a[right]) {
            JrDataUtil::swap(a[mid], a[right]);
        }

        JrDataUtil::swap(a[mid], a[right - 1]); //< 피봇된 수를 'right - 1'의 위치에 있는 수와 swap.

        assert(right > 0);

        return a[right - 1];
    }

    template<typename T, typename INDEX>
    PivotInfo<INDEX> partitionMedian(T a[], INDEX left, INDEX right)
    {
        PivotInfo<INDEX> retval = { 0, 0 };

        INDEX i = left;
        INDEX j = right - 1;
        INDEX m = left;
        INDEX n = right - 1;

        T pivot = findMedianPivot(a, left, right);

        // three way partitions.
        while (1) {
            while (i < right && a[++i] < pivot)
                ;

            while (j > left && a[--j] > pivot) {
                if (j == left) {
                    break;
                }
            }

            if (i >= j) {
                break;
            }

            JrDataUtil::swap(a[i], a[j]);

            if (a[i] == pivot) {
                JrDataUtil::swap(a[++m], a[i]);
            }

            if (a[j] == pivot) {
                JrDataUtil::swap(a[--n], a[j]);
            }
        }

        JrDataUtil::swap(a[i], a[right - 1]);
        j = i - 1;
        i = i + 1;

        for (INDEX k = left; k < m; k++, j--) {
            JrDataUtil::swap(a[k], a[j]);
        }

        for (INDEX k = right - 1; k > n; k--, i++) {
            JrDataUtil::swap(a[k], a[i]);
        }

        retval.left = i;
        retval.right = j;

        return retval;        
    }

    template<typename T, typename INDEX>
    void quickSortMedian(JrStack<INDEX>* S, T a[], INDEX left, INDEX right)
    {
        T* start = &a[left];
        INDEX count = right - left + 1;

        S->init();
        S->push(left);
        S->push(right);

        while (!S->isEmpty()) {
            right = S->pop();
            left = S->pop();

            if (left >= right) {
                break;
            }

            PivotInfo<INDEX> pi = partitionMedian(a, left, right);

            if (left < pi.right) {
                S->push(left);
                S->push(pi.right);
            }

            if (pi.left < right) {
                S->push(pi.left);
                S->push(right);
            }
        }

        // insertion-sorting for almost sorted array.
        insertionSort(start, count);
    }


    /////////////////////////////////////////////////////////////////////

    enum QSortPivotType { QS_NORMAL, QS_MEDIAN };

    template<typename T, typename INDEX>
    void quickSort(QSortPivotType type, JrStack<INDEX>* S, T a[], INDEX left, INDEX right)
    {
        if (QS_MEDIAN == type) {
            quickSortMedian<T, INDEX>(S, a, left, right);
        }
        else {
            quickSortNormal<T, INDEX>(S, a, left, right);
        }
    }


    /////////////////////////////////////////////////////////////////////

    template<typename T, typename INDEX>
    INDEX partition(T a[], INDEX p, INDEX r)
    {
        INDEX i = p - 1;
        INDEX j = p;
        while (j < r) {
            if (a[j] <= a[r]) {
                JrDataUtil::swap(a[++i], a[j]);
            }
            j++;
        }
        JrDataUtil::swap(a[++i], a[j]);
        return i;
    }

    template<typename T, typename INDEX>
    void quickSortTailRecursionImpl(T a[], INDEX left, INDEX right)
    {
        if (left < 0 || left >= std::numeric_limits<INDEX>::max()) {
            return;
        }

        if (right < 0 || right >= std::numeric_limits<INDEX>::max()) {
            return;
        }

        while (left < right) {
            INDEX q = partition(a, left, right);
            quickSortTailRecursionImpl(a, left, q - 1);
            left = q + 1;
        }
    }

    template<typename T, typename INDEX>
    void quickSortTailRecursion(T a[], INDEX left, INDEX right)
    {
        quickSortTailRecursionImpl(a, left, right);
    }


    /////////////////////////////////////////////////////////////////////

    template<typename T, typename INDEX>
    void quickSortPureRecursion(T a[], INDEX left, INDEX right)
    {
        if (left < 0 || left >= std::numeric_limits<INDEX>::max()) {
            return;
        }

        if (right < 0 || right >= std::numeric_limits<INDEX>::max()) {
            return;
        }

        if (left < right) {
            INDEX q = partition(a, left, right);
            quickSortPureRecursion(a, left, q - 1);
            quickSortPureRecursion(a, q + 1, right);
        }
    }

}   // end of Jirak

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_ALGORITHM_QUICK_SORT_H


// <EOF>


