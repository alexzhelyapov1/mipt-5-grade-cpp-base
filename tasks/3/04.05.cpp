#include <limits>

template <int N> struct Fibonacci {
  static_assert(N >= 0, "N must be non-negative");

  static constexpr int prev1 = Fibonacci<N - 1>::value;
  static constexpr int prev2 = Fibonacci<N - 2>::value;

  static_assert(prev1 <= std::numeric_limits<int>::max() - prev2,
                "Integer overflow detected");

  static constexpr int value = prev1 + prev2;
};

template <> struct Fibonacci<0> { static constexpr int value = 0; };

template <> struct Fibonacci<1> { static constexpr int value = 1; };

template <int N> constexpr int fib_v = Fibonacci<N>::value;

int main() {
  static_assert(fib_v<0> == 0);
  static_assert(fib_v<1> == 1);
  static_assert(fib_v<2> == 1);
  static_assert(fib_v<3> == 2);
  static_assert(fib_v<4> == 3);
  static_assert(fib_v<5> == 5);
  static_assert(fib_v<6> == 8);
  static_assert(fib_v<10> == 55);
  static_assert(fib_v<20> == 6765);
  static_assert(fib_v<46> == 1836311903);
}
