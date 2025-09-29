#include "thread_functions.h"
#include <iostream>
#include <windows.h>

using namespace std;

DWORD WINAPI min_max_thread(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    int* arr = data->array;
    int size = data->size;

    if (size == 0) {
        data->min = 0;
        data->max = 0;
        return 0;
    }

    int min_val = arr[0];
    int max_val = arr[0];

    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        Sleep(7);
    }

    data->min = min_val;
    data->max = max_val;

    cout << "Min element: " << min_val << endl;
    cout << "Max element: " << max_val << endl;

    return 0;
}

DWORD WINAPI average_thread(LPVOID lpParam) {
    ThreadData* data = (ThreadData*)lpParam;
    int* arr = data->array;
    int size = data->size;

    if (size == 0) {
        data->average = 0;
        return 0;
    }

    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
        Sleep(12);
    }

    int average_val = sum / size;
    data->average = average_val;
    cout << "Average value: " << average_val << endl;

    return 0;
}

void showmas(int* mas, int size1) {
    cout << "Array: ";
    for (int i = 0; i < size1; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
}

void get_thread_results(ThreadData& minMaxData, ThreadData& averageData,
    int& min_val, int& max_val, int& average_val) {
    min_val = minMaxData.min;
    max_val = minMaxData.max;
    average_val = averageData.average;
}

void replace_min_max_with_average(int* array, int size, int min_val, int max_val, int average_val) {
    for (int i = 0; i < size; i++) {
        if (array[i] == min_val || array[i] == max_val) {
            array[i] = average_val;
        }
    }
}

int ThreadCreating(int* array, int size, int& min_val, int& max_val, int& average_val) {
    ThreadData minMaxData{array, size};
    ThreadData averageData{array, size};

    HANDLE hMinMax = CreateThread(NULL, 0, min_max_thread, &minMaxData, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average_thread, &averageData, 0, NULL);

    if (hMinMax == NULL || hAverage == NULL) {
        cout << "Error creating threads!" << endl;
        return 1;
    }

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    get_thread_results(minMaxData, averageData, min_val, max_val, average_val);
    return 0;
}

int find_max(int* array, int size) {
    if (size == 0) return 0;
    int max_val = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max_val) {
            max_val = array[i];
        }
    }
    return max_val;
}

int find_min(int* array, int size) {
    if (size == 0) return 0;
    int min_val = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] < min_val) {
            min_val = array[i];
        }
    }
    return min_val;
}

int calculate_average(int* array, int size) {
    if (size == 0) return 0;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}
