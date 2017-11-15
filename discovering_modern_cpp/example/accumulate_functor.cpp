#include <iostream>
#include <vector>

template <typename Iter, typename T, typename BinaryFunction>
T accumulate(Iter begin, Iter end, T init, BinaryFunction bf) {
  for (; begin != end; ++begin) {
    init = bf(init, *begin);
  }
  return init;
}

template <typename T> struct add {
  T operator()(const T &x, const T &y) const { return x + y; }
};

struct times {
  template <typename T> T operator()(const T &x, const T &y) const {
    return x * y;
  }
};

int main() {
  std::vector<double> v{7.0, 8.0, 10.0};
  double s{accumulate(std::begin(v), std::end(v), 0.0, add<double>{})};
  double t{accumulate(std::begin(v), std::end(v), 0.0, times{})};
  std::cout << "s = " << s << " t = " << t << '\n';
}