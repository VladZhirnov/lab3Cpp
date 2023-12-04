#include <vector>

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


void quick_sort_recursive(std::vector<int>& arr, size_t low, size_t high, stats& s) {
    if (low < high) {
        size_t pivot_index = low + (high - low) / 2;
        int pivot = arr[pivot_index];
        size_t i = low;
        size_t j = high;

        while (i <= j) {
            while (arr[i] < pivot) {
                ++i;
                s.add_comparison();
            }

            while (arr[j] > pivot) {
                --j;
                s.add_comparison();
            }

            if (i <= j) {
                std::swap(arr[i], arr[j]);
                s.add_copy();
                ++i;
                --j;
            }
        }

        quick_sort_recursive(arr, low, j, s);
        quick_sort_recursive(arr, i, high, s);
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
