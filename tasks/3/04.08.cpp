#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

template <typename... Ts> class Tuple {
public:
  constexpr std::size_t size() const { return sizeof...(Ts); }
};

template <typename T, typename... Ts> class Tuple<T, Ts...> {
public:
  constexpr Tuple(T &&x, Ts &&...xs)
      : m_head(std::forward<T>(x)), m_tail(std::forward<Ts>(xs)...) {}

  template <std::size_t I> constexpr auto get() const {
    if constexpr (I > 0) {
      return m_tail.template get<I - 1>();
    } else {
      return m_head;
    }
  }

  constexpr std::size_t size() const { return 1 + sizeof...(Ts); }

private:
  T m_head;
  Tuple<Ts...> m_tail;
};

int main() {
  constexpr Tuple<int, double, char> t1(1, 2.5, 'a');

  static_assert(t1.size() == 3);
  static_assert(t1.get<0>() == 1);
  static_assert(t1.get<1>() == 2.5);
  static_assert(t1.get<2>() == 'a');

  constexpr Tuple<int> t2(42);
  static_assert(t2.size() == 1);
  static_assert(t2.get<0>() == 42);

  Tuple<int, std::string> t3(10, "test");
  assert(t3.size() == 2);
  assert(t3.get<0>() == 10);
  assert(t3.get<1>() == "test");
}
