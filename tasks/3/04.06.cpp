#include <array>
#include <cassert>
#include <numbers>

consteval double abs_diff(double a, double b) {
  double diff = a - b;
  return diff < 0 ? -diff : diff;
}

consteval double calculate_pi(double epsilon) {
  double sum = 0.0;
  double sign = 1.0;
  double denominator = 1.0;
  double term = 1.0;

  while (term >= epsilon) {
    sum += sign * term;
    sign = -sign;
    denominator += 2.0;
    term = 1.0 / denominator;
  }

  return sum * 4.0;
}

consteval double calculate_e(double epsilon) {
  double sum = 1.0;
  double term = 1.0;
  double n = 1.0;

  while (term >= epsilon) {
    term /= n;
    if (term < epsilon)
      break;
    sum += term;
    n += 1.0;
  }

  return sum;
}

int main() {
  constexpr std::array<double, 3> epsilons = {1e-3, 1e-4, 1e-5};

  static_assert(abs_diff(calculate_pi(epsilons[0]),
                         std::numbers::pi_v<double>) < epsilons[0] * 5.0);
  static_assert(abs_diff(calculate_pi(epsilons[1]),
                         std::numbers::pi_v<double>) < epsilons[1] * 5.0);
  static_assert(abs_diff(calculate_pi(epsilons[2]),
                         std::numbers::pi_v<double>) < epsilons[2] * 5.0);

  static_assert(abs_diff(calculate_e(epsilons[0]), std::numbers::e_v<double>) <
                epsilons[0]);
  static_assert(abs_diff(calculate_e(epsilons[1]), std::numbers::e_v<double>) <
                epsilons[1]);
  static_assert(abs_diff(calculate_e(epsilons[2]), std::numbers::e_v<double>) <
                epsilons[2]);
}