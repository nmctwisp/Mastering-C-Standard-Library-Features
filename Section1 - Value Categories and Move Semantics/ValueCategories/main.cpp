#include <utility>

// The terms lvalue and rvalue were nto enough when designing C++11's move
// semantics. Unconditionally moving rvalues would have caused potentially
// dangerous behavior, so a more fine-grained model was required.

// There are now essentially three "leaf" value categories:
// * prvalue - pure rvalues
// * lvalues
// * xvalues - expiring rvalues

//				Expression
//					|
//		Glvalue ----------- RValue
//		   |                   |
//	   --------------   ----------------
//	   |			|	|			   |
//	LValue			Xvalue			Prvalue

// Both xvalues and lvalues are glvalues.
// Both xvalues and prvalues are rvalues.

// Glvalues => "has identity".
// Rvalue => "can be moved from".

struct foo {
	foo prvalue();
	foo& lvalue();
	foo&& xvalue();
};

int main() {
	// The following expression is a prvalue, because foo has
	// no identity and can be moved from.
	// foo{}.prvalue();

	// The following expression is an lvalue, because foo& has 
	// an identity (refers to something) and cannot be moved 
	// (lvalue reference).

	// foo{}.lvalue();

	// The following expression is a xvalue, because foo&& has 
	// identity (refers to something) and can be moved (is an 
	// rvalue reference).

	// foo{}.xvalue();

	foo f;
	f;				// is an lvalue.
	std::move(f);	// std::move(f) is an xvalue.

	// An xvalue can be obtained from an lvalue, but not a
	// prvalue. That's why it stands for "pure rvalue".
	// You can think of prvalues as rvalues that are not
	// references (no identity).

	// http://en.cppreference.com/w/cpp/language/value_category

	return 0;
}

