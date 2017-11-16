#include <cassert>
#include <ostream>
#include <vector>

template <typename T> class Stack {
private:
  std::vector<T> elems; // elements

public:
  Stack() = default;
  Stack(T const &elem); // initialize stack with one element

  void push(const T &elem); // push element
  void pop();               // pop the element
  const T &top() const;     // return the top element
  bool empty() const { return elems.empty(); }
  void printOn(std::ostream &os) const;

  // Friend functions
  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Stack<U> &s);
};

#if __cplusplus >= 201703L
// Deduction guide to deduce a Stack of C-style strings to std::string
Stack(const char *) -> Stack<std::string>;
#endif

template <typename T> Stack<T>::Stack(T const &elem) : elems({elem}) {}

template <typename T> void Stack<T>::push(const T &elem) {
  elems.push_back(elem); // appends a copy of passed element
}

template <typename T> void Stack<T>::pop() {
  assert(!elems.empty());
  elems.pop_back(); // remove last element
}

template <typename T> const T &Stack<T>::top() const {
  assert(!elems.empty());
  return elems.back(); // return copy of last element
}

template <typename T> void Stack<T>::printOn(std::ostream &os) const {
  for (const T &e : elems) {
    os << e << ' '; // call << for each element
  }
}

// Non member functions
template <typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &s) {
  s.printOn(os);
  return os;
}
