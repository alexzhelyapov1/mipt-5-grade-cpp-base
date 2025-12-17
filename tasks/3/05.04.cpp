#include <cassert>

struct SumStrategy {
  int algorithm(int a, int b) const { return a + b; }
};

struct MulStrategy {
  int algorithm(int a, int b) const { return a * b; }
};

template <typename T> struct Entity : public T {
  int execute(int a, int b) const { return T::algorithm(a, b); }
};

int main() {
  Entity<SumStrategy> entity1;
  assert(entity1.execute(10, 20) == 30);

  Entity<MulStrategy> entity2;
  assert(entity2.execute(10, 20) == 200);
}
