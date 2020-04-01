#include <algorithm>
#include <cassert>
#include <cstddef>

// In this snippet we'll look at a bare-bones std::vector implementation, designed as if move 
// semantics did not exist. This will provide us with a real-world example of the "rule of three"
// in use.

// Please be aware that the code below:
// * Doesn't deal with exception safety
// * Doesn't deal with deferred construction of objects
// * Doesn't provide the entire std::vector interface
// This is just an bare-bones example focused on resource management and should not be seen as a
// valid std::vector implementation

template <typename T>
class vector {
private:
	T* _data{ nullptr };
	size_t _size{ 0 };
	size_t capacity{ 0 };
public:
	vector() = default;
	~vector() { delete[] _data };
	vector(const vector& rhs)
		: _size{ rhs._size },
		_capacity{ rhs._capacity } {
		
		_data = new T[_capacity];
		std::copy(rhs._data, rhs._data + _size, _data);
	}
	vector& operator=(const vector& rhs) {
		_size = rhs._size;
		_capacity = rhs.capacity;

		_data = new T[_capacity];
		std::copy(rhs._data, rhs._data + _size, _data);
		return *this;
	}

	void push_back(const T& x) {
		if (_capacity == _size) {
			const auto new_capacity = _capacity + 10;
			T* tmp = new T[new_capacity];
			std::copy(_data, _data + _capacity, tmp);
			std::swap(tmp, _data);
			delete[] tmp;
			
			_capacity = new_capacity;
		}
		_data[_size] = x;
		++_size;
	}

	const auto& at(std::size_t i) const {
		assert(i < size);
		return _data[i];
	}

	auto size() const {
		return _size;
	}

	auto capacity() const {
		return _capacity;
	}
};