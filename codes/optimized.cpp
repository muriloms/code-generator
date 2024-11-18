
#include <iostream>
#include <vector>
#include <chrono>
#include <limits>

// Linear Congruential Generator
unsigned int lcg(unsigned int &seed, const unsigned int a = 1664525, const unsigned int c = 1013904223, const unsigned int m = 1u << 32) {
    // Update seed and return new value
    seed = (a * seed + c) % m;
    return seed;
}

// Calculate the maximum subarray sum
int max_subarray_sum(const int n, unsigned int seed, const int min_val, const int max_val) {
    std::vector<int> random_numbers(n);
    const int range = max_val - min_val + 1;
    
    // Generate random numbers in specified range and store in random_numbers
    for (int i = 0; i < n; ++i) {
        random_numbers[i] = static_cast<int>(lcg(seed) % range) + min_val;
    }
    
    int max_sum = std::numeric_limits<int>::min();
    for (int i = 0; i < n; ++i) {
        int current_sum = 0;
        for (int j = i; j < n; ++j) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum) max_sum = current_sum;
        }
    }
    return max_sum;
}

// Calculate the total maximum subarray sum over 20 different runs
int total_max_subarray_sum(const int n, unsigned int initial_seed, const int min_val, const int max_val) {
    int total_sum = 0;
    for (int i = 0; i < 20; ++i) {
        unsigned int seed = lcg(initial_seed);
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return total_sum;
}

int main() {
    const int n = 10000;
    const unsigned int initial_seed = 42;
    const int min_val = -10;
    const int max_val = 10;
    
    auto start_time = std::chrono::high_resolution_clock::now();
    int result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
