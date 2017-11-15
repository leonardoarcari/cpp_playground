#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

/**
 * Exercise 3.1
 * Write a generic funtion to_string that takes an argument of arbitrary type
 * (as const&) and generates a string by piping it to a std::stringstream and
 * returning the resulting string
 */
template <typename T> std::string inline to_string(const T &x) {
  std::stringstream ss{};
  ss << x;
  return ss.str();
}

/**
 * Exercise 3.2
 * Write a variadic template function that represents an arbitrary number of
 * arguments as tuple in a string. That is, the function call
 * to_tuple_string(x, y, z) returns a string of the form (x, y, z) by printing
 * each elements to a string stream
 */
template <typename T> void to_tuple_string_aux(std::stringstream &ss, T t) {
  ss << t;
}

template <typename T, typename... P>
void to_tuple_string_aux(std::stringstream &ss, T t, P... p) {
  ss << t << ", ";
  to_tuple_string_aux(ss, p...);
}

template <typename... P> std::string to_tuple_string(P... p) {
  std::stringstream ss;
  ss << "(";
  to_tuple_string_aux(ss, p...);
  ss << ")";
  return ss.str();
}

/**
 * Write a stack implementation for a generic value type. The maximal size of
 * stack is defined in the class (hard-wired). Provide:
 * Constructor, Destructor if necessary, top, pop, push, clear, size, full,
 * empty. Stack over-or-under flowmust throw an exception
 */
template <unsigned N, typename T> class stack {
public:
  stack(){};
  stack(const std::initializer_list<T> &l) : stack() {
    if (l.size() > N)
      throw std::invalid_argument{"Too much arguments for declared size"};
    std::copy(std::begin(l), std::end(l), std::begin(m_data));
    m_size = l.size();
    m_top_pos = m_size - 1;
  }
  //~stack() { delete[] m_data; } no more necessary

  bool empty() const { return m_top_pos == -1; }
  bool full() const { return m_size == N; }
  const T &top() const {
    if (empty())
      throw std::domain_error{"Empty stack"};
    return m_data[m_top_pos];
  }
  void pop() {
    if (empty())
      throw std::underflow_error{"Empty stack"};
    --m_size;
    --m_top_pos;
  }
  void push(const T &to_push) {
    if (full())
      throw std::overflow_error{"Stack is full"};
    ++m_size;
    ++m_top_pos;
    m_data[m_top_pos] = to_push;
  }
  int size() const { return m_size; }

private:
  T m_data[N];
  int m_size{0};
  int m_top_pos{-1};
};

// Test stack implementation
template <unsigned N, typename T>
void testStack(const ::stack<N, T> &s, const std::string &stack_name) {
  std::cout << stack_name << " is empty? " << s.empty() << "\n"
            << stack_name << " size: " << s.size() << "\n"
            << stack_name << " top: " << s.top() << "\n";
}

/**
 * Add the methods begin() and end() for returning a begin and end iterator to
 * class vector. Add the types iterator and const_iterator to the class as well.
 * Note that pointers are models of the concept of random-access iterators.
 * Use the STL function sort for ordering vector entries to demonstrate that
 * your iterators work as they should.
 */
template <typename T> class vector {
  void check_size(int that_size) const { assert(m_size == that_size); }
  void check_index(int i) const { assert(i >= 0 && i < m_size); }

public:
  explicit vector(int size) : m_size{size}, m_data{new T[m_size]} {}
  vector() : m_size{0}, m_data{nullptr} {}
  vector(const vector &that) : m_size{that.m_size}, m_data{new T[m_size]} {
    std::copy(&that.m_data[0], &that.m_data[that.my_size], &m_data[0]);
  }

  int size() const { return m_size; }

  vector &operator=(const vector &that) {
    check_size(that.m_size);
    std::copy(&that.m_data[0], &that.m_data[that.m_size], &m_data[0]);
    return *this;
  }

  const T &operator[](int i) const { return m_data[i]; }

  T &operator[](int i) {
    check_index(i);
    return m_data[i];
  }

  vector operator+(const vector &that) const {
    check_size(that.my_size);
    vector sum(m_size);
    for (int i = 0; i < m_size; ++i)
      sum[i] = m_data[i] + that[i];
    return sum;
  }

private:
  int m_size;
  std::unique_ptr<T[]> m_data;

public:
  // Iterators
  class const_vector_iterator {
  public:
    using value_type = T;
    using difference_type = int;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::random_access_iterator_tag;

    using self = const_vector_iterator;

    // Constructors
    const_vector_iterator(T *data) : m_data{data} {}
    const_vector_iterator();
    const_vector_iterator(const const_vector_iterator &other) {
      m_data = other.m_data;
    }

    // Assignment
    self &operator=(const self &other) {
      m_data = other.m_data;
      return *this;
    }

    // Aritmethic
    self &operator++() {
      ++m_data;
      return *this;
    }
    self &operator--() {
      --m_data;
      return *this;
    }
    self operator++(int i) { return self(++(*this)); }
    self &operator+=(const difference_type n) {
      difference_type m = n;
      if (m >= 0) {
        while (m--) {
          ++m_data;
        }
      } else {
        while (m++) {
          --m_data;
        }
      }
      return *this;
    }
    self operator+(const difference_type n) const {
      self ret{*this};
      return ret += n;
    }
    self &operator-=(const difference_type n) {
      difference_type m = n;
      if (m >= 0) {
        while (m--) {
          --m_data;
        }
      } else {
        while (m++) {
          ++m_data;
        }
      }
      return *this;
    }
    difference_type operator-(const self &other) const {
      bool this_ahead = m_data > other.m_data;
      T *cur = other.m_data;
      difference_type m{0};
      if (this_ahead) {
        while (cur != m_data) {
          ++cur;
          ++m;
        }
      } else {
        while (cur != m_data) {
          --cur;
          --m;
        }
      }
      return m;
    }
    self &operator-(difference_type n) {
      self tmp = *this;
      return tmp -= n;
    }

    // Access
    reference operator*() const { return *m_data; }
    reference operator[](const difference_type n) const { return *(*this + n); }

    // Comparison
    bool operator==(const self &other) { return m_data == other.m_data; }
    bool operator!=(const self &other) { return !(*this == other); }
    bool operator>(const self &other) { return m_data > other.m_data; };
    bool operator<(const self &other) { return m_data < other.m_data; };
    bool operator>=(const self &other) { return !(*this < other); }
    bool operator<=(const self &other) { return !(*this > other); }

    void swap(self &other) {
      std::cout << "Swapping!\n";
      T *tmp{m_data};
      m_data = other.m_data;
      other.m_data = tmp;
    }

  private:
    T *m_data{nullptr};
  };

public:
  using iterator = const_vector_iterator;
  iterator begin() const { return const_vector_iterator(&m_data[0]); }
  iterator end() const { return const_vector_iterator(&m_data[m_size]); }
  void swap(iterator &a, iterator &b) { a.swap(b); }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &v) {
  os << '[';
  for (int i = 0; i < v.size(); ++i)
    os << v[i] << ((i != v.size() - 1) ? ", " : "");
  os << ']';
  return os;
}

/**
* Write an iterator class for odd numbers named odd_iterator. The class must
* model (realize) the ForwardIterator concept
* (http://www.sgi.com/tech/stl/ForwardIterator.html). That means it must
* provide the following members:
* • Default and copy constructor;
* • operator++ to the next odd element, as pre-increment and post-increment;
* • operator* as dereference which returns an (odd) int;
* • operator== and operator!=; and
* • operator=.
* with the obvious semantics. In addition, the class should contain a
* constructor that accepts an int value. This value will be returned in the
* dereference operator (as long as the iterator is not incremented). This
* constructor should throw an exception if the value is even. Likewise the
* default constructor should initialize the internal value with 1 to provide a
* legal state.
*/
class odd_iterator {
public:
  using self = odd_iterator;

  // Constructors
  explicit odd_iterator(int starting_value) {
    if (starting_value % 2 == 0)
      throw std::invalid_argument("starting_value is even. Odd value required");
    else
      value = starting_value;
  }
  odd_iterator() {}
  odd_iterator(const self &other) : value{other.value} {}

  // Assignment
  self &operator=(const self &other) {
    value = other.value;
    return *this;
  }

  // Iterator operators
  self &operator++() {
    value += 2;
    return *this;
  }
  int operator*() const { return value; }

  // Comparison
  bool operator==(const self &other) const { return value == other.value; }
  bool operator!=(const self &other) const { return !(*this == other); }

private:
  int value{1};
};

/**
 * Write a class for a range of odd numbers. The member or free functions begin
 * and end should return an odd_iterator as defined in Exercise 3.11.5. The
 * following code should print the odd numbers {7, 9, ..., 25}:
 * for (int i : odd_range(7, 27))
 *     std::cout    i    “\n”;
 */
class odd_range {
public:
  using const_iterator = odd_iterator;
  explicit odd_range(int begin, int end) : _begin_it{begin}, _end_it{end} {}

  // Range methods
  const_iterator begin() { return _begin_it; }
  const_iterator end() { return _end_it; }

private:
  odd_iterator _begin_it;
  odd_iterator _end_it;
};

// Testing main
int main(int argc, char const *argv[]) {
  // To string function
  int x{5};
  double y{3.9};
  unsigned int z{5000000};
  std::cout << "x: " << to_string(x) << "\ny: " << to_string(y)
            << "\nz: " << to_string(z) << "\n";

  // to_tuple_string function
  std::cout << to_tuple_string(21, 12, 15, 18) << "\n";

  // Stack class
  ::stack<5, std::string> s1{"ciao", "belli"};
  ::stack<10, int> s2;
  ::stack<10, double> s3;

  testStack(s1, "s1");

  // Vector iterator
  vector<double> v1(5);
  v1[0] = 5;
  v1[1] = 2;
  v1[2] = 7;
  v1[3] = 6;
  v1[4] = 1;
  std::cout << "Pre-sort: " << v1 << "\n";
  std::sort(std::begin(v1), std::end(v1));
  std::cout << "Post-sort: " << v1 << "\n";

  vector<std::string> v2(5);
  v2[0] = "Ciao";
  v2[1] = "Belli";
  v2[2] = "Come";
  v2[3] = "State";
  v2[4] = "Appa";
  std::cout << "Pre-sort: " << v2 << "\n";
  std::sort(std::begin(v2), std::end(v2));
  std::cout << "Post-sort: " << v2 << "\n";

  // Odd iterator
  odd_iterator i2{9};
  for (odd_iterator i1; i1 != i2; ++i1) {
    std::cout << "odd_iterator i1: " << *i1 << "\n";
  }

  try {
    odd_iterator i1{2};
  } catch (std::invalid_argument e) {
    std::cout << e.what() << "\n";
  }

  for (int i : odd_range(7, 27)) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  return 0;
}
