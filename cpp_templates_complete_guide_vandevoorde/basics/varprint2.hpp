#include <iostream>

// This is interesting. This works just fine even if we don't have a
// template overload for the empty parameter pack. This is because
// we will never see the case of an empty parameter pack, since in case
// two matching overloads are found, the one with no parameter pack argument
// is preferred. So at the point we instantiate print for firstArg and args
// such that sizeof...(args) == 1, the call to print(args...) will invoke
// print(T arg) instead of print(T firstArg, Types... args') with args' such
// that sizeof...(args') == 0.
template <typename T>
void print(T arg) {
	std::cout << arg << '\n';
}

template <typename T, typename... Types>
void print(T firstArg, Types... args) {
	print(firstArg);
	print(args...);
}