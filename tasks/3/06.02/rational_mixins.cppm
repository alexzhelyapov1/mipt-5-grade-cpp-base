module; // Глобальный фрагмент

export module rational:mixins;

export namespace math {
template <typename T> struct addable {
  friend T operator+(T lhs, const T &rhs) { return lhs += rhs; }
};
template <typename T> struct subtractable {
  friend T operator-(T lhs, const T &rhs) { return lhs -= rhs; }
};
template <typename T> struct multipliable {
  friend T operator*(T lhs, const T &rhs) { return lhs *= rhs; }
};
template <typename T> struct dividable {
  friend T operator/(T lhs, const T &rhs) { return lhs /= rhs; }
};
template <typename T> struct incrementable {
  friend T operator++(T &self, int) {
    T t = self;
    ++self;
    return t;
  }
};
template <typename T> struct decrementable {
  friend T operator--(T &self, int) {
    T t = self;
    --self;
    return t;
  }
};
} // namespace math
