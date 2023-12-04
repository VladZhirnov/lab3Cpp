#include <functions/header.h>
#include <iostream>
#include <vector>

int main(){
    //Bubble Sort
    std::cout << "Bubble Sort :" << std::endl;
    std::vector<int> arr1 = { 5, 2, 9, 1, 5, 6 };
    std::cout << "Original Array:" << std::endl;
    for (int num : arr1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    stats result1 = bubble_sort(arr1);

    std::cout << "Sorted Array:" << std::endl;
    for (int num : arr1) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Comparison Count: " << result1.get_comparison() << std::endl;
    std::cout << "Copy Count: " << result1.get_copy() << std::endl;
    std::cout << std::endl << std::endl;


    //Quickly Sort
    std::cout << "Quickly Sort :" << std::endl;
    std::vector<int> arr2 = { 5, 2, 9, 1, 5, 6 };

    std::cout << "Original Array:" << std::endl;
    for (int num : arr2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    stats result2 = quick_sort(arr2);

    std::cout << "Sorted Array:" << std::endl;
    for (int num : arr2) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Comparison Count: " << result2.get_comparison() << std::endl;
    std::cout << "Copy Count: " << result2.get_copy() << std::endl;
    std::cout << std::endl;


    //Heap Sort
    std::cout << "Heap Sort :" << std::endl;
    std::vector<int> arr3 = { 5, 2, 9, 1, 5, 6 };

    std::cout << "Original Array:" << std::endl;
    for (int num : arr3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    stats result3 = heap_sort(arr3);

    std::cout << "Sorted Array:" << std::endl;
    for (int num : arr3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Comparison Count: " << result3.get_comparison() << std::endl;
    std::cout << "Copy Count: " << result3.get_copy() << std::endl;
}