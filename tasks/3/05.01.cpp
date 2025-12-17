#include <cassert>
#include <string>
#include <utility>

class Builder;

class Person {
public:
  const std::string &get_name() const { return m_name; }
  int get_age() const { return m_age; }
  int get_grade() const { return m_grade; }

private:
  friend class Builder;

  std::string m_name;
  int m_age = 0;
  int m_grade = 0;
};

class Builder {
public:
  Builder() = default;

  Builder &name(std::string name) {
    m_person.m_name = std::move(name);
    return *this;
  }

  Builder &age(int age) {
    m_person.m_age = age;
    return *this;
  }

  Builder &grade(int grade) {
    m_person.m_grade = grade;
    return *this;
  }

  Person get() { return std::move(m_person); }

private:
  Person m_person;
};

int main() {
  Builder builder;
  auto person = builder.name("Ivan").age(25).grade(10).get();

  assert(person.get_name() == "Ivan");
  assert(person.get_age() == 25);
  assert(person.get_grade() == 10);
}
