#include "tim_sort.hpp"
#include "utils/all.hpp"

#include <gtest/gtest.h>

#define trace(...)

using namespace Jirak;

int gTimSort = 0;

TEST(JrCore_Algorithm_Sorting_Tim, DefaultTest)
{
    const size_t ARRAY_COUNT = 100000000; //< 100 million items.
    std::vector<uint32> array(ARRAY_COUNT);

    JrRandomUtil::init();

    for (size_t i = 0; i < ARRAY_COUNT; i++) {
        array[i] = JrRandomUtil::genNumber<uint32>();
    }

    trace("Jirak::timSortTest... (%ld items)\n", ARRAY_COUNT);
    uint32 tick0 = JrTickUtil::currentTick();
    Jirak::timsort(array.begin(), array.end(), std::less<uint32>());
    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(&array[0], ARRAY_COUNT));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 40000);
}

TEST(JrCore_Algorithm_Sorting_Tim, PartialySorted)
{
    const size_t ARRAY_COUNT = 100000000; //< 100 million items.
    std::vector<uint32> array(ARRAY_COUNT);

    JrRandomUtil::init();

    for (size_t i = 0; i < ARRAY_COUNT; i++) {
        if (i < 10) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else if (ARRAY_COUNT - 10 < i) {
            array[i] = JrRandomUtil::genNumber<uint32>();
        }
        else {
            array[i] = static_cast<uint32>(i);
        }
    }

    trace("Jirak::timSortTest... (%ld items)\n", ARRAY_COUNT);
    uint32 tick0 = JrTickUtil::currentTick();
    Jirak::timsort(array.begin(), array.end(), std::less<uint32>());
    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(&array[0], ARRAY_COUNT));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 40000);
}

TEST(JrCore_Algorithm_Sorting_Tim, ReversedSorted)
{
    const size_t ARRAY_COUNT = 100000000; //< 100 million items.
    std::vector<uint32> array(ARRAY_COUNT);

    JrRandomUtil::init();

    for (size_t i = ARRAY_COUNT - 1; i > 0; i--) {
        array[i] = static_cast<uint32>(i);
    }

    trace("Jirak::timSortTest... (%ld items)\n", ARRAY_COUNT);
    uint32 tick0 = JrTickUtil::currentTick();
    Jirak::timsort(array.begin(), array.end(), std::less<uint32>());
    uint32 tick1 = JrTickUtil::currentTick();
    trace("elapsed-time: %u ms\n", JrTickUtil::diffTick(tick0, tick1));

    EXPECT_TRUE(JrDataUtil::checkSortedArray(&array[0], ARRAY_COUNT));
    EXPECT_TRUE(JrTickUtil::diffTick(tick0, tick1) < 40000);
}


// <EOF>


