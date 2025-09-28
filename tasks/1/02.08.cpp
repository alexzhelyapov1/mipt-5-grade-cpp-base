#include <iostream>
#include <vector>
#include <cstddef>

std::size_t get_collatz_length(unsigned long long int n, std::vector<std::size_t>& cache) {
    if (n == 1) {
        return 1;
    }
    if (n < cache.size() && cache[n] != 0) {
        return cache[n];
    }

    std::size_t length;
    if (n % 2 == 0) {
        length = 1 + get_collatz_length(n / 2, cache);
    } else {
        length = 1 + get_collatz_length(3 * n + 1, cache);
    }

    if (n < cache.size()) {
        cache[n] = length;
    }

    return length;
}

int main() {
    constexpr std::size_t limit = 100;
    std::vector<std::size_t> cache(1000000, 0);

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
