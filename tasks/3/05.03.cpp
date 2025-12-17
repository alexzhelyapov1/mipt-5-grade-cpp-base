#include <algorithm>
#include <cassert>
#include <memory>
#include <numeric>
#include <vector>

class Unit {
public:
  virtual ~Unit() = default;

  int perform_action() const {
    prepare();
    return execute();
  }

  virtual void add(std::shared_ptr<Unit>) {}

protected:
  virtual void prepare() const = 0;
  virtual int execute() const = 0;
};

class Soldier : public Unit {
public:
  explicit Soldier(int damage) : m_damage(damage) {}

protected:
  void prepare() const override {}

  int execute() const override { return m_damage; }

private:
  int m_damage;
};

class Tank : public Unit {
public:
  explicit Tank(int damage) : m_damage(damage) {}

protected:
  void prepare() const override {}

  int execute() const override { return m_damage * 2; }

private:
  int m_damage;
};

class Squad : public Unit {
public:
  void add(std::shared_ptr<Unit> unit) override {
    m_units.push_back(std::move(unit));
  }

protected:
  void prepare() const override {}

  int execute() const override {
    return std::transform_reduce(
        m_units.begin(), m_units.end(), 0, std::plus<>(),
        [](const auto &unit) { return unit->perform_action(); });
  }

private:
  std::vector<std::shared_ptr<Unit>> m_units;
};

class SquadBuilder {
public:
  SquadBuilder() { reset(); }

  void reset() { m_squad = std::make_shared<Squad>(); }

  SquadBuilder &add_soldier(int damage) {
    m_squad->add(std::make_shared<Soldier>(damage));
    return *this;
  }

  SquadBuilder &add_tank(int damage) {
    m_squad->add(std::make_shared<Tank>(damage));
    return *this;
  }

  SquadBuilder &add_sub_squad(std::shared_ptr<Unit> sub_squad) {
    m_squad->add(std::move(sub_squad));
    return *this;
  }

  std::shared_ptr<Unit> get() {
    auto result = m_squad;
    reset();
    return result;
  }

private:
  std::shared_ptr<Squad> m_squad;
};

int main() {
  SquadBuilder builder;

  auto alpha_squad = builder.add_soldier(10).add_soldier(15).get();

  auto bravo_squad = builder.add_tank(20).get();

  auto army = builder.add_sub_squad(alpha_squad)
                  .add_sub_squad(bravo_squad)
                  .add_soldier(5)
                  .get();

  assert(alpha_squad->perform_action() == 25);

  assert(bravo_squad->perform_action() == 40);

  assert(army->perform_action() == 25 + 40 + 5);
}
