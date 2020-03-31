#include <iostream>
#include <memory>

// http://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared

// std::make_shared has all the advantages of std::make_unique:
// * Prevents memory leaks due to unspecified order of evaluation
// * Makes code terser and more readable
// * Doesn't require an explicit new call.

// std::make_shared has; however, one more very important feature: 
// it prevenets an unnecessary addtional allocation and improves cache 
// locality

//int main() {
//	// Consider the following code:
//	std::shared_ptr<int> s0{ new int{5} };
//	auto s2 = s0;
//	// The compiler is forced to allocate twice here:
//	// * Once for the int
//	// * Once for the shared_ptr's control block
//
//	// This is wasteful, as both allocations could be coalesced into one
//
//	// std::make_shared allows implementations to only allocate once for both 
//	// shared object and the control block.
//	
//	// Consider the following code:
//	auto s1 = std::make_shared<int>(5);
//	
//	// Only one allocation will be made, big enough for both int and the
//	// shared_ptr's control block.
//}