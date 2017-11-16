#include "varprint1.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  using namespace std::string_literals;
  auto s = "world"s;
  print(7.5, "hello", s);
  return 0;
}


