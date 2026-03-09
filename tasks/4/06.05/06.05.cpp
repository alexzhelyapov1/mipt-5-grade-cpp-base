#include <functional>
#include <iostream>
#include <string>

#include <boost/dll.hpp>

int main() {
  std::cout << "Enter library name (e.g., test_v1.so or test_v2.so): ";
  std::string path;
  std::cin >> path;

  try {
    auto test_func = boost::dll::import_symbol<void()>(path, "test");
    test_func();
  } catch (const boost::system::system_error &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}
