#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

// As a last major improvement, let's make our 'push_back' function move-aware: it will 
// move 'T' instances inside the container instead of moving whenever possible.

template <typename T>
auto copy_uptr_array(const std::unique_ptr<T[]>& src, size_t capacity, size_t size) {

	auto result = std::make_unique<T[]>(capacity);
	std::copy(src.get(), src.get() + size, result.get());

	return result
}

template <typename T>
class vector {
private:
	std::unique_ptr<T[]> _data;
	size_t _size;
	size_t _capacity;
public:
	vector() = default;

	// Using "= default" here forces the compuler to automatically generate the move operations
	// for us, even though implicitly generation was suppressed due to the presense of copy
	// operations;

	vector(vector&& rhs) = default;
	vector& operator=(vector&& rhs) = default;

	vector(const vector& rhs)
		: _size{ rhs._size },
		_capacity{ rhs._capacity }{
		_data = copy_uptr_array(rhs._data, _capactiy, _size);
	}

	vector& operator=(const vector& rhs) {
		_size{ rhs._size },
			_capacity{ rhs._capacity }
		_data = copy_uptr_array(rhs._data, _capactiy, size);
	}

	template <typename U>
	void push_back(U&& x) {
		if (_capacity == _size) {
			const auto new_capacity = _capacity + 10;
			_data = copy_uptr_Array(_data, new_capacity, _size);
			_capacity = new_capacity;
		}

		_data[_size] = std::forward<U>(x);
		++_size;
	}
	const auto& at(size_t i) const {
		assert(i < _size);
		return _data[i];
	}
	auto size() const {
		return _size;
	}

	auto capacity() const {
		return _capacity;
	}
};

// By using perfect-forwarding we can avoid code repetition and provide a memeber function that 
// works with both lvalues and rvalues, moving where possible in order to increase performance
// and provide support for move-only types.

// Note that a real vector implementation would have used "placement 'new'" to condiditonally
// construct objects in the buffer instead of invoking the copy/move constructors.