#include <cassert>
#include <cstddef>

template <typename T, T v> struct integral_constant {
  static constexpr T value = v;
  using value_type = T;
  using type = integral_constant;
  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template <bool B, typename T, typename F> struct conditional {
  using type = T;
};

template <typename T, typename F> struct conditional<false, T, F> {
  using type = F;
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

template <typename T> struct remove_const { using type = T; };
template <typename T> struct remove_const<const T> { using type = T; };

template <typename T> using remove_const_t = typename remove_const<T>::type;

template <typename T> struct remove_volatile { using type = T; };
template <typename T> struct remove_volatile<volatile T> { using type = T; };

template <typename T> struct remove_cv {
  using type = typename remove_volatile<typename remove_const<T>::type>::type;
};

template <typename T> using remove_cv_t = typename remove_cv<T>::type;

template <typename T> struct add_const { using type = const T; };
template <typename T> struct add_const<T &> { using type = T &; };
template <typename T> struct add_const<T &&> { using type = T &&; };

template <typename T> using add_const_t = typename add_const<T>::type;

template <typename T> struct remove_reference { using type = T; };
template <typename T> struct remove_reference<T &> { using type = T; };
template <typename T> struct remove_reference<T &&> { using type = T; };

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

namespace detail {
template <typename T> struct is_class_impl {
  template <typename C> static char test(int C::*);
  template <typename C> static long test(...);

  static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(char);
};
} // namespace detail

template <typename T>
struct is_class : integral_constant<bool, detail::is_class_impl<T>::value> {};

template <typename T> inline constexpr bool is_class_v = is_class<T>::value;

template <typename T> struct is_array : false_type {};

template <typename T> struct is_array<T[]> : true_type {};

template <typename T, std::size_t N> struct is_array<T[N]> : true_type {};

template <typename T> struct is_function : false_type {};

template <typename R, typename... Args>
struct is_function<R(Args...)> : true_type {};

template <typename R, typename... Args>
struct is_function<R(Args...) const> : true_type {};

template <typename T> struct remove_extent { using type = T; };

template <typename T> struct remove_extent<T[]> { using type = T; };

template <typename T, std::size_t N> struct remove_extent<T[N]> {
  using type = T;
};

template <typename T> struct decay {
private:
  using U = remove_reference_t<T>;

public:
  using type = conditional_t<
      is_array<U>::value, typename remove_extent<U>::type *,
      conditional_t<is_function<U>::value, typename add_const<U>::type *,
                    remove_cv_t<U>>>;
};

template <typename R, typename... Args> struct decay<R(Args...)> {
  using type = R (*)(Args...);
};

template <typename R, typename... Args> struct decay<R(Args...) const> {
  using type = R (*)(Args...);
};

template <typename T> using decay_t = typename decay<T>::type;

template <typename T, typename U> struct is_same : false_type {};

template <typename T> struct is_same<T, T> : true_type {};

template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

struct A {};
union B {};

int main() {
  // Test is_class
  static_assert(is_class_v<A>);
  static_assert(is_class_v<B>); // Pointer to member works for unions too
  static_assert(!is_class_v<int>);
  static_assert(!is_class_v<int *>);
  static_assert(!is_class_v<A &>);

  // Test add_const
  static_assert(is_same_v<add_const_t<int>, const int>);
  static_assert(is_same_v<add_const_t<int &>, int &>);
  static_assert(is_same_v<add_const_t<const int>, const int>);

  // Test remove_const
  static_assert(is_same_v<remove_const_t<const int>, int>);
  static_assert(is_same_v<remove_const_t<int>, int>);

  // Test conditional
  static_assert(is_same_v<conditional_t<true, int, double>, int>);
  static_assert(is_same_v<conditional_t<false, int, double>, double>);

  // Test decay
  static_assert(is_same_v<decay_t<int>, int>);
  static_assert(is_same_v<decay_t<int &>, int>);
  static_assert(is_same_v<decay_t<const int &>, int>);
  static_assert(is_same_v<decay_t<int[2]>, int *>);
  static_assert(is_same_v<decay_t<int(int)>, int (*)(int)>);
}