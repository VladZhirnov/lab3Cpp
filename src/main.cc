#include <functions/header.h>
#include <iostream>
#include <vector>


int main(){
    const std::vector<size_t> array_sizes = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000 };
    random_experiment(array_sizes, 3);
    for (auto size : array_sizes) {
        //sorted_array(size, 2);
        //reverse_sorted_array(size, 3);
    }
}