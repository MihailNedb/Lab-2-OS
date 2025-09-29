#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    struct ThreadData {
        int* array;
        int size;
        int average;
        int max;
        int min;
    };


    void showmas(int* mas, int size1);
    void get_thread_results(ThreadData& minMaxData, ThreadData& averageData,
        int& min_val, int& max_val, int& average_val);
    void replace_min_max_with_average(int* array, int size, int min_val, int max_val, int average_val);
    int ThreadCreating(int* array, int size, int& min_val, int& max_val, int& average_val);

    int find_max(int* array, int size);
    int find_min(int* array, int size);
    int calculate_average(int* array, int size);

#ifdef __cplusplus
}
#endif