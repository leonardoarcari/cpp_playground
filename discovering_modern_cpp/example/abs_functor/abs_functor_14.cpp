// C++ 14 way

template <typename T> struct abs_functor {
  using result_type = T;

  T operator()(const T &x) { return x < 0 ? -x : x; }
};

template <typename T> decltype(auto) abs(const T &x) {
  return abs_functor<T>()(x);
}