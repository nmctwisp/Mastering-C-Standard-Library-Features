#include <iostream>
#include <string>
int& bar(int& a) {
	return a;
}
int main() {
	int a;

	// L-Values can appear on the left side of 
	// the built-in assignment operator:
	a = 0;

	// The address of l-value can be taken:
	int* a_ptr = &a;

	// L-values can bind to l-value references:
	int& a_ref = a;

	// Examples of l-values:
	// (1) Name of a Variable:
	a;

	// (2) "Member of Object" expression:
	struct foo {
		int _b;
	};
	foo f;

	f._b;

	// (3) Function call returning l-value reference:

	int* y = &bar(a); 
	*y += 1;

	bar(a) = 5;

	y = &bar(a);

	//without int& in function declaration you would not be able to return the address of "a"
}

