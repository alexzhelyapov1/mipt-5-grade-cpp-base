#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iomanip>

int main() {
    constexpr size_t max_size = 1000;
    double data[max_size];
    size_t count = 0;

    while (count < max_size && std::cin >> data[count]) {
        ++count;
    }

    if (count == 0) {
        return 0;
    }

    double min_val = data[0];
    double max_val = data[0];
    double sum = 0.0;

    for (size_t i = 0; i < count; ++i) {
        if (data[i] < min_val) {
            min_val = data[i];
        }

        if (data[i] > max_val) {
            max_val = data[i];
        }

        sum += data[i];
    }

    const double mean = sum / count;

    double sum_sq_diff = 0.0;
    for (size_t i = 0; i < count; ++i) {
        sum_sq_diff += (data[i] - mean) * (data[i] - mean);
    }
    const double std_dev = std::sqrt(sum_sq_diff / count);

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Max: " << max_val << std::endl;
    std::cout << "Min: " << min_val << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Standard Deviation: " << std_dev << std::endl;

    return 0;
}