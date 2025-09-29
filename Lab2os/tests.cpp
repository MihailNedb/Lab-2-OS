#include <gtest/gtest.h>
#include "thread_functions.h"
#include <vector>
#include <random>

// Тесты для find_max

TEST(FindMaxTest, SingleElement) {
    int arr[] = {42};
    EXPECT_EQ(find_max(arr, 1), 42);
}

TEST(FindMaxTest, NegativeNumbers) {
    int arr[] = {-5, -2, -10, -1};
    EXPECT_EQ(find_max(arr, 4), -1);
}

TEST(FindMaxTest, MixedNumbers) {
    int arr[] = {-3, 0, 15, -8, 7};
    EXPECT_EQ(find_max(arr, 5), 15);
}

TEST(FindMaxTest, AllSameElements) {
    int arr[] = {5, 5, 5, 5};
    EXPECT_EQ(find_max(arr, 4), 5);
}

// Тесты для find_min
TEST(FindMinTest, SingleElement) {
    int arr[] = {-7};
    EXPECT_EQ(find_min(arr, 1), -7);
}

TEST(FindMinTest, PositiveNumbers) {
    int arr[] = {3, 1, 8, 2};
    EXPECT_EQ(find_min(arr, 4), 1);
}

TEST(FindMinTest, MixedNumbers) {
    int arr[] = {0, -5, 10, -15, 20};
    EXPECT_EQ(find_min(arr, 5), -15);
}

// Тесты для calculate_average

TEST(CalculateAverageTest, SingleElement) {
    int arr[] = {10};
    EXPECT_EQ(calculate_average(arr, 1), 10);
}

TEST(CalculateAverageTest, RoundingDown) {
    int arr[] = {1, 2, 3, 4}; // сумма = 10, среднее = 2.5 -> округляется до 2
    EXPECT_EQ(calculate_average(arr, 4), 2);
}

TEST(CalculateAverageTest, NegativeAverage) {
    int arr[] = {-2, -4, -6};
    EXPECT_EQ(calculate_average(arr, 3), -4);
}

TEST(CalculateAverageTest, ZeroAverage) {
    int arr[] = {-5, 0, 5};
    EXPECT_EQ(calculate_average(arr, 3), 0);
}

// Тесты для replace_min_max_with_average

TEST(ReplaceMinMaxWithAverageTest, SingleElement) {
    int arr[] = {10};
    replace_min_max_with_average(arr, 1, 10, 10, 5);
    EXPECT_EQ(arr[0], 5);
}

TEST(ReplaceMinMaxWithAverageTest, MultipleMinMaxOccurrences) {
    int arr[] = {1, 9, 1, 5, 9, 3};
    replace_min_max_with_average(arr, 6, 1, 9, 5);
    int expected[] = {5, 5, 5, 5, 5, 3};
    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(ReplaceMinMaxWithAverageTest, NoReplacementWhenNoMinMax) {
    int arr[] = {2, 3, 4, 5};
    int original[] = {2, 3, 4, 5};
    replace_min_max_with_average(arr, 4, 1, 9, 5);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(arr[i], original[i]);
    }
}

TEST(ReplaceMinMaxWithAverageTest, MinEqualsMax) {
    int arr[] = {5, 5, 5, 5};
    replace_min_max_with_average(arr, 4, 5, 5, 10);
    int expected[] = {10, 10, 10, 10};
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Тесты для ThreadCreating

TEST(ThreadCreatingTest, SingleElement) {
    int arr[] = {100};
    int min_val, max_val, avg_val;
    int result = ThreadCreating(arr, 1, min_val, max_val, avg_val);
    
    EXPECT_EQ(result, 0);
    EXPECT_EQ(min_val, 100);
    EXPECT_EQ(max_val, 100);
    EXPECT_EQ(avg_val, 100);
}

TEST(ThreadCreatingTest, LargeArray) {
    const int size = 100;
    int arr[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1; // 1, 2, 3, ..., 100
    }
    
    int min_val, max_val, avg_val;
    int result = ThreadCreating(arr, size, min_val, max_val, avg_val);
    
    EXPECT_EQ(result, 0);
    EXPECT_EQ(min_val, 1);
    EXPECT_EQ(max_val, 100);
    EXPECT_EQ(avg_val, 50); // (1+100)/2 = 50.5 -> округляется до 50
}

TEST(ThreadCreatingTest, AllNegativeNumbers) {
    int arr[] = {-10, -5, -20, -1};
    int min_val, max_val, avg_val;
    int result = ThreadCreating(arr, 4, min_val, max_val, avg_val);
    
    EXPECT_EQ(result, 0);
    EXPECT_EQ(min_val, -20);
    EXPECT_EQ(max_val, -1);
    EXPECT_EQ(avg_val, -9); // (-10-5-20-1)/4 = -36/4 = -9
}

TEST(ThreadCreatingTest, RandomNumbers) {
    int arr[] = {7, -3, 15, 0, -8, 22, 4};
    int min_val, max_val, avg_val;
    int result = ThreadCreating(arr, 7, min_val, max_val, avg_val);
    
    EXPECT_EQ(result, 0);
    EXPECT_EQ(min_val, -8);
    EXPECT_EQ(max_val, 22);
    
    // Проверяем правильность вычислений
    int expected_min = find_min(arr, 7);
    int expected_max = find_max(arr, 7);
    int expected_avg = calculate_average(arr, 7);
    
    EXPECT_EQ(min_val, expected_min);
    EXPECT_EQ(max_val, expected_max);
    EXPECT_EQ(avg_val, expected_avg);
}

// Тесты на граничные случаи
TEST(BoundaryTest, VeryLargeNumbers) {
    int arr[] = {INT_MAX, INT_MIN, 0};
    int min_val, max_val, avg_val;
    int result = ThreadCreating(arr, 3, min_val, max_val, avg_val);
    
    EXPECT_EQ(result, 0);
    EXPECT_EQ(min_val, INT_MIN);
    EXPECT_EQ(max_val, INT_MAX);
    // Среднее может быть вычислено некорректно из-за переполнения, но поток не должен падать
}

TEST(BoundaryTest, ArrayWithZeros) {
    int arr[] = {0, 0, 0, 0};
    int min_val, max_val, avg_val;
    int result = ThreadCreating(arr, 4, min_val, max_val, avg_val);
    
    EXPECT_EQ(result, 0);
    EXPECT_EQ(min_val, 0);
    EXPECT_EQ(max_val, 0);
    EXPECT_EQ(avg_val, 0);
}

// Тест на согласованность результатов
TEST(ConsistencyTest, ThreadResultsMatchDirectCalculations) {
    int arr[] = {3, 7, 2, 8, 1, 9, 4};
    const int size = 7;
    
    // Прямые вычисления
    int direct_min = find_min(arr, size);
    int direct_max = find_max(arr, size);
    int direct_avg = calculate_average(arr, size);
    
    // Вычисления через потоки
    int thread_min, thread_max, thread_avg;
    ThreadCreating(arr, size, thread_min, thread_max, thread_avg);
    
    EXPECT_EQ(thread_min, direct_min);
    EXPECT_EQ(thread_max, direct_max);
    EXPECT_EQ(thread_avg, direct_avg);
}

