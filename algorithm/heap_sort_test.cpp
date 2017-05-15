#include "heap_sort.hpp"
#include "utils/all.hpp"

#include <gtest/gtest.h>

using namespace Jirak;

int gHeapSort = 0;

TEST(JrCore_Algorithm_Sorting_Heap, DefaultTest)
{
    const size_t ARRAY_COUNT = 10000; //< 10 thousand items.
    uint32* array = new uint32[ARRAY_COUNT];

    JrRandomUtil::init();

    for (size_t i = 0; i < ARRAY_COUNT; i++) {
        array[i] = JrRandomUtil::genNumber<uint32>();
    }

    printf("Jirak::heapSortTest... (%ld items)\n", ARRAY_COUNT);
    uint32 tick0 = JrTickUtil::currentTick();
    Jirak::heapSort<uint32>(array, ARRAY_COUNT);
    uint32 tick1 = JrTickUtil::currentTick();
    printf("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(array, ARRAY_COUNT));

    delete[] array;
}


// <EOF>


