#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <iomanip>

int main() {
    std::vector<double> data;
    double value = 0.0;
    while (std::cin >> value) {
        data.push_back(value);
    }

    if (data.empty()) {
        return 0;
    }

    const auto min_val = *std::min_element(data.begin(), data.end());
    const auto max_val = *std::max_element(data.begin(), data.end());

    const double sum = std::accumulate(data.begin(), data.end(), 0.0);
    const double mean = sum / data.size();

    double sum_sq_diff = 0.0;
    for (const double val : data) {
        sum_sq_diff += (val - mean) * (val - mean);
    }
    const double std_dev = std::sqrt(sum_sq_diff / data.size());

    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Max: " << max_val << std::endl;
    std::cout << "Min: " << min_val << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Standard Deviation: " << std_dev << std::endl;

    return 0;
}