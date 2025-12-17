#include <cassert>
#include <string>
#include <utility>

struct Entity {
  virtual ~Entity() = default;
  virtual std::string execute() const = 0;
};

struct ConcreteEntity : virtual public Entity {
  std::string execute() const override { return "data"; }
};

template <typename T> struct Decorator : public T, virtual public Entity {
  std::string execute() const override { return T::execute(); }
};

template <typename T> struct BracketsDecorator : public Decorator<T> {
  std::string execute() const override {
    return "[" + Decorator<T>::execute() + "]";
  }
};

template <typename T> struct AsterisksDecorator : public Decorator<T> {
  std::string execute() const override {
    return "*" + Decorator<T>::execute() + "*";
  }
};

int main() {
  ConcreteEntity entity;
  assert(entity.execute() == "data");

  BracketsDecorator<ConcreteEntity> bracketed;
  assert(bracketed.execute() == "[data]");

  AsterisksDecorator<ConcreteEntity> asterisked;
  assert(asterisked.execute() == "*data*");

  AsterisksDecorator<BracketsDecorator<ConcreteEntity>> combined;
  assert(combined.execute() == "*[data]*");

  Entity *base_ptr = &combined;
  assert(base_ptr->execute() == "*[data]*");
}