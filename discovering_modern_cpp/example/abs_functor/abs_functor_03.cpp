// C++ 03 way
template <typename T> struct abs_functor {
  typedef T result_type;

  T operator()(const T &x) { return x < 0 ? -x : x; }
};

template <typename T> typename abs_functor<T>::result_type abs(const T &x) {
  return abs_functor<T>()(x);
}