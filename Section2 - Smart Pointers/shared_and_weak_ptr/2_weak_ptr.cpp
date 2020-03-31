#include <iostream>
#include <cassert>
#include <memory>

// std::weak_ptr can only be constructed from instances of std::shared_ptr or
// other weak_ptrs.
// http://en.cppreference.com/w/cpp/memory/weak_ptr

// weak_ptr can be used to check whether or not an object managed by shared_ptr
// is alive:

void checking_existence() {
	std::weak_ptr<int> wp;

	assert(wp.use_count() == 0);
	assert(wp.expired());

	{
		auto sp = std::make_shared<int>(42);
		wp = sp;

		assert(wp.use_count() == 1);
		assert(!wp.expired());

		auto sp2 = sp;

		assert(wp.use_count() == 2);
		assert(!wp.expired());
	}	
	assert(wp.use_count() == 0);
	assert(wp.expired());
}

// Accessing an object through an std::weak_ptr requires conversion to 
// std::shared_ptr first:

void accessing_object() {
	// http://en.cppreference.com/w/cpp/memory/weak_ptr/lock

	std::weak_ptr<int> wp;
	assert(wp.lock() == nullptr);

	auto sp = std::make_shared<int>(42);
	wp = sp;
	auto sp2 = wp.lock(); // returns a new shared_pointer so you can access
	assert(*sp2 == 42);
}

//int main() {
//	checking_existence();
//	accessing_object();
//}