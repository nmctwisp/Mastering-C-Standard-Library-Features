#include <iostream>
#include <stdexcept>
#include <memory>

void foo(std::unique_ptr<int>, int) {
	std::cout << "Inside foo\n";
};

int bar() {
	throw std::runtime_error("whoops!");
}

//int main() {
//	// Consider the following line of code:
//	foo(std::unique_ptr<int>{new int{ 5 }}, bar());
//	
//	// There are three orders in which the above 'foo' invocation could be executed.
//
//	// Order #0
//	// * Allocate memory for 'new int{5}'
//	// * Construct the unique_ptr
//	// * Invoke bar() and throw
//
//	// Order #1
//	// * Invoke bar() and throw
//	// * Allocate memory for 'new int{5}'
//	// * Construct the unique_ptr
//
//	// Order #2
//	// * Allocate memory for 'new int{5}'
//	// * Invoke bar() and throw
//	// * Construct the unique ptr
//
//	// In the case of #0 and #1, everything is perfectly sage: the unique_ptr cleans
//	// up after itself if required and no memory leak occurs.
//
//	// In the case of order #2, there is a memory leak! The unique_ptr doesn't get a 
//	// chance to complete its construction before the exception is thrown. However,
//	// the memory for the int was already allocated, so it gets leaked.
//
//	// Now consider the alternative 'foo' call:
//	foo(std::make_unique<int>(5), bar());
//
//	// Using std::make_unique prevents the issue explained above - the above invovation
//	// will not interleave an allocation with the call to bar().
//
//	// Additionally, using make_unique: 
//	// * Makes the code terset and more readable
//	// * Doesn't require an explicit call to new.
//}
