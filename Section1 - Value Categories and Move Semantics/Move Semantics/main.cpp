#include <type_traits>
#include <utility>
#include <vector>

int main() {
	// Let's now analyze a different scenario:
	// we have an lvalue 'v0' that we want to "move"
	// to a destination vector.

	std::vector<int> v0{ 1,2,3,4,5 };

	// We, as developers, know that 'v0' won't be used
	// anymore in the current scope and that an unnecessary
	// copy can be avoided. How can we inform the compiler 
	// of our intentions?

	auto v1 = std::move(v0);

	// std::move does precisely that: it casts an existing lvalue
	// expression to an rvalue, so that the implementation of 
	// std::vector can take advantage of the fact that 'v0' is
	// about to expire.

	// How does std::move work? It literally is only a static_cast
	// to an r-value reference.

	auto v2 = static_cast<std::vector<int>&&>(v1);

	// In the line above, we perform the same operation as
	// std::move does, but in a verbose and less expressive manner

	// Note: that using 'v0' or 'v1' here would lead to undefined behavior.

	return 0;
}
