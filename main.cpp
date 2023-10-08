#include "allocator.hpp"
#include "vector.hpp"

#include <vector>

int factorial(int i) {
    if (i <= 0) {
        return 0;
    }
    if (i == 1) {
        return 1;
    }
    return i * factorial(i - 1);
}

template <class less, class allocator>
void fill_map(std::map<int, int, less, allocator> &inMap) {
    for (int i = 0; i <= 9; i++) {
        inMap[i] = factorial(i);
    }
}


template <class vector>
void fill_vector(vector &inVector) {
    for (int i = 0; i <= 9; i++) {
        inVector.push_back(factorial(i));
    }
}

template <class less, class allocator>
void printMap(const std::map<int, int, less, allocator> &inMap) {
    for (const auto &[key, value] : inMap ){
        std::cout << key << " "  << value << " ";
    }
    std::cout << std::endl;
}

template <class T> 
using my_alloc_vector = my_vector<T, my_alloc::my_allocator<T>>;

int main() {
    {
        std::map<int, int> sample_map;
        fill_map(sample_map);
    }
    {
        my_alloc::map<int, int> sample_map;
        fill_map(sample_map);
        printMap(sample_map);
    }
    {
        my_vector<int> sample_vector;
        fill_vector(sample_vector);
    }
    {
        my_alloc_vector<int> sample_vector;
        fill_vector(sample_vector);
        sample_vector.foreach([](const int &elem) -> void {
           std::cout << elem << " "; 
        });
        std::cout << std::endl;
    }
    return 0;
}