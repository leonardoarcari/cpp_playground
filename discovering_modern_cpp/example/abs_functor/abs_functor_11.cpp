// C++ 11 way

template <typename T> struct abs_functor {
  using return_type = T;

  T operator()(const T &x) { return x < 0 ? -x : x; }
};

template <typename T> auto abs(const T &x) -> decltype(abs_functor<T>()(x)) {
  return abs_functor<T>()(x);
}