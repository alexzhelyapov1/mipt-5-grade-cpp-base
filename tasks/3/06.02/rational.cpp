module;

#include <numeric>

module rational;

namespace math {
template <typename T>
Rational<T>::Rational(T num, T den) : m_num(num), m_den(den) {
  reduce();
}

template <typename T> void Rational<T>::reduce() {
  if (m_den < 0) {
    m_num = -m_num;
    m_den = -m_den;
  }
  auto gcd = std::gcd(m_num, m_den);
  m_num /= gcd;
  m_den /= gcd;
}

template <typename T>
Rational<T> &Rational<T>::operator+=(Rational const &other) {
  auto lcm = std::lcm(m_den, other.m_den);
  m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
  m_den = lcm;
  reduce();
  return *this;
}

template <typename T>
Rational<T> &Rational<T>::operator-=(Rational const &other) {
  return *this += Rational(other.m_num * -1, other.m_den);
}
template <typename T>
Rational<T> &Rational<T>::operator*=(Rational const &other) {
  m_num *= other.m_num;
  m_den *= other.m_den;
  reduce();
  return *this;
}
template <typename T>
Rational<T> &Rational<T>::operator/=(Rational const &other) {
  return *this *= Rational(other.m_den, other.m_num);
}

template class Rational<int>;
template class Rational<long long>;
} // namespace math