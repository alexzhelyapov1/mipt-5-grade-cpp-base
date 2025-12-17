module;

#include <compare>
#include <istream>
#include <ostream>

export module rational;

export import :mixins;

namespace math {
export template <typename T>
class Rational : public addable<Rational<T>>,
                 public subtractable<Rational<T>>,
                 public multipliable<Rational<T>>,
                 public dividable<Rational<T>>,
                 public incrementable<Rational<T>>,
                 public decrementable<Rational<T>> {
public:
  Rational(T num = 0, T den = 1);
  explicit operator double() const { return 1.0 * m_num / m_den; }

  Rational &operator+=(Rational const &other);
  Rational &operator-=(Rational const &other);
  Rational &operator*=(Rational const &other);
  Rational &operator/=(Rational const &other);

  Rational &operator++() {
    *this += 1;
    return *this;
  }
  Rational &operator--() {
    *this -= 1;
    return *this;
  }

  friend bool operator==(Rational const &lhs, Rational const &rhs) {
    return lhs.m_num == rhs.m_num && lhs.m_den == rhs.m_den;
  }

  friend std::strong_ordering operator<=>(Rational const &lhs,
                                          Rational const &rhs) {
    return (lhs.m_num * rhs.m_den) <=> (rhs.m_num * lhs.m_den);
  }

  friend std::istream &operator>>(std::istream &stream, Rational &rational) {
    T n, d;
    stream >> n;
    stream.ignore();
    stream >> d;
    rational = Rational(n, d);
    return stream;
  }

  friend std::ostream &operator<<(std::ostream &stream,
                                  Rational const &rational) {
    return stream << rational.m_num << '/' << rational.m_den;
  }

private:
  void reduce();
  T m_num = 0;
  T m_den = 1;
};

export {
  template <typename T> Rational(T, T) -> Rational<T>;
  template <typename T> Rational(T) -> Rational<T>;
}
} // namespace math
