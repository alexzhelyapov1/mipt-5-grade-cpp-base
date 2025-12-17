#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

template <typename T>
void order(std::vector<T> &vector, std::size_t left, std::size_t right) {
  for (auto i = left + 1; i < right; ++i) {
    for (auto j = i; j > left; --j) {
      if (vector[j - 1] > vector[j]) {
        std::swap(vector[j], vector[j - 1]);
      }
    }
  }
}

template <typename T>
std::size_t partition(std::vector<T> &vector, std::size_t left,
                      std::size_t right) {
  auto mid = std::midpoint(left, right - 1);
  auto last = right - 1;

  if (vector[mid] < vector[left])
    std::swap(vector[left], vector[mid]);
  if (vector[last] < vector[left])
    std::swap(vector[left], vector[last]);
  if (vector[last] < vector[mid])
    std::swap(vector[mid], vector[last]);

  auto pivot = vector[mid];
  auto i = left - 1;
  auto j = right;

  while (true) {
    do {
      ++i;
    } while (vector[i] < pivot);
    do {
      --j;
    } while (vector[j] > pivot);

    if (i >= j)
      return j;

    std::swap(vector[i], vector[j]);
  }
}

template <typename T>
void split(std::vector<T> &vector, std::size_t left, std::size_t right) {
  if (right - left > 16) {
    auto p = partition(vector, left, right);

    split(vector, left, p + 1);
    split(vector, p + 1, right);
  } else {
    order(vector, left, right);
  }
}

template <typename T> void sort(std::vector<T> &vector) {
  split(vector, 0, std::size(vector));
}

int main() {
  {
    auto size = 1000;
    std::vector<int> vector(size);
    for (auto i = 0; i < size; ++i)
      vector[i] = size - i;
    sort(vector);
    assert(std::ranges::is_sorted(vector));
  }

  {
    std::vector<double> vector = {3.14, 1.41, 2.71, 0.57, 1.61, 9.81, 6.62};
    sort(vector);
    assert(std::ranges::is_sorted(vector));
  }

  {
    std::vector<std::string> vector = {"delta", "alpha", "charlie", "bravo",
                                       "echo"};
    sort(vector);
    assert(std::ranges::is_sorted(vector));
  }
}
