#include <string>
#include <functional>
#include <iostream>

template<char const* threadName>
void doWork() {
	std::cout << "[ " << threadName << " ] working...\n";
}

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 10; ++i) {
		static const char a[] = "hey";
		doWork<a>();
	}
	return 0;
}