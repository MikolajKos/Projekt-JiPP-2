#include <gtest/gtest.h>
#include <stdexcept>
#include "../src/smartArray/SmartArray.h"

TEST(SmartArrayTest, AtThrowsOutOfRange) {
    SmartArray<int> arr;
    arr.pushBack(10);
    arr.pushBack(20);
    EXPECT_EQ(arr.at(0), 10);
    EXPECT_EQ(arr.at(1), 20);
    EXPECT_THROW(arr.at(2), std::out_of_range);
}

TEST(SmartArrayTest, OperatorIndexReturnsValueWithoutCheck) {
    SmartArray<int> arr;
    arr.pushBack(42);
    EXPECT_EQ(arr[0], 42);
    // Nie testujemy zachowania poza zakresem bo nie jest okreœlone
}

TEST(SmartArrayTest, IsEmptyWorksCorrectly) {
    SmartArray<int> arr;
    EXPECT_TRUE(arr.isEmpty());
    arr.pushBack(1);
    EXPECT_FALSE(arr.isEmpty());
    arr.popBack();
    EXPECT_TRUE(arr.isEmpty());
}

TEST(SmartArrayTest, SizeReturnsCorrectValue) {
    SmartArray<int> arr;
    EXPECT_EQ(arr.size(), 0u);
    arr.pushBack(1);
    arr.pushBack(2);
    EXPECT_EQ(arr.size(), 2u);
}

TEST(SmartArrayTest, CapacityReturnsReservedSize) {
    SmartArray<int> arr;
    arr.reserve(10);
    EXPECT_GE(arr.capacity(), 10u);
}

TEST(SmartArrayTest, ReserveIncreasesCapacityButNotSize) {
    SmartArray<int> arr;
    arr.pushBack(5);
    unsigned oldSize = arr.size();
    arr.reserve(100);
    EXPECT_GE(arr.capacity(), 100u);
    EXPECT_EQ(arr.size(), oldSize);
}

TEST(SmartArrayTest, ResizeDecreasesSize) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.pushBack(3);
    arr.resize(2);
    EXPECT_EQ(arr.size(), 2u);
}

TEST(SmartArrayTest, ResizeIncreasesSizeDefaultValue) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.resize(3);
    EXPECT_EQ(arr.size(), 3u);
    EXPECT_EQ(arr[0], 1);
    // arr[1] i arr[2] mog¹ mieæ dowolne wartoœci (niezainicjalizowane)
}

TEST(SmartArrayTest, ResizeIncreasesSizeWithElem) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.resize(3, 7);
    EXPECT_EQ(arr.size(), 3u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 7);
    EXPECT_EQ(arr[2], 7);
}

TEST(SmartArrayTest, ClearResetsSizeButNotCapacity) {
    SmartArray<int> arr;
    arr.reserve(10);
    arr.pushBack(5);
    arr.pushBack(10);
    arr.clear();
    EXPECT_EQ(arr.size(), 0u);
    EXPECT_GE(arr.capacity(), 10u);
}

TEST(SmartArrayTest, InsertThrowsOnOutOfRange) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(2);
    EXPECT_THROW(arr.insert(3, 100), std::out_of_range);
}

TEST(SmartArrayTest, InsertAddsElementAtIndex) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(3);
    arr.insert(1, 2);
    EXPECT_EQ(arr.size(), 3u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(SmartArrayTest, EraseThrowsOnOutOfRange) {
    SmartArray<int> arr;
    arr.pushBack(1);
    EXPECT_THROW(arr.erase(1), std::out_of_range);
}

TEST(SmartArrayTest, EraseRemovesElementAtIndex) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.pushBack(3);
    arr.erase(1);
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(SmartArrayTest, EraseMultipleThrowsOnOutOfRange) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(2);
    EXPECT_THROW(arr.erase(1, 2), std::out_of_range);
}

TEST(SmartArrayTest, EraseMultipleRemovesElements) {
    SmartArray<int> arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.pushBack(3);
    arr.pushBack(4);
    arr.erase(1, 2);
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 4);
}

TEST(SmartArrayTest, PushBackAddsElementToEnd) {
    SmartArray<int> arr;
    arr.pushBack(5);
    EXPECT_EQ(arr.size(), 1u);
    EXPECT_EQ(arr[0], 5);
}

TEST(SmartArrayTest, PopBackRemovesLastElement) {
    SmartArray<int> arr;
    arr.pushBack(5);
    arr.pushBack(10);
    arr.popBack();
    EXPECT_EQ(arr.size(), 1u);
    EXPECT_EQ(arr[0], 5);
}
