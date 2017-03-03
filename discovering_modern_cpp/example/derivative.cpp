#include <cmath>
template <typename F, typename T, unsigned N>

class nth_derivative {
  using prev_derivative = nth_derivative<F, T, N - 1>;

public:
  nth_derivative(const F &f, const T &h) : h(h), fp(f, h) {}

  T operator()(const T &x) const {
    return N & 1 ? (fp(x + h) - fp(x)) / h : (fp(x) - fp(x + h)) / h;
  }

private:
  T h;
  prev_derivative fp;
};

template <typename F, typename T> class nth_derivative<F, T, 1> {
public:
  nth_derivative(const F &f, const T &h) : f(f), h(h) {}
  T operator()(const T &x) { return (f(x + h) - f(x)) / h; }

private:
  const F &f;
  T h;
};

class psc_f {
public:
  psc_f(double alpha) : alpha(alpha) {}
  double operator()(double x) const { return sin(alpha * x) + cos(x); }

private:
  double alpha;
};

template <unsigned N, typename F, typename T>
nth_derivative<F, T, N> make_nth_derivative(const F &f, const T &h) {
  return nth_derivative<F, T, N>(f, h);
};