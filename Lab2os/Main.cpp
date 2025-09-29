#include <iostream>
#include "thread_functions.h"



int main() {
    int size;
    std::cout << "Enter array size: ";
    std::cin >> size;

    int* array = new int[size];
    std::cout << "Enter array elements: ";

    for (int i = 0; i < size; i++) {
        std::cin >> array[i];
    }

    int min_val, max_val, average_val;
    ThreadCreating(array, size, min_val, max_val, average_val);

    replace_min_max_with_average(array, size, min_val, max_val, average_val);

    showmas(array, size);

    delete[] array;
    system("pause");
    return 0;
}
