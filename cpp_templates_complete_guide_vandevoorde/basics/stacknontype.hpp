#include <array>
#include <cassert>

template <typename T, std::size_t MaxSize>
class Stack {
private:
	std::array<T, MaxSize> elems; // elements
	std::size_t numElems; // current number of elements

public:
	Stack(); // ctor
	void push(T const& elem); // push element
  void pop();               // pop the element
  T const& top() const;     // return the top element
  bool empty() const { return numElems == 0; }
  std::size_t size() const {return numElems; }
};

template <typename T, std::size_t MaxSize>
Stack<T, MaxSize>::Stack() : numElems(0) {}

template <typename T, std::size_t MaxSize>
void Stack<T, MaxSize>::push(T const& elem) {
	assert(numElems < MaxSize);
	elems[numElems] = elem; // append element
	++numElems; // increment number of elements
}

template <typename T, std::size_t MaxSize>
void Stack<T, MaxSize>::pop() {
	assert(!empty());
	--numElems; // decrement number of elements
}

template <typename T, std::size_t MaxSize>
T const& Stack<T, MaxSize>::top() const {
	assert(!empty());
	return elems[numElems - 1]; // return last element
}


