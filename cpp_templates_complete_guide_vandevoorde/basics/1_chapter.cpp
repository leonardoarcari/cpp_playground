#include <iostream>
#include <type_traits>

// If we don't take the std::decay::type of the return type in some cases
// it might happen that, because T1 or T2 could be references, the return
// type would be forced to be a reference which is should be not.
// Hence, using std::decay we get the type of the expression with no
// modifiers.
// Care: because std::decay::type returns a type with must prepend typename
// 			 to qualify the expression
template <typename T1, typename T2>
auto max_trailing(T1 a, T2 b) ->
    typename std::decay<decltype(true ? a : b)>::type {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return b < a ? a : b;
}

#if __cplusplus == 201103L
// Although, for types where implicit conversion is available, we can leverage
// on C++11 std::common_type<>
template <typename T1, typename T2>
typename std::common_type<T1, T2>::type max_common(T1 a, T2 b) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return b < a ? a : b;
}
#elif __cplusplus >= 201402L
// In C++14 we can go for a shorter definition
template <typename T1, typename T2>
std::common_type_t<T1, T2> max_common(T1 a, T2 b) {
  std::cout << __PRETTY_FUNCTION__ << "\n";
  return b < a ? a : b;
}
#endif

int main(int argc, char const *argv[]) {
  std::cout << ::max_trailing(2, 3) << '\n' << ::max_common(2, 3) << '\n';
  return 0;
}