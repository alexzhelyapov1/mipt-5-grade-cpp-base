#include <iostream>

class Entity_v1 {
public:
  Entity_v1(int value) : m_private_field(value) {}
  int get_value() const { return m_private_field; }
private:
  int m_private_field;
};

class Entity_v2 {
public:
  int m_public_field;
};


int main() {
  // Method 1: reinterpret_cast
  Entity_v1 e1(42);
  std::cout << "e1 before cast: " << e1.get_value() << std::endl;

  Entity_v2& e2 = reinterpret_cast<Entity_v2&>(e1);
  e2.m_public_field = 100;
  
  std::cout << "e1 after cast: " << e1.get_value() << std::endl;

  // Method 2: Pointer arithmetic
  Entity_v1 e3(200);
  std::cout << "e3 before pointer arithmetic: " << e3.get_value() << std::endl;

  int* ptr = reinterpret_cast<int*>(&e3);
  *ptr = 300;

  std::cout << "e3 after pointer arithmetic: " << e3.get_value() << std::endl;

  return 0;
}
