#include <gtest/gtest.h>
#include "thread_functions.h"

TEST(UtilsTest, FindMax) {
    int arr[] = {1, 5, 3, 9, 2};
    EXPECT_EQ(find_max(arr, 5), 9);
}

TEST(UtilsTest, FindMin) {
    int arr[] = {1, 5, -3, 9, 2};
    EXPECT_EQ(find_min(arr, 5), -3);
}

TEST(UtilsTest, CalculateAverage) {
    int arr[] = {2, 4, 6, 8};
    EXPECT_EQ(calculate_average(arr, 4), 5);
}

TEST(UtilsTest, ReplaceMinMaxWithAverage) {
    int arr[] = {1, 9, 3, 9, 1};
    replace_min_max_with_average(arr, 5, 1, 9, 5);
    int expected[] = {5, 5, 3, 5, 5};
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(ThreadTest, ThreadCreatingWorks) {
    int arr[] = {10, 20, 30, 40};
    int min_val, max_val, avg_val;
    ThreadCreating(arr, 4, min_val, max_val, avg_val);

    EXPECT_EQ(min_val, 10);
    EXPECT_EQ(max_val, 40);
    EXPECT_EQ(avg_val, 25);
}
