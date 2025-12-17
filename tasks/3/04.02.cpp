#include <cassert>
#include <cmath>
#include <utility>

double minimum(double n) { return n; }

template <typename... Args> double minimum(double n, Args... args) {
  double min_tail = minimum(args...);
  return n < min_tail ? n : min_tail;
}

double maximum(double n) { return n; }

template <typename... Args> double maximum(double n, Args... args) {
  double max_tail = maximum(args...);
  return n > max_tail ? n : max_tail;
}

template <typename... Args> double sum(Args... args) { return (args + ...); }

template <typename... Args> double average(Args... args) {
  return (args + ...) / static_cast<double>(sizeof...(args));
}

int main() {
  constexpr double epsilon = 1e-9;

  assert(std::abs(minimum(5.5, 2.2, 9.1, 1.1, 4.4) - 1.1) < epsilon);
  assert(std::abs(minimum(3.14) - 3.14) < epsilon);

  assert(std::abs(maximum(5.5, 2.2, 9.1, 1.1, 4.4) - 9.1) < epsilon);
  assert(std::abs(maximum(2.71) - 2.71) < epsilon);

  assert(std::abs(sum(1.1, 2.2, 3.3) - 6.6) < epsilon);
  assert(std::abs(sum(10.0) - 10.0) < epsilon);

  assert(std::abs(average(1.0, 2.0, 3.0, 4.0) - 2.5) < epsilon);
  assert(std::abs(average(10.0, 20.0) - 15.0) < epsilon);
}