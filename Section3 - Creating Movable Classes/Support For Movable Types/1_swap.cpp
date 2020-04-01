#include <utility>

// std::swap function is a very versatile way of swapping two objects. Users can
// define their own swap specializations that will be found through ADL, but 
// std::swap is always a valid fallback.

// Before C++11 std::swap was typically defined as follows:

template <typename T>
void old_swap(T& x, T& y) {
	T tmp{ x }; // Copy #0
	x = y;		// Copy #1
	y = tmp;	// Copy #2
}

// This was incredibly expensive for a lot of types, which led to containers
// implementations to provide their own fast swap specializations.

// In C++11 and above, std::swap is dedined in terms of move semantics

template <typename T>
void new_swap(T& x, T& y) {
	T tmp{ std::move(x) };	// Move #0
	x = std::move(y);		// Move #1
	y = std::move(tmp);		// Move #2
}

// No copies are executed when using the default implementation, std::swap. This is
// great for both library users and developers: as long as you provide sensible move
// operations for your types, std::swap will be efficient.
