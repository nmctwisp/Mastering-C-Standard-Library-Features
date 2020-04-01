#include <utility>

// Since C++14, an utility that's similar to std::swap has been introduced in the
// Standar Library.

template <typename T, typename U = T>
T exchange(T& obj, U&& new_value);

// std::exchange replaces obj with new_value, while returning the old value of obj.
// It relies on T and U supporting move operations.

// Here's a possible implementation

template <typename T, typename U = T>
T exchange(T& obj, U&& new_value) {
	// Temporarily store old value of obj
	T old_Value = std::move(obj);

	// Update obj with new_value
	obj = std::forward<U>(new_value);

	// Return the stored old_value
	return old_value;
}

// If both T and U implements efficient move operations, std::exchange is a very cheap way 
// of modeling "replacement where the previous value is interesting".
// The most common use case for std::exchange is implementing move operations for user-defined 
// types:

class barebones_uptr {
private:
	int* _p{ nullptr };
public:
	barebones_uptr() = default;
	barebones_uptr(int* p) : _p{ p } {};
	~barebones_uptr() { delete _p; };

	// Prevent Copies
	barebones_uptr(const barebones_uptr&) = delete;
	barebones_uptr& operator=(const barebones_uptr&) = delete;
	
	// Add Move Operators
	barebones_uptr(barebones_uptr&& rhs) 
		: _p{std::exchange(rhs._p, nullptr)} {
	}
	barebones_uptr& operator=(barebones_uptr&& rhs) {
		_p = std::exchange(rhs._p, nullptr);
		return *this;
	}
};
