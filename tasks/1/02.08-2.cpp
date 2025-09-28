#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstddef>
#include <algorithm>

std::size_t get_collatz_length(
    unsigned long long int n, 
    std::unordered_map<unsigned long long int, std::size_t>& cache) {

    if (cache.count(n)) {
        return cache.at(n);
    }

    unsigned long long int current_n = n;
    std::vector<unsigned long long int> path;

    while (cache.find(current_n) == cache.end()) {
        path.push_back(current_n);
        if (current_n % 2 == 0) {
            current_n /= 2;
        } else {
            current_n = 3 * current_n + 1;
        }
    }

    std::size_t length = cache.at(current_n);
    std::for_each(path.rbegin(), path.rend(), [&](unsigned long long int val) {
        length++;
        cache[val] = length;
    });

    return cache.at(n);
}

int main() {
    constexpr std::size_t limit = 100;
    std::unordered_map<unsigned long long int, std::size_t> cache;
    cache[1] = 1;

    std::size_t max_length = 0;
    std::size_t start_value_for_max_length = 0;

    for (std::size_t i = 1; i <= limit; ++i) {
        std::size_t current_length = get_collatz_length(i, cache);
        if (current_length > max_length) {
            max_length = current_length;
            start_value_for_max_length = i;
        }
    }

    std::cout << "Start value: " << start_value_for_max_length << std::endl;
    std::cout << "Max length: " << max_length << std::endl;

    return 0;
}