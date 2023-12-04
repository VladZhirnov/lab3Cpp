#include <vector>
#include <random>
#include <iostream>
#include <chrono> 


struct stats {
private:
    size_t comparison_count;
    size_t copy_count;
public:
    stats();
    void add_comparison();
    void add_copy();
    size_t get_comparison();
    size_t get_copy();
    void reset() {
        comparison_count = 0;
        copy_count = 0;
    }

    void print() const {
        std::cout << "Comparison Count: " << comparison_count << std::endl;
        std::cout << "Copy Count: " << copy_count << std::endl;
    }
};

stats::stats() {
    comparison_count = 0;
    copy_count = 0;
}

void stats::add_comparison() {
    comparison_count++;
}

void stats::add_copy() {
    copy_count++;
}

size_t stats::get_comparison() {
    return comparison_count;
}

size_t stats::get_copy() {
    return copy_count;
}


stats bubble_sort(std::vector<int>& arr) {
    stats s;
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            s.add_comparison();
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                s.add_copy();
            }
        }
    }
    return s;
}


size_t partition(std::vector<int>& arr, size_t low, size_t high, stats& s) {
    int pivot = arr[low + (high - low) / 2];
    size_t i = low - 1;
    size_t j = high + 1;

    while (true) {
        do {
            ++i;
            s.add_comparison();
        } while (arr[i] < pivot);

        do {
            --j;
            s.add_comparison();
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }

        std::swap(arr[i], arr[j]);
        s.add_copy();
    }
}

void quick_sort_recursive(std::vector<int>& arr, size_t low, size_t high, stats& s) {
    if (low < high) {
        size_t pivot_index = partition(arr, low, high, s);

        quick_sort_recursive(arr, low, pivot_index, s);
        quick_sort_recursive(arr, pivot_index + 1, high, s);
    }
}

stats quick_sort(std::vector<int>& arr) {
    stats s;
    quick_sort_recursive(arr, 0, arr.size() - 1, s);
    return s;
}


void heapify(std::vector<int>& arr, size_t n, size_t i, stats& s) {
    size_t largest = i;
    size_t left = 2 * i + 1;  // Потомок слева
    size_t right = 2 * i + 2; // Потомок справа

    if (left < n && arr[left] > arr[largest]) {
        s.add_comparison();
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        s.add_comparison();
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        s.add_copy();

        heapify(arr, n, largest, s);
    }
}

stats heap_sort(std::vector<int>& arr) {
    size_t n = arr.size();
    stats s;

    // Построение max-heap
    for (size_t i = n / 2 - 1; i != SIZE_MAX; --i) {
        heapify(arr, n, i, s);
    }

    // Извлечение максимального элемента и перестановка его в конец
    for (size_t i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        s.add_copy();

        heapify(arr, i, 0, s);
    }

    return s;
}

void my_iota(std::vector<int>& v, int start) {
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = start++;
    }
}


void sorted_array(size_t size, int index) {
    std::vector<int> arr(size);
    stats s;
    s.reset();
    my_iota(arr, 1);
    if (index == 1){
        s = bubble_sort(arr);
    }
    else if (index == 2) {
        s = quick_sort(arr);
    }
    else {
        s = heap_sort(arr);
    }
    std::cout << " Sorted Array of Size " << size << ":" << std::endl;
    s.print();
    std::cout << "----------------------" << std::endl;
}

void reverse_sorted_array(size_t size, int index) {
    std::vector<int> arr(size);
    stats s;
    s.reset();
    my_iota(arr, 1);

    for (size_t i = 0; i < size / 2; ++i) {
        std::swap(arr[i], arr[size - i - 1]);
    }

    if (index == 1) {
        s = bubble_sort(arr);
    }
    else if (index == 2) {
        s = quick_sort(arr);
    }
    else {
        s = heap_sort(arr);
    }

    std::cout << " Reverse Sorted Array of Size " << size << ":" << std::endl;
    s.print();
    std::cout << "----------------------" << std::endl;
}

void random_experiment(const std::vector<size_t>& array_sizes, int index) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    for (auto size : array_sizes) {
        std::cout << " Array Size: " << size << std::endl;
        size_t sum_comparison = 0;
        size_t sum_copy = 0;
        for (int experiment = 0; experiment < 100; ++experiment) {
            std::vector<int> arr(size);
            my_iota(arr, 1);

            // Перемешиваем массив случайным образом
            std::shuffle(arr.begin(), arr.end(), generator);

            // Запускаем сортировку
            stats s;
            if (index == 1) {
                s = bubble_sort(arr);
            }
            else if (index == 2) {
                s = quick_sort(arr);
            }
            else {
                s = heap_sort(arr);
            }
            sum_comparison += s.get_comparison();
            sum_copy += s.get_copy();
        }
        double avg_comparison = sum_comparison / 100;
        double avg_copy = sum_copy / 100;
        std::cout << " Average comparison :" << avg_comparison << std::endl;
        std::cout << " Average copy :" << avg_copy << std::endl;
        std::cout << "----------------------" << std::endl;
    }
}