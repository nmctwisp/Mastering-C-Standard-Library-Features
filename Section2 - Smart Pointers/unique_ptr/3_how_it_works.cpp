#include <iostream>

// How does std::unique_ptr works? Why are move semantics necessary for it
// implementation? Lets answer those question by creating our own barebones
// unique_ptr.

template <typename T>
class my_unique_ptr {
private:
	T* ptr{ nullptr };
public:
	my_unique_ptr() = default;
	
	my_unique_ptr(T* ptr)
		: ptr{ ptr } {
	};

	~my_unique_ptr() {
		// Deleting a 'nullptr' is perfectly safe
		delete this->ptr;
	}

	// Deleting Copy Ctor & Copy Assignment to prevent copies being made 
	my_unique_ptr(const my_unique_ptr& ptr) = delete;
	my_unique_ptr& operator=(const my_unique_ptr& ptr) = delete;

	// Move Ctor and Move Assignment for Ownership Transfer
	my_unique_ptr(my_unique_ptr&& rhs) 
		: ptr{ rhs.ptr } {
		rhs.ptr = nullptr;
	}
	my_unique_ptr& operator=(my_unique_ptr&& rhs) {
		ptr = rhs.ptr;
		rhs.ptr = nullptr;
		return *this;
	}
};

int main() {
	my_unique_ptr<int> t {new int{ 1 }};

	auto k{ std::move(t) };

	my_unique_ptr<int> z;
	z = std::move(k);
	// https://godbolt.org/g/EdBxSu
}