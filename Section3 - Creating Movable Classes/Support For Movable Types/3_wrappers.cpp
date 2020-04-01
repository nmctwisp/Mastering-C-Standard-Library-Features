#include <utility>
#include <cassert>
#include <tuple>

// std::pair and std::tuple are general-purpose wrapper classes that bundle together 
// object of potentially different types.

// As std::pair is less general than std::tuple we're going to only cover std::tuple.
// All observations also apply to std::pair.

struct foo {};
struct bar {};

// std::tuple instances can be created either explicitly or through std::make_tuple, 
// which deduce the types of the objects for you.

// Moves are used whenever possible, both during construction and assignment

void creating_and_assigning() {
	std::tuple<foo, bar, int> t0{ {}, {}, 1 };
	auto t1 = std::make_tuple(foo{}, bar{}, 1);

	t0 = t1;			// Element-wise copy
	t1 = std::move(t0);	// Element-wise move
}

// Items can be retrieved out of tuples anf pairs by using std::get

void retrieving_by_index() {
	auto t = std::make_tuple(foo{}, bar{}, 5);

	// Getting lvalue references
	foo& i0 = std::get<0>(t);
	bar& i1 = std::get<1>(t);
	int& i2 = std::get<2>(t);

	// Moving out of a tuple
	foo m0 = std::move(std::get<0>(t));
	bar m1 = std::get<1>(std::move(t));
}

// Since C++14, std::get supports retrievalby-type if there are no duplicate types

void retrieving_by_type() {
	auto t = std::make_tuple(foo{}, bar{}, 5);
	const auto& i = std::get<int>(t);
	assert(i == 5);
}

// std::tuples can be destructured by using std::tie. This is particularly useful when
// a function returns a tuple.

std::tuple<foo, bar> get_t();

void destructuring() {
	foo f;
	bar b;
	std::tie(f, b) = get_t();
	// the boject will be moved out of the source toubple if it is an rvalue.
}

// Since C++17, std::apply can be used to invoke a function with the elements of a tuple. 
// Objects will be moved out of the tuple if appropriate.

int add(int x, int y) { return x + y; };
void apply_example() {
	int result{ std::apply(add, std::make_tuple(1, 2)) };
	assert(result == 3);
}

// Tuples are very useful in generic programming or when writing "glue" code. They can also be 
// used for quick prototyping or to avoid boilerplate when a simple wrapper is required.
// Additionally, they support lexicographical comparison which allows easy definition of
// by-member comparison operators:

struct two_ints {
	int _a, _b;

	bool operator==(const two_ints& rhs) const {
		return std::tie(_a, _b) == std::tie(rhs._a, rhs._b);
	}
};
