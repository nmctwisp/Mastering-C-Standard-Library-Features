#include <utility>

struct file_handle;
void acquire(file_handle*);
void release(file_handle*);
file_handle* share(file_handle*);

// In the previous code examples, the file class was dealing with multiple tasks:
// - Managing the file_handle resource
// - providing the _flags memeber variable

// Let's apply the "rule of zero" to the 'file' class: the resource management logic can be
// extracted to a separare 'shared_file_handle' class that follows the "rule of five", while
// 'file' becomes very simple (following the SRP).

class shared_file_handle {
private:
	file_handle* _fh;
public:
	~shared_file_handle() {
		release(_fh);
	}
	shared_file_handle(const shared_file_handle& rhs)
		: _fh{ share(rhs._fh) } {
	}
	shared_file_handle& operator=(const shared_file_handle& rhs) {
		_fh = share(rhs._fh);
		return *this;
	}
	shared_file_handle(shared_file_handle&& rhs) noexcept
		: _fh{ std::exchange(rhs._fh, nullptr) } {
	}
	shared_file_handle& operator=(shared_file_handle&& rhs) noexcept {
		_fh = std::exchange(rhs._fh, nullptr);
		return *this;
	}
};

class file {
private:
	int _flags{ 0 };
public:
	~file() = default;
	file(const file& rhs) = default;
	file(file&& rhs) = default;
	file& operator=(const file& rhs) = default;
	file& operator=(file&& rhs) = default;
};