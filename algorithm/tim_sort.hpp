#ifndef _JIRAK_CORE_ALGORITHM_TIM_SORT_H
#define _JIRAK_CORE_ALGORITHM_TIM_SORT_H
/////////////////////////////////////////////////////////////////////

// MS compatible compilers support #pragma once.
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include "../base/type.hpp"
#include "../utils/all.hpp"

#include <vector>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <utility>

#ifdef ENABLE_TIMSORT_LOG
    #include <iostream>
    #define JIRAK_TIMSORT_LOG(expr) (std::clog << "# " << __func__ << ": " << expr << std::endl)
#else
    #define JIRAK_TIMSORT_LOG(expr) ((void)0)
#endif

#if __cplusplus >= 201103L && !DISABLE_STD_MOVE
    #define ENABLE_STD_MOVE 1
#endif

#if ENABLE_STD_MOVE
    #define JIRAK_TIMSORT_MOVE(x) std::move(x)
    #define JIRAK_TIMSORT_MOVE_RANGE(in1, in2, out) std::move((in1), (in2), (out))
    #define JIRAK_TIMSORT_MOVE_BACKWARD(in1, in2, out) std::move_backward((in1), (in2), (out))
#else
    #define JIRAK_TIMSORT_MOVE(x) (x)
    #define JIRAK_TIMSORT_MOVE_RANGE(in1, in2, out) std::copy((in1), (in2), (out))
    #define JIRAK_TIMSORT_MOVE_BACKWARD(in1, in2, out) std::copy_backward((in1), (in2), (out))
#endif

/////////////////////////////////////////////////////////////////////

/**
 @namespace Jirak
 Jirak library default namespace.
 */

namespace Jirak {

    /**
     * Same as std::stable_sort(first, last).
     */
    template<typename RandomAccessIterator>
    inline void timsort(RandomAccessIterator const first, RandomAccessIterator const last);

    /**
     * Same as std::stable_sort(first, last, c).
     */
    template<typename RandomAccessIterator, typename CompFunction>
    inline void timsort(RandomAccessIterator const first, RandomAccessIterator const last, CompFunction compare);


    /////////////////////////////////////////////////////////////////////
    // Implementation

    template<typename Value, typename CompFunction>
    class Compare {
    public:
        typedef Value value_type;
        typedef CompFunction func_type;
        Compare(CompFunction f) : _less(f) {}
        Compare(const Compare<value_type, func_type> &other) : _less(other._less) {}
        bool lt(value_type x, value_type y) { return _less(x, y); }
        bool le(value_type x, value_type y) { return _less(x, y) || !_less(y, x); }
        bool gt(value_type x, value_type y) { return !_less(x, y) && _less(y, x); }
        bool ge(value_type x, value_type y) { return !_less(x, y); }
        func_type &less_function() { return _less; }
    private:
        func_type _less;
    };


    template<typename RandomAccessIterator, typename CompFunction>
    class TimSort {
        typedef RandomAccessIterator iter_t;
        typedef typename std::iterator_traits<iter_t>::value_type value_t;
        typedef typename std::iterator_traits<iter_t>::reference ref_t;
        typedef typename std::iterator_traits<iter_t>::difference_type diff_t;
        typedef Compare<const value_t &, CompFunction> compare_t;

        static const int MIN_MERGE = 32;
        static const int MIN_GALLOP = 7;
        compare_t _comp;
        int _minGallop; // default to MIN_GALLOP.
        std::vector<value_t> _tmp; // temp storage for merges.
        typedef typename std::vector<value_t>::iterator _tmpiter_t;

        struct run {
            iter_t base;
            diff_t len;
            run(iter_t const b, diff_t const l) : base(b), len(l) {}
        };
        std::vector<run> _pending;

        static void sort(iter_t const lo, iter_t const hi, compare_t c)
        {
            assert(lo <= hi);

            diff_t nRemaining = (hi - lo);
            if (nRemaining < 2) {
                return; // nothing to do
            }

            if (nRemaining < MIN_MERGE) {
                diff_t const initRunLen = countRunAndMakeAscending(lo, hi, c);
                JIRAK_TIMSORT_LOG("initRunLen: " << initRunLen);
                binarySort(lo, hi, lo + initRunLen, c);
                return;
            }

            TimSort ts(c);
            diff_t const minRun = minRunLength(nRemaining);
            iter_t cur = lo;
            do {
                diff_t runLen = countRunAndMakeAscending(cur, hi, c);

                if (runLen < minRun) {
                    diff_t const force = std::min(nRemaining, minRun);
                    binarySort(cur, cur + force, cur + runLen, c);
                    runLen = force;
                }

                ts.pushRun(cur, runLen);
                ts.mergeCollapse();

                cur += runLen;
                nRemaining -= runLen;
            } while (nRemaining != 0);

            assert(cur == hi);
            ts.mergeForceCollapse();
            assert(ts._pending.size() == 1);

            JIRAK_TIMSORT_LOG("size: " << (hi - lo) << " _tmp.size(): " << ts._tmp.size() << " _pending.size(): " << ts._pending.size());
        }

        static void binarySort(iter_t const lo, iter_t const hi, iter_t start, compare_t compare)
        {
            assert(lo <= start && start <= hi);

            if (start == lo) {
                ++start;
            }

            for (; start < hi; ++start) {
                assert(lo <= start);
                /*const*/ value_t pivot = JIRAK_TIMSORT_MOVE(*start);

                iter_t const pos = std::upper_bound(lo, start, pivot, compare.less_function());
                for (iter_t p = start; p > pos; --p) {
                    *p = JIRAK_TIMSORT_MOVE(*(p - 1));
                }
                *pos = JIRAK_TIMSORT_MOVE(pivot);
            }
        }

        static diff_t countRunAndMakeAscending(iter_t const lo, iter_t const hi, compare_t compare)
        {
            assert(lo < hi);

            iter_t runHi = lo + 1;
            if (runHi == hi) {
                return 1;
            }

            if (compare.lt(*(runHi++), *lo)) { // descending
                while (runHi < hi && compare.lt(*runHi, *(runHi - 1))) {
                    ++runHi;
                }
                std::reverse(lo, runHi);
            }
            else { // ascending
                while (runHi < hi && compare.ge(*runHi, *(runHi - 1))) {
                    ++runHi;
                }
            }

            return runHi - lo;
        }

        static diff_t minRunLength(diff_t n)
        {
            assert(n >= 0);

            diff_t r = 0;
            while (n >= MIN_MERGE) {
                r |= (n & 1);
                n >>= 1;
            }
            return n + r;
        }

        TimSort(compare_t c) : _comp(c), _minGallop(MIN_GALLOP) {}

        void pushRun(iter_t const runBase, diff_t const runLen)
        {
            _pending.push_back(run(runBase, runLen));
        }

        void mergeCollapse()
        {
            while (_pending.size() > 1) {
                diff_t n = _pending.size() - 2;

                if ((n > 0 && _pending[n - 1].len <= _pending[n].len + _pending[n + 1].len) ||
                    (n > 1 && _pending[n - 2].len <= _pending[n - 1].len + _pending[n].len)) {
                    if (_pending[n - 1].len < _pending[n + 1].len) {
                        --n;
                    }
                    mergeAt(n);
                }
                else if (_pending[n].len <= _pending[n + 1].len) {
                    mergeAt(n);
                }
                else {
                    break;
                }
            }
        }

        void mergeForceCollapse()
        {
            while (_pending.size() > 1) {
                diff_t n = _pending.size() - 2;

                if (n > 0 && _pending[n - 1].len < _pending[n + 1].len) {
                    --n;
                }
                mergeAt(n);
            }
        }

        void mergeAt(diff_t const i)
        {
            diff_t const stackSize = _pending.size();
            assert(stackSize >= 2);
            assert(i >= 0);
            assert(i == stackSize - 2 || i == stackSize - 3);

            iter_t base1 = _pending[i].base;
            diff_t len1 = _pending[i].len;
            iter_t base2 = _pending[i + 1].base;
            diff_t len2 = _pending[i + 1].len;

            assert(len1 > 0 && len2 > 0);
            assert(base1 + len1 == base2);

            _pending[i].len = len1 + len2;

            if (i == stackSize - 3) {
                _pending[i + 1] = _pending[i + 2];
            }

            _pending.pop_back();

            diff_t const k = gallopRight(*base2, base1, len1, 0);
            assert(k >= 0);

            base1 += k;
            len1 -= k;

            if (len1 == 0) {
                return;
            }

            len2 = gallopLeft(*(base1 + (len1 - 1)), base2, len2, len2 - 1);
            assert(len2 >= 0);
            if (len2 == 0) {
                return;
            }

            if (len1 <= len2) {
                mergeLo(base1, len1, base2, len2);
            }
            else {
                mergeHi(base1, len1, base2, len2);
            }
        }

        template <typename Iter>
        diff_t gallopLeft(ref_t key, Iter const base, diff_t const len, diff_t const hint)
        {
            assert(len > 0 && hint >= 0 && hint < len);

            diff_t lastOfs = 0;
            diff_t ofs = 1;

            if (_comp.gt(key, *(base + hint))) {
                diff_t const maxOfs = len - hint;
                while (ofs < maxOfs && _comp.gt(key, *(base + (hint + ofs)))) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;

                    if (ofs <= 0) { // int overflow
                        ofs = maxOfs;
                    }
                }
                if (ofs > maxOfs) {
                    ofs = maxOfs;
                }

                lastOfs += hint;
                ofs += hint;
            }
            else {
                diff_t const maxOfs = hint + 1;
                while (ofs < maxOfs && _comp.le(key, *(base + (hint - ofs)))) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;

                    if (ofs <= 0) {
                        ofs = maxOfs;
                    }
                }
                if (ofs > maxOfs) {
                    ofs = maxOfs;
                }

                diff_t const tmp = lastOfs;
                lastOfs = hint - ofs;
                ofs = hint - tmp;
            }
            assert(-1 <= lastOfs && lastOfs < ofs && ofs <= len);

            return std::lower_bound(base + (lastOfs + 1), base + ofs, key, _comp.less_function()) - base;
        }

        template <typename Iter>
        diff_t gallopRight(ref_t key, Iter const base, diff_t const len, diff_t const hint)
        {
            assert(len > 0 && hint >= 0 && hint < len);

            diff_t ofs = 1;
            diff_t lastOfs = 0;

            if (_comp.lt(key, *(base + hint))) {
                diff_t const maxOfs = hint + 1;
                while (ofs < maxOfs && _comp.lt(key, *(base + (hint - ofs)))) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;

                    if (ofs <= 0) {
                        ofs = maxOfs;
                    }
                }
                if (ofs > maxOfs) {
                    ofs = maxOfs;
                }

                diff_t const tmp = lastOfs;
                lastOfs = hint - ofs;
                ofs = hint - tmp;
            }
            else {
                diff_t const maxOfs = len - hint;
                while (ofs < maxOfs && _comp.ge(key, *(base + (hint + ofs)))) {
                    lastOfs = ofs;
                    ofs = (ofs << 1) + 1;

                    if (ofs <= 0) { // int overflow
                        ofs = maxOfs;
                    }
                }
                if (ofs > maxOfs) {
                    ofs = maxOfs;
                }

                lastOfs += hint;
                ofs += hint;
            }
            assert(-1 <= lastOfs && lastOfs < ofs && ofs <= len);

            return std::upper_bound(base + (lastOfs + 1), base + ofs, key, _comp.less_function()) - base;
        }

        void mergeLo(iter_t const base1, diff_t len1, iter_t const base2, diff_t len2)
        {
            assert(len1 > 0 && len2 > 0 && base1 + len1 == base2);

            copy_to_tmp(base1, len1);

            _tmpiter_t cursor1 = _tmp.begin();
            iter_t cursor2 = base2;
            iter_t dest = base1;

            *(dest++) = JIRAK_TIMSORT_MOVE(*(cursor2++));
            if (--len2 == 0) {
                JIRAK_TIMSORT_MOVE_RANGE(cursor1, cursor1 + len1, dest);
                return;
            }
            if (len1 == 1) {
                JIRAK_TIMSORT_MOVE_RANGE(cursor2, cursor2 + len2, dest);
                *(dest + len2) = JIRAK_TIMSORT_MOVE(*cursor1);
                return;
            }

            int minGallop(_minGallop);

            // outer:
            while (true) {
                int count1 = 0;
                int count2 = 0;

                bool break_outer = false;
                do {
                    assert(len1 > 1 && len2 > 0);

                    if (_comp.lt(*cursor2, *cursor1)) {
                        *(dest++) = JIRAK_TIMSORT_MOVE(*(cursor2++));
                        ++count2;
                        count1 = 0;
                        if (--len2 == 0) {
                            break_outer = true;
                            break;
                        }
                    }
                    else {
                        *(dest++) = JIRAK_TIMSORT_MOVE(*(cursor1++));
                        ++count1;
                        count2 = 0;
                        if (--len1 == 1) {
                            break_outer = true;
                            break;
                        }
                    }
                } while ((count1 | count2) < minGallop);
                if (break_outer) {
                    break;
                }

                do {
                    assert(len1 > 1 && len2 > 0);

                    count1 = gallopRight(*cursor2, cursor1, len1, 0);
                    if (count1 != 0) {
                        JIRAK_TIMSORT_MOVE_BACKWARD(cursor1, cursor1 + count1, dest + count1);
                        dest += count1;
                        cursor1 += count1;
                        len1 -= count1;

                        if (len1 <= 1) {
                            break_outer = true;
                            break;
                        }
                    }
                    *(dest++) = JIRAK_TIMSORT_MOVE(*(cursor2++));
                    if (--len2 == 0) {
                        break_outer = true;
                        break;
                    }

                    count2 = gallopLeft(*cursor1, cursor2, len2, 0);
                    if (count2 != 0) {
                        JIRAK_TIMSORT_MOVE_RANGE(cursor2, cursor2 + count2, dest);
                        dest += count2;
                        cursor2 += count2;
                        len2 -= count2;
                        if (len2 == 0) {
                            break_outer = true;
                            break;
                        }
                    }
                    *(dest++) = JIRAK_TIMSORT_MOVE(*(cursor1++));
                    if (--len1 == 1) {
                        break_outer = true;
                        break;
                    }

                    --minGallop;
                } while ((count1 >= MIN_GALLOP) | (count2 >= MIN_GALLOP));

                if (break_outer) {
                    break;
                }

                if (minGallop < 0) {
                    minGallop = 0;
                }
                minGallop += 2;
            } // end of "outer" loop

            _minGallop = std::min(minGallop, 1);

            if (len1 == 1) {
                assert(len2 > 0);
                JIRAK_TIMSORT_MOVE_RANGE(cursor2, cursor2 + len2, dest);
                *(dest + len2) = JIRAK_TIMSORT_MOVE(*cursor1);
            }
            else {
                assert(len1 != 0 && "Comparison function violates its general contract");
                assert(len2 == 0);
                assert(len1 > 1);
                JIRAK_TIMSORT_MOVE_RANGE(cursor1, cursor1 + len1, dest);
            }
        }

        void mergeHi(iter_t const base1, diff_t len1, iter_t const base2, diff_t len2)
        {
            assert(len1 > 0 && len2 > 0 && base1 + len1 == base2);

            copy_to_tmp(base2, len2);

            iter_t cursor1 = base1 + (len1 - 1);
            _tmpiter_t cursor2 = _tmp.begin() + (len2 - 1);
            iter_t dest = base2 + (len2 - 1);

            *(dest--) = JIRAK_TIMSORT_MOVE(*(cursor1--));
            if (--len1 == 0) {
                JIRAK_TIMSORT_MOVE_RANGE(_tmp.begin(), _tmp.begin() + len2, dest - (len2 - 1));
                return;
            }
            if (len2 == 1) {
                dest -= len1;
                cursor1 -= len1;
                JIRAK_TIMSORT_MOVE_BACKWARD(cursor1 + 1, cursor1 + (1 + len1), dest + (1 + len1));
                *dest = JIRAK_TIMSORT_MOVE(*cursor2);
                return;
            }

            int minGallop(_minGallop);

            // outer:
            while (true) {
                int count1 = 0;
                int count2 = 0;

                bool break_outer = false;
                do {
                    assert(len1 > 0 && len2 > 1);

                    if (_comp.lt(*cursor2, *cursor1)) {
                        *(dest--) = JIRAK_TIMSORT_MOVE(*(cursor1--));
                        ++count1;
                        count2 = 0;
                        if (--len1 == 0) {
                            break_outer = true;
                            break;
                        }
                    }
                    else {
                        *(dest--) = JIRAK_TIMSORT_MOVE(*(cursor2--));
                        ++count2;
                        count1 = 0;
                        if (--len2 == 1) {
                            break_outer = true;
                            break;
                        }
                    }
                } while ((count1 | count2) < minGallop);
                if (break_outer) {
                    break;
                }

                do {
                    assert(len1 > 0 && len2 > 1);

                    count1 = len1 - gallopRight(*cursor2, base1, len1, len1 - 1);
                    if (count1 != 0) {
                        dest -= count1;
                        cursor1 -= count1;
                        len1 -= count1;
                        JIRAK_TIMSORT_MOVE_BACKWARD(cursor1 + 1, cursor1 + (1 + count1), dest + (1 + count1));

                        if (len1 == 0) {
                            break_outer = true;
                            break;
                        }
                    }
                    *(dest--) = JIRAK_TIMSORT_MOVE(*(cursor2--));
                    if (--len2 == 1) {
                        break_outer = true;
                        break;
                    }

                    count2 = len2 - gallopLeft(*cursor1, _tmp.begin(), len2, len2 - 1);
                    if (count2 != 0) {
                        dest -= count2;
                        cursor2 -= count2;
                        len2 -= count2;
                        JIRAK_TIMSORT_MOVE_RANGE(cursor2 + 1, cursor2 + (1 + count2), dest + 1);
                        if (len2 <= 1) {
                            break_outer = true;
                            break;
                        }
                    }
                    *(dest--) = JIRAK_TIMSORT_MOVE(*(cursor1--));
                    if (--len1 == 0) {
                        break_outer = true;
                        break;
                    }

                    minGallop--;
                } while ((count1 >= MIN_GALLOP) | (count2 >= MIN_GALLOP));
                if (break_outer) {
                    break;
                }

                if (minGallop < 0) {
                    minGallop = 0;
                }
                minGallop += 2;
            } // end of "outer" loop

            _minGallop = std::min(minGallop, 1);

            if (len2 == 1) {
                assert(len1 > 0);
                dest -= len1;
                JIRAK_TIMSORT_MOVE_BACKWARD(cursor1 + (1 - len1), cursor1 + 1, dest + (1 + len1));
                *dest = JIRAK_TIMSORT_MOVE(*cursor2);
            }
            else {
                assert(len2 != 0 && "Comparison function violates its general contract");
                assert(len1 == 0);
                assert(len2 > 1);
                JIRAK_TIMSORT_MOVE_RANGE(_tmp.begin(), _tmp.begin() + len2, dest - (len2 - 1));
            }
        }

        void copy_to_tmp(iter_t const begin, diff_t const len)
        {
            _tmp.clear();
            _tmp.reserve(len);
            JIRAK_TIMSORT_MOVE_RANGE(begin, begin + len, std::back_inserter(_tmp));
        }

        // the only interface is the friend timsort() function
        template <typename IterT, typename LessT> friend void timsort(IterT first, IterT last, LessT c);
    };


    template<typename RandomAccessIterator>
    inline void timsort(RandomAccessIterator const first, RandomAccessIterator const last)
    {
        typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
        timsort(first, last, std::less<value_type>());
    }

    template<typename RandomAccessIterator, typename CompFunction>
    inline void timsort(RandomAccessIterator const first, RandomAccessIterator const last, CompFunction compare)
    {
        TimSort<RandomAccessIterator, CompFunction>::sort(first, last, compare);
    }

}   // end of Jirak

#undef JIRAK_TIMSORT_LOG
#undef JIRAK_TIMSORT_MOVE
#undef JIRAK_TIMSORT_MOVE_RANGE
#undef JIRAK_TIMSORT_MOVE_BACKWARD

/////////////////////////////////////////////////////////////////////
#endif  // _JIRAK_CORE_ALGORITHM_TIM_SORT_H


// <EOF>


