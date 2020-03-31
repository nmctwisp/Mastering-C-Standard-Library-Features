#include <type_traits>
#include <utility>
#include <vector>

/* Summary
- Learned that the rvalue expression represents temporariness and lack of 
"identity.
- Learned that the std::move is just a cast to an rvalue that expresses the 
"intention" of moving, not necessarily the action. In order to move it would
the result of std::move would need to be assigned to a variable.
- Understood that it is unsafe to use objects after they have been "moved from".
- Learned that moving when returning is unnecessary and sometimes detrimental.
*/


void noop_example() {
	// One very important thing to understand is that std::move doesn't
	// actually move anything: it simply casts an expression to an rvalue.

	// Think of std::move as a way of telling the compiler that "we would
	// like to move this particular object if possible, and we swear that  
	// we're not going to use it again later".

	std::vector<int> v0{ 1,2,3,4,5 };

	std::move(v0); // no-op.

	v0.size(); // perfectly safe
}

std::vector<int> return_example() {
	// Another thing to be aware of is that using std::move when returning
	// from a function is unnecessary and sometimes detrimental, as it 
	// prevents RVO("Return Value Optimization").

	std::vector<int> v0{ 1,2,3,4,5 };

	// Wrong:
	 //return std::move(v0);

	// Correct
	 return v0;
}

struct foo {
	std::vector<int> v;
	std::vector<int> move_v() {
		// unlike the return_example, when moving data members it is appropriate
		// to use std::move.
		return std::move(this->v);
	}
};

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
	
	noop_example();

	std::vector<int> t{ return_example() };


	return 0;
}

