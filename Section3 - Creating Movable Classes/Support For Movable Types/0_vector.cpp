#include <vector>
#include <iostream>

// Almost every container in the Standard Library is move-aware. This means that
// it will use move operations (if available) when dealing with its items.
// Let's begin by looking at std::vector

// Assuming that foo is a class that support move semantics, we can see that the vector
// will try to move whenever possible.

struct foo {
	foo() { std::cout << "foo::foo()\n"; };
	~foo() { std::cout << "foo::~foo()\n"; };

	foo(const foo&) { std::cout << "foo::foo(const foo&)\n"; };
	foo(foo&&) noexcept { std::cout << "foo::foo(foo&&)\n"; };
};

void vector_move_awareness() {
	std::vector<foo> v;
	v.reserve(10);
	foo f0;

	// Copies f0
	v.push_back(f0);

	// Moves f0
	v.push_back(std::move(f0));

	// Moves foo rvalue
	v.push_back(foo{});
}

// Containers allow us to go one step further, and sometimes allow us to entirely avoid
// the move. This can happen when an item is being constructed "in-place" inside the 
// container. This operation is called "emplacement" and is supported by most Standard
// Library containers.

struct bar {
	int _x;
	bar(int x)
		: _x{ x } {
	};
};

void vector_emplacement() {
	std::vector<bar> v;
	v.reserve(10);

	// Moves rvalue bar
	v.push_back(bar{ 42 });

	// Constructs a bar instance "in-place"
	v.emplace_back(42);
}

// Emplacement works by perfectly-forwarding all arguments passed to emplace_back to the 
// constructor of a bar instance being created directly in the target memory location inside
// the vector. 

// Note that writing move-aware classes is very important even if emplacement exists. consider the 
// case where a wrapper class is going to be emplace.

struct bar_wrapper {
	bar _b;
	bar_wrapper(bar b)
		: _b{ std::move(b) } {
		std::cout << "bar_wrapper::bar_wrapper(bar b)";
	};
};

void vector_emplacement_and_move() {
	std::vector<bar_wrapper> v;

	// Moves rvalue bar when constructing the bar_wrapper in place.
	v.emplace_back(bar{ 42 });
}

// In the code above, the move operation for bar cannot be avoided as it happens while constructing
// bar_wrapper. This example shows that having support for move operations is beneficial even when
// trying to maximize the use of emplace_back and similar methods.

//int main() {
//	vector_move_awareness();
//	vector_emplacement();
//	vector_emplacement_and_move();
//
//}
//
