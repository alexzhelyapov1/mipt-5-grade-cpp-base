#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>

int main() {
    double a, b, c;
    std::cin >> a >> b >> c;

    constexpr double epsilon = std::numeric_limits<double>::epsilon();

    if (std::abs(a) < epsilon) {
        if (std::abs(b) < epsilon) {
            if (std::abs(c) < epsilon) {
                std::cout << "Infinite solutions" << std::endl;
            } else {
                std::cout << "No solutions" << std::endl;
            }
        } else {
            std::cout << std::fixed << std::setprecision(15) << -c / b << std::endl;
        }
    } else {
        double discriminant = b * b - 4 * a * c;
        if (discriminant > epsilon) {
            double sqrt_d = std::sqrt(discriminant);
            double x1 = (-b + sqrt_d) / (2 * a);
            double x2 = (-b - sqrt_d) / (2 * a);
            std::cout << std::fixed << std::setprecision(15) << x1 << std::endl;
            std::cout << std::fixed << std::setprecision(15) << x2 << std::endl;
        } else if (std::abs(discriminant) < epsilon) {
            std::cout << std::fixed << std::setprecision(15) << -b / (2 * a) << std::endl;
        } else {
            std::cout << "No real solutions" << std::endl;
        }
    }

    return 0;
}