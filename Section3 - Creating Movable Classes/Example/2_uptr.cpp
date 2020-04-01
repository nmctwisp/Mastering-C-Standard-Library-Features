#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

// Let's now think about the design of our vector clone. The vector class is both responsible
// for management of a dynamically-allocated bufffer and a "_size" that keeps track of how many 
// elements are in the container.

// Let's try to apply the "rule of zero" and move as much resource management code as possible 
// in a separate class. Luckily, std::unique_ptr is a great fit here.

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

	const auto& at(size_t i) const {
		assert(i < _size);
		return _data[i];
	}
};


// Due to the fct that our copy operations have to take the _size memeber variable into account,
// the "rule of zero" cannot be completely applied in this situation, atleast without significant
// refactoring.

// Being able to "= default" the move operations; however, prevents possible mistakes and increases
// maintainability and readability of the code. Getting rid of the manual memory management prevents 
// potential security-critical pitfalls that we've seen previously.