#include <cmath>
#include <iomanip>
#include <iostream>
#include <optional>
#include <utility>
#include <variant>

using result_variant = std::variant<std::monostate, double, std::pair<double, double>>;

std::optional<result_variant> solve(double a, double b, double c) {
  constexpr double epsilon = 1e-9;

  if (std::abs(a) < epsilon) {
    if (std::abs(b) < epsilon) {
      if (std::abs(c) < epsilon) {
        return result_variant(std::monostate{});
      }
      return std::nullopt;
    }
    return result_variant(-c / b);
  }

  double discriminant = b * b - 4 * a * c;

  if (discriminant < -epsilon) {
    return std::nullopt;
  }

  if (std::abs(discriminant) < epsilon) {
    return result_variant(-b / (2 * a));
  }

  double sqrt_d = std::sqrt(discriminant);
  return result_variant(
      std::make_pair((-b + sqrt_d) / (2 * a), (-b - sqrt_d) / (2 * a)));
}

int main() {
  double a = 0.0, b = 0.0, c = 0.0;
  std::cin >> a >> b >> c;

  auto result = solve(a, b, c);

  if (!result) {
    std::cout << "No real solutions" << std::endl;
  } else {
    if (std::holds_alternative<std::monostate>(*result)) {
      std::cout << "Infinite solutions" << std::endl;
    } else if (auto *root = std::get_if<double>(&*result)) {
      std::cout << std::fixed << std::setprecision(15) << *root << std::endl;
    } else if (auto *roots = std::get_if<std::pair<double, double>>(&*result)) {
      std::cout << std::fixed << std::setprecision(15) << roots->first << std::endl;
      std::cout << std::fixed << std::setprecision(15) << roots->second
                << std::endl;
    }
  }

  return 0;
}
