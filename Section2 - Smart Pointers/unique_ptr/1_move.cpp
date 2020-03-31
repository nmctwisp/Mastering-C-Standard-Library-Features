#include <iostream>
#include <memory>

// As previously mentioned, std::unique_ptr<T> is a move-only class. Why?

// The idea of "copying" doesn't make sense in the context of "unique ownership".
// How can we copy an unique owner of a resource? The whole point is that the
// resource will be accessible only through a single owner at any point in time, 
// that is responsible for acquiring and releasing it.

struct foo {
	foo() { std::cout << "foo::foo()\n"; };
	~foo() { std::cout << "~foo::foo()\n"; };
};

void does_not_compile() {
	std::unique_ptr<foo> f{ new foo };
	//auto f2 = f;
}

// On the other hand, the concept of "moving" is well-defined and makes sense for 
// unique_ptr. The idea is using move semantics to represent ownership transfer from 
// unique_ptr to another

void ownership_transfer() {
	std::unique_ptr<foo> f{ new foo };
	auto f2 = std::move(f);
	// After the above statement, 'f' loses its ownership of the heap-allocated 'foo' 
	// instance. 'f2' becomes the only new unique owner.

	// In this situation, when 'f2' goes out of scope, ~foo() will be invoked. When 'f'
	// goes out of scope, its destructor will not produce any side-effects.
}

// Move semantics allows us to safelt and intuitively return and accept std::unique_ptr
// instances from/to functions.

std::unique_ptr<foo> bar() {
	std::unique_ptr<foo> f{ new foo };
	return f;
}

void take_ownership(std::unique_ptr<foo> fp) {
	std::cout << "fp took ownership of 'f'\n";
}
void take_ownership2(std::unique_ptr<foo>& fpr) {
	auto g = std::move(fpr);
	std::cout << "g took ownership of 'f'\n";
}

//int main() {
//	ownership_transfer();
//	std::cout << "\n";
//
//	auto f = bar();
//	take_ownership(std::move(f));
//
//	f = bar();
//	take_ownership2(f);
//	int x;
//}