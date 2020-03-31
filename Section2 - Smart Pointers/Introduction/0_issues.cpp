#include <vector>

// Before C++11, dynamic memory management in C++ has been traditionally done through
// the use of the 'new' and 'delete' keywords.

struct foo {};

int memory_leak() {
	int* x = new int{ 42 };
	return *x;
}

void double_free() {
	int* x = new int{ 42 };
	delete x;
	delete x; // Undefined Behavior
}

int use_after_free() {
	int* x = new int{ 42 };
	delete x;

	return *x; // Undefined Behavior
}

void bar(int* x) {
	// Who owns 'x'
	// Am I supposed to 'delete' it?
	// Can I assume that it is a NOT a nullptr?
}

struct abc {
	std::vector<foo*> _foos;

	// Is 'abc' responsible for allocating and cleaning up the items of '_foos'?
	// Does 'abc' only refer to 'foo' instances?
	// Should 'abc' be copyable? What should the destructor of 'abc' do?
};

int main() {
	// The 'new' keyword allocates memory for a 'foo' instance, constructs it, and
	// returns a pointer to the newly-allocated memory location
	foo* f = new foo;

	// The 'delete' keyword destroys the instance of 'foo' allocated at the address of 'f',
	// then reclaims the dynamically allocated memory for future reuse
	delete f;

	// There are some major problems with the use of 'new' and 'delete':

	// * They are error prone. Forgetting to use the 'delete' keyword or using it multiple 
	// times can lead to "memory leaks" or "double-free" errors, which can harm stability or
	// introduce security problems. Accessing a pointer after 'delete' has been called is 
	// another very dangerous mistake.

	memory_leak();
	double_free();
	use_after_free();

	// * They increase conigitive overhead on devs and people reading/reviewing the code. As
	// soon as a pointer is spotted in a code base, many questions have to be asked:
	// Was the pointer allocated dynamically?
	// Am I suppose to 'delete' the pointer after using it?
	// Who is the owner of the allocated memory?
	// and, so on...
	int* x = new int{ 1 };
	bar(x);
	
	abc d{};
}