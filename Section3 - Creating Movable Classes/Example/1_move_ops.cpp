#include <algorithm>
#include <cassert>
#include <cstddef>

// In this snippet we'll add move operations to our bare-bones std::vector implementation. We 
// will follow the "rule of five"

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
	vector(vector&& rhs)
		: _data{ std::exchange(rhs._data, nullptr) }
		_size{ rhs._size },
		_capacity{ rhs._capacity } {
	}

	vector& operator=(vector&& rhs) {
		_data = std::exchange(rhs._data, nullptr)
		_size = rhs._size;
		_capacity = rhs.capacity;

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