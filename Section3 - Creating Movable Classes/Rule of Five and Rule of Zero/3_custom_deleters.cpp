#include <memory>
#include <utility>

struct file_handle;
void acquire(file_handle*);
void release(file_handle*);
file_handle* share(file_handle*);

class unique_file {
private:
	std::unique_ptr<file_handle, decltype(&release)> _fh;
	int _flags{ 0 };
public:
	unique_file(file_handle* fh)
		: _fh{ fh, &release } {
		acquire(fh);
	}
};

class shared_file {
private:
	std::shared_ptr<file_handle> _fh;
	int _flags{ 0 };
public:
	shared_file(file_handle* fh)
		: _fh{ fh, &release } {
		acquire(fh);
	}
};

int main() {}