#include <iostream>
#include <memory>

// std::shared_ptr<T> is a copyable class that represents shared ownership over a dynamically
// allocated object. It uses reference counting to keep track of how many alive owners are present 
// and releases the memory when that count reaches zero.

// Copying a std::shared_ptr shares ownership
// Moving a std:::shared_ptr transfers ownership

struct foo {
	foo() { std::cout << "foo::foo()\n"; };
	~foo() { std::cout << "~foo::foo()\n"; };
};

void sharing() {
	std::shared_ptr<foo> keep_alive; 
	{
		std::shared_ptr<foo> f0{ new foo };
		auto f1 = f0;
		auto f2 = f0;
		auto f3 = f1;
		keep_alive = f2;
	// f0, f1, f2 and keep_alive are all valid here.
	}
	// Even though f0, f1 and f2 have been destroyed here, the foo instance originally created
	// under f0's constructor is still alive and accessible via keep_alive.

	// You can see that although the resource is acquired in a nested scope, it can be
	// kept alive by sharing it with an owner living outside of the scope.
}


void transferring() {
	std::shared_ptr<foo> f0{ new foo };
	auto f1 = std::move(f0);
}

// http://en.cppreference.com/w/cpp/memory/shared_ptr

//int main() {
//	sharing();
//	transferring();
//}