#include "stack1.hpp"
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  Stack<int> intStack;            // stack of Ints
  Stack<std::string> stringStack; // stack of strings

  // Manipulate int stack
  intStack.push(7);
  std::cout << intStack.top() << '\n';
  intStack.push(8);
  intStack.push(9);
  std::cout << intStack << '\n';

  // Manipulate string stack
  stringStack.push("hello");
  std::cout << stringStack.top() << '\n';
  stringStack.pop();

  #if __cplusplus >= 201703L
  Stack autoIntStack = 0;
  std::cout << autoIntStack << '\n';

  Stack autoStringStack{"hello"};
  std::cout << autoStringStack << autoStringStack.top().size() << '\n';
  #endif

  return 0;
}