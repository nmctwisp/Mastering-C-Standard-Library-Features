#include <iostream>
#include <memory>

// To use smart pointers, the '<memory>' header must be included.

// std::unique_ptr<T> is a move-only class that represents unique ownership
// over a dynamically allocated object.

struct foo {
	foo() { std::cout << "foo::foo()\n"; };
	~foo() { std::cout << "~foo::foo()\n"; };
};

void not_so_smart() {
	foo* f = new foo;
	// ... use 'f' ...
	delete f;
}

void smart() {
	std::unique_ptr<foo> f{ new foo };
	// ... use 'f' ...
}

// When the unique_ptr instance, f, goes out of scope, it will automatically call 
// 'delete' for us, making sure that we do not forget to free the previously 
// allocated memory. The above 'not_so_smart' and 'smart' functions are equivalent 
// in behavior and performance. The main difference is that 'smart' is way less
// error-prone than 'not_so_smart' and way easier to understand.

// As you can see std::unique_ptr<T> requires an explicit template parameter for the 
// owned type. It has a constructor taking a 'T*' that takes ownership of the passed 
// pointer.
// http://en.cppreference.com/w/cpp/memory/unique_ptr

//int main() {
//	not_so_smart();
//	smart();
//}