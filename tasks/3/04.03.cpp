#include <cassert>
#include <string>
#include <utility>
#include <vector>

template <typename Container> void handle(Container &container, int value) {
  container.push_back(value);
}

template <typename Container, typename T> void handle(Container &, T &&) {}

template <typename Container, typename... Args>
void insert_ints(Container &container, Args &&...args) {
  (handle(container, std::forward<Args>(args)), ...);
}

int main() {
  std::vector<int> numbers;

  insert_ints(numbers, 10, 3.14, "text", 20, 'c', 30);

  assert(numbers.size() == 3);
  assert(numbers[0] == 10);
  assert(numbers[1] == 20);
  assert(numbers[2] == 30);
}
