#include <iostream>
#include <string>

enum class Status { success, failure };

struct Person {
  std::string const &name() const { return m_name; }
  int grade() const { return m_grade; }
  long long salary() const { return m_salary; }
  int id() const { return m_id; }

private:
  std::string m_name = "default";
  int m_grade = 0;
  long long m_salary = 0;
  int m_id = 0;
};

void save(Status s, int id) {};

void test(Person const &person) {
  // operator<< can throw std::ios_base::failure.
  // person.name() can throw (e.g., if Person is in a bad state).
  // The std::string temporary for name() can throw std::bad_alloc.
  std::cout << "test : " << person.name() << std::endl;

  // person.grade() or person.salary() could throw.
  // The || operator has short-circuiting, so person.salary() is only called
  // if person.grade() != 10.
  if (person.grade() == 10 || person.salary() > 1'000'000) {
    // person.id() could throw.
    // save() could throw (e.g., I/O error, database error, std::bad_alloc).
    save(Status::success, person.id());
  } else {
    // person.id() could throw.
    // save() could throw.
    save(Status::failure, person.id());
  }
}

int main() {}
