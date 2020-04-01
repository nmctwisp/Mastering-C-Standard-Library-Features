#include <utility>

struct file_handle;
void acquire(file_handle*);
void release(file_handle*);
file_handle* share(file_handle*);

// Using the same example as before, let's now followi the "rule of five" to implement
// move operations

class file {
private:
	file_handle* _fh;
	int _flags{ 0 };
public:
	~file() {
		release(_fh);
	}

	file(const file& rhs)
		: _fh{ share(rhs._fh) },
		  _flags{ rhs._flags }{
	}

	file& operator=(const file& rhs) {
		_fh = share(rhs._fh);
		_flags = rhs._flags;
		return *this;
	}
	
	file(file&& rhs) noexcept
		: _fh{ std::exchange(rhs._fh, nullptr) },
		  _flags{ rhs._flags } {
	}

	file& operator=(file&& rhs) noexcept {
		_fh = std::exchange(rhs._fh, nullptr);
		_flags = rhs._flags;
		return *this;
	}
};