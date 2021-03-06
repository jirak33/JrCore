#include "bubble_sort.hpp"
#include "utils/all.hpp"

#include <gtest/gtest.h>

#define trace(...)

using namespace Jirak;

int gBubbleSort = 0;

TEST(JrCore_Algorithm_Sorting_Bubble, DefaultTest)
{
    const size_t ARRAY_COUNT = 10000; //< 10 thousand items.
    uint32* array = new uint32[ARRAY_COUNT];

    JrRandomUtil::init();

    for (size_t i = 0; i < ARRAY_COUNT; i++) {
        array[i] = JrRandomUtil::genNumber<uint32>();
    }

    trace("Jirak::bubbleSortTest... (%ld items)\n", ARRAY_COUNT);
    uint32 tick0 = JrTickUtil::currentTick();
    Jirak::bubbleSort<uint32>(array, ARRAY_COUNT);
    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 40000);

    delete[] array;
}


// <EOF>


