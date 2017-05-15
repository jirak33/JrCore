#include "quick_sort.hpp"
#include "utils/all.hpp"

#include <cstdlib>
#include <gtest/gtest.h>

#define trace(...)

using namespace Jirak;

int gQuickSort = 0;

/////////////////////////////////////////////////////////////////////
// QuickSort std::qsort() algorithm.

const size_t ARRAY_COUNT_StdCpp = 100000000; //< 100 million items.

TEST(JrCore_Algorithm_Sorting_QuickStdCpp, DefaultTest)
{   
    uint32* array = new uint32[ARRAY_COUNT_StdCpp];

    JrRandomUtil::init();

    trace("std::qsort... (%ld items)\n", ARRAY_COUNT_StdCpp);

    for (size_t i = 0; i < ARRAY_COUNT_StdCpp; i++) {
        array[i] = JrRandomUtil::genNumber<uint32>();
    }

    uint32 tick0 = JrTickUtil::currentTick();

    std::qsort(array, ARRAY_COUNT_StdCpp, sizeof(uint32),
        [](const void* x, const void* y)
        {
            uint32 arg1 = *static_cast<const uint32*>(x);
            uint32 arg2 = *static_cast<const uint32*>(y);
            if (arg1 < arg2) return -1;
            if (arg1 > arg2) return 1;
            return 0;
        }
    );

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_StdCpp));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 40000);

    delete[] array;
}

TEST(JrCore_Algorithm_Sorting_QuickStdCpp, PartialySorted)
{
    uint32* array = new uint32[ARRAY_COUNT_StdCpp];

    JrRandomUtil::init();

    trace("std::qsort... (%ld items)\n", ARRAY_COUNT_StdCpp);

    for (size_t i = 0; i < ARRAY_COUNT_StdCpp; i++) {
        if (i < 10) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else if (ARRAY_COUNT_StdCpp - 10 < i) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else {
            array[i] = static_cast<uint32>(i);
        }
    }

    uint32 tick0 = JrTickUtil::currentTick();

    std::qsort(array, ARRAY_COUNT_StdCpp, sizeof(uint32),
        [](const void* x, const void* y)
        {
            uint32 arg1 = *static_cast<const uint32*>(x);
            uint32 arg2 = *static_cast<const uint32*>(y);
            if (arg1 < arg2) return -1;
            if (arg1 > arg2) return 1;
            return 0;
        }
    );

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_StdCpp));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 40000);

    delete[] array;
}

TEST(JrCore_Algorithm_Sorting_QuickStdCpp, ReversedSorted)
{
    uint32* array = new uint32[ARRAY_COUNT_StdCpp];

    JrRandomUtil::init();

    trace("std::qsort... (%ld items)\n", ARRAY_COUNT_StdCpp);

    for (size_t i = ARRAY_COUNT_StdCpp - 1; i > 0; i--) {
        array[i] = static_cast<uint32>(i);
    }

    uint32 tick0 = JrTickUtil::currentTick();

    std::qsort(array, ARRAY_COUNT_StdCpp, sizeof(uint32),
        [](const void* x, const void* y)
        {
            uint32 arg1 = *static_cast<const uint32*>(x);
            uint32 arg2 = *static_cast<const uint32*>(y);
            if (arg1 < arg2) return -1;
            if (arg1 > arg2) return 1;
            return 0;
        }
    );

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_StdCpp));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 40000);

    delete[] array;
}


/////////////////////////////////////////////////////////////////////
// QuickSort median-iteration algorithm.

const size_t ARRAY_COUNT_Median = 100000000; //< 100 million items.
const int32 STACK_COUNT_Median = 300;

TEST(JrCore_Algorithm_Sorting_QuickIterationMedian, DefaultTest)
{   
    uint32* array = new uint32[ARRAY_COUNT_Median];
    Jirak::JrStack<size_t>* S = new Jirak::JrStack<size_t>(STACK_COUNT_Median);

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_Median);

    for (size_t i = 0; i < ARRAY_COUNT_Median; i++) {
        array[i] = JrRandomUtil::genNumber<uint32>();
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSort<uint32, size_t>(QS_MEDIAN, S, array, 0, ARRAY_COUNT_Median - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));
    trace("max-stack-depth: %ld\n", S->maxIndexValue());

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_Median));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 15000);

    delete[] array;
    delete S;
}

TEST(JrCore_Algorithm_Sorting_QuickIterationMedian, PartialySorted)
{
    uint32* array = new uint32[ARRAY_COUNT_Median];
    Jirak::JrStack<size_t>* S = new Jirak::JrStack<size_t>(STACK_COUNT_Median);

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_Median);

    for (size_t i = 0; i < ARRAY_COUNT_Median; i++) {
        if (i < 10) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else if (ARRAY_COUNT_Median - 10 < i) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else {
            array[i] = static_cast<uint32>(i);
        }
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSort<uint32, size_t>(QS_MEDIAN, S, array, 0, ARRAY_COUNT_Median - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));
    trace("max-stack-depth: %ld\n", S->maxIndexValue());

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_Median));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 15000);

    delete[] array;
    delete S;
}

TEST(JrCore_Algorithm_Sorting_QuickIterationMedian, ReversedSorted)
{
    uint32* array = new uint32[ARRAY_COUNT_Median];
    Jirak::JrStack<size_t>* S = new Jirak::JrStack<size_t>(STACK_COUNT_Median);

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_Median);

    for (size_t i = ARRAY_COUNT_Median - 1; i > 0; i--) {
        array[i] = static_cast<uint32>(i);
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSort<uint32, size_t>(QS_MEDIAN, S, array, 0, ARRAY_COUNT_Median - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));
    trace("max-stack-depth: %ld\n", S->maxIndexValue());

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_Median));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 15000);

    delete[] array;
    delete S;
}


/////////////////////////////////////////////////////////////////////
// QuickSort normal-iteration algorithm.

const size_t ARRAY_COUNT_Normal = 10000; //< 10 thousand items.
const int32 STACK_COUNT_Normal = 30000;

TEST(JrCore_Algorithm_Sorting_QuickIterationNormal, DefaultTest)
{
    uint32* array = new uint32[ARRAY_COUNT_Normal];
    Jirak::JrStack<size_t>* S = new Jirak::JrStack<size_t>(STACK_COUNT_Normal);

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_Normal);

    for (size_t i = 0; i < ARRAY_COUNT_Normal; i++) {
        array[i] = JrRandomUtil::genNumber<uint32>();
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSort<uint32, size_t>(QS_NORMAL, S, array, 0, ARRAY_COUNT_Normal - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));
    trace("max-stack-depth: %ld\n", S->maxIndexValue());

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_Normal));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 1000);

    delete[] array;
    delete S;
}

TEST(JrCore_Algorithm_Sorting_QuickIterationNormal, PartialySorted)
{
    uint32* array = new uint32[ARRAY_COUNT_Normal];
    Jirak::JrStack<size_t>* S = new Jirak::JrStack<size_t>(STACK_COUNT_Normal);

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_Normal);

    for (size_t i = 0; i < ARRAY_COUNT_Normal; i++) {
        if (i < 10) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else if (ARRAY_COUNT_Normal - 10 < i) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else {
            array[i] = static_cast<uint32>(i);
        }
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSort<uint32, size_t>(QS_NORMAL, S, array, 0, ARRAY_COUNT_Normal - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));
    trace("max-stack-depth: %ld\n", S->maxIndexValue());

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_Normal));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 1000);

    delete[] array;
    delete S;
}

TEST(JrCore_Algorithm_Sorting_QuickIterationNormal, ReversedSorted)
{
    uint32* array = new uint32[ARRAY_COUNT_Normal];
    Jirak::JrStack<size_t>* S = new Jirak::JrStack<size_t>(STACK_COUNT_Normal);

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_Normal);

    for (size_t i = ARRAY_COUNT_Normal - 1; i > 0; i--) {
        array[i] = static_cast<uint32>(i);
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSort<uint32, size_t>(QS_NORMAL, S, array, 0, ARRAY_COUNT_Normal - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));
    trace("max-stack-depth: %ld\n", S->maxIndexValue());

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_Normal));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 1000);

    delete[] array;
    delete S;
}


/////////////////////////////////////////////////////////////////////
// QuickSort tail-recursion algorithm.

const size_t ARRAY_COUNT_TailRecursion = 10000; //< 10 thousand items.

TEST(JrCore_Algorithm_Sorting_QuickTailRecursion, DefaultTest)
{
    uint32* array = new uint32[ARRAY_COUNT_TailRecursion];

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_TailRecursion);

    for (size_t i = 0; i < ARRAY_COUNT_TailRecursion; i++) {
        array[i] = JrRandomUtil::genNumber<uint32>();
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSortTailRecursion<uint32, size_t>(array, 0, ARRAY_COUNT_TailRecursion - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_TailRecursion));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 1000);

    delete[] array;
}

TEST(JrCore_Algorithm_Sorting_QuickTailRecursion, PartialySorted)
{
    uint32* array = new uint32[ARRAY_COUNT_TailRecursion];

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_TailRecursion);

    for (size_t i = 0; i < ARRAY_COUNT_TailRecursion; i++) {
        if (i < 10) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else if (ARRAY_COUNT_TailRecursion - 10 < i) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else {
            array[i] = static_cast<uint32>(i);
        }
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSortTailRecursion<uint32, size_t>(array, 0, ARRAY_COUNT_TailRecursion - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_TailRecursion));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 1000);

    delete[] array;
}

TEST(JrCore_Algorithm_Sorting_QuickTailRecursion, ReversedSorted)
{
    uint32* array = new uint32[ARRAY_COUNT_TailRecursion];

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_TailRecursion);

    for (size_t i = ARRAY_COUNT_TailRecursion - 1; i > 0; i--) {
        array[i] = static_cast<uint32>(i);
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSortTailRecursion<uint32, size_t>(array, 0, ARRAY_COUNT_TailRecursion - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_TailRecursion));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 1000);

    delete[] array;
}


/////////////////////////////////////////////////////////////////////
// QuickSort pure-recursion algorithm.

const size_t ARRAY_COUNT_PureRecursion = 10000; //< 10 thousand items.

TEST(JrCore_Algorithm_Sorting_QuickPureRecursion, DefaultTest)
{
    uint32* array = new uint32[ARRAY_COUNT_PureRecursion];

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_PureRecursion);

    for (size_t i = 0; i < ARRAY_COUNT_PureRecursion; i++) {
        array[i] = JrRandomUtil::genNumber<uint32>();
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSortPureRecursion<uint32, size_t>(array, 0, ARRAY_COUNT_PureRecursion - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_PureRecursion));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 1000);

    delete[] array;
}

TEST(JrCore_Algorithm_Sorting_QuickPureRecursion, PartialySorted)
{
    uint32* array = new uint32[ARRAY_COUNT_PureRecursion];

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_PureRecursion);

    for (size_t i = 0; i < ARRAY_COUNT_PureRecursion; i++) {
        if (i < 10) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else if (ARRAY_COUNT_PureRecursion - 10 < i) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else {
            array[i] = static_cast<uint32>(i);
        }
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSortPureRecursion<uint32, size_t>(array, 0, ARRAY_COUNT_PureRecursion - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_PureRecursion));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 1000);

    delete[] array;
}

TEST(JrCore_Algorithm_Sorting_QuickPureRecursion, ReversedSorted)
{
    uint32* array = new uint32[ARRAY_COUNT_PureRecursion];

    JrRandomUtil::init();

    trace("Jirak::quickSortTest... (%ld items)\n", ARRAY_COUNT_PureRecursion);

    for (size_t i = ARRAY_COUNT_PureRecursion - 1; i > 0; i--) {
        array[i] = static_cast<uint32>(i);
    }

    uint32 tick0 = JrTickUtil::currentTick();

    Jirak::quickSortPureRecursion<uint32, size_t>(array, 0, ARRAY_COUNT_PureRecursion - 1);

    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT_PureRecursion));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 1000);

    delete[] array;
}


// <EOF>


