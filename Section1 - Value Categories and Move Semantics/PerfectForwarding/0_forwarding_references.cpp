#include <utility>

// When no template argument deduction is happening, '&' means 
// lvalue reference and '&&' means rvalue reference.

void take_lvalue(int& value) {};
void take_rvalue(int&& value) {};

// In the context of template argument deduction, '&&' has a different 
// meaning: "forwarding reference".

template <typename T>
void take_anything(T&& value) {};

// In the function signature above, 'T&&' does NOT mean rvalue reference,
// it means "forwarding reference" instead. A "forwarding reference" binds
// everything and remembers the original value category of the passed object.

void example() {
	take_anything(0);
	// '0' is a prvalue, which is an rvalue.
	// inside the body of "take_anything"
	// * T evaluates to int
	// * T&& evaluates to int&&

	int x;
	take_anything(x);
	// x is a lvalue
	// inside the body of "take_anything"
	// * T evaluates to int&
	// * T&& evaluates to int&
}

// There is a special case that makes T evaluate to an lvalue reference when an 
// lvalue is passed. This was intentionally added to the C++ Standard to allow
// "perfect forwarding".
// http://en.cppreference.com/w/cpp/language/template_argument_deduction#Deduction_from_a_function_call
// Remember that T&& is a forwarding reference only when T is being deduced.

// Why are forwarding reference useful? They remember the original value category 
// of the passed object. This allows developers to weite more generic code avoiding
// repetition and providing more flexible and optimal interfaces.

template <typename T>
struct foo {
	// In this case 'T' is not being deduced here, so 'T&&' is an rvalue 
	// reference to 'T'.
	void not_a_forwarding_reference(T&&);

};
