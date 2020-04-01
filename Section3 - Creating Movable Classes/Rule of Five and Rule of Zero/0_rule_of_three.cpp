// To show an example of the "rule of three" in action, imagine some sort of 'file_handle' pointer
// type that is a "resource" which can be acquired, released and shared.

struct file_handle;
void acquire(file_handle*);
void release(file_handle*);
file_handle* share(file_handle*);

// Imagine that we wnat to create a RAII wrapper around the C-like 'file_handle' that will automatically
// deal with resource acquistiion/release and with ownership sharing.

class file {
private:
	file_handle* _fh;
	int _flags{ 0 };
public:
	~file() {
		release(_fh);
	}
	// Following the "rule of three", as soon as you have a user-defined destructor, you should probably 
	// define copy operations as well.

	file(const file& rhs)
	:	_fh{ share(rhs._fh) },
		_flags{rhs._flags}{
	}

	file& operator=(const file& rhs) {
		_fh = share(rhs._fh);
		_flags = rhs._flags;
		return *this;
	}

	// Explicitly defining copy operations, prevents move operations from being automatically generated
	// by the compiler. We'll see soon how to explicitly define them using the "rule of file"
};
