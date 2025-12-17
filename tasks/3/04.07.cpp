//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <numeric>
#include <type_traits>

//////////////////////////////////////////////////////////////////////////////////////////

template <int N = 0, int D = 1> struct Ratio {
  constexpr static auto num = N;

  constexpr static auto den = D;
};

//////////////////////////////////////////////////////////////////////////////////////////

template <typename R1, typename R2> struct Sum {
  constexpr static auto _num = R1::num * R2::den + R2::num * R1::den;
  constexpr static auto _den = R1::den * R2::den;
  constexpr static auto _gcd = std::gcd(_num, _den);

  constexpr static auto num = _num / _gcd;
  constexpr static auto den = _den / _gcd;

  //  ------------------------------------------------------------------

  using type = Ratio<num, den>;
};

//////////////////////////////////////////////////////////////////////////////////////////

template <typename R1, typename R2> using sum = typename Sum<R1, R2>::type;

//////////////////////////////////////////////////////////////////////////////////////////

template <typename R1, typename R2> struct Sub {
  using type = typename Sum<R1, Ratio<-R2::num, R2::den>>::type;
  constexpr static auto num = type::num;
  constexpr static auto den = type::den;
};

template <typename R1, typename R2> using sub = typename Sub<R1, R2>::type;

//////////////////////////////////////////////////////////////////////////////////////////

template <typename R1, typename R2> struct Mul {
  constexpr static auto _num = R1::num * R2::num;
  constexpr static auto _den = R1::den * R2::den;
  constexpr static auto _gcd = std::gcd(_num, _den);

  constexpr static auto num = _num / _gcd;
  constexpr static auto den = _den / _gcd;

  using type = Ratio<num, den>;
};

template <typename R1, typename R2> using mul = typename Mul<R1, R2>::type;

//////////////////////////////////////////////////////////////////////////////////////////

template <typename R1, typename R2> struct Div {
  static_assert(R2::num != 0, "Division by zero");

  using type = typename Mul<R1, Ratio<R2::den, R2::num>>::type;
  constexpr static auto num = type::num;
  constexpr static auto den = type::den;
};

template <typename R1, typename R2> using div = typename Div<R1, R2>::type;

//////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename R = Ratio<1>> struct Duration {
  T x = T();

  explicit constexpr Duration(T val) : x(val) {}
};

//////////////////////////////////////////////////////////////////////////////////////////

template <typename T1, typename R1, typename T2, typename R2>
constexpr auto operator+(Duration<T1, R1> const &lhs,
                         Duration<T2, R2> const &rhs) {
  using ratio_t = Ratio<1, sum<R1, R2>::den>;

  auto x = (lhs.x * ratio_t::den / R1::den * R1::num +

            rhs.x * ratio_t::den / R2::den * R2::num);

  return Duration<decltype(x), ratio_t>(x);
}

//////////////////////////////////////////////////////////////////////////////////////////

template <typename T1, typename R1,

          typename T2, typename R2>
constexpr auto operator-(Duration<T1, R1> const &lhs,
                         Duration<T2, R2> const &rhs) {
  return lhs + Duration<T2, R2>(-rhs.x);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main() {
  auto x = 1, y = 2;

  //  ----------------------------------------------------------------------

  Duration<int, Ratio<1, 2>> duration_1(x);

  Duration<int, Ratio<1, 3>> duration_2(y);

  //  ----------------------------------------------------------------------

  Duration<int, Ratio<1, 6>> duration_3 = duration_1 + duration_2;

  //  ----------------------------------------------------------------------

  assert(duration_3.x == 7);

  // Reduction tests
  static_assert(std::is_same_v<sum<Ratio<1, 2>, Ratio<1, 2>>, Ratio<1, 1>>);
  static_assert(std::is_same_v<mul<Ratio<2, 3>, Ratio<3, 4>>, Ratio<1, 2>>);

  // Operation tests
  static_assert(std::is_same_v<sub<Ratio<1, 2>, Ratio<1, 6>>, Ratio<1, 3>>);
  static_assert(std::is_same_v<div<Ratio<1, 2>, Ratio<1, 4>>, Ratio<2, 1>>);

  // Duration subtraction test
  constexpr Duration<int, Ratio<1, 2>> d1(5); // 2.5
  constexpr Duration<int, Ratio<1, 4>> d2(2); // 0.5
  constexpr auto d3 = d1 - d2;
  static_assert(d3.x == 8);
  static_assert(std::is_same_v<decltype(d3), const Duration<int, Ratio<1, 4>>>);
}

//////////////////////////////////////////////////////////////////////////////////////////