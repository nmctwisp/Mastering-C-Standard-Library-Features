#include <utility>
#include <vector>
#include <string>

// Let's say we are writing a class that represents a vector of words

class dictionary {
private:
	std::vector<std::string> _words;
public:
	// If we take 's' as a forwarding reference, we can then forward
	// it to the push_back method in order to acheive optimal behavior
	// without code reptition.

	template <typename T>
	void add(T&& s) {
		_words.push_back(std::forward<T>(s));
	}
};

// This works and it is now optimal. The only drawback is that 'add' is
// now is an unconstrained template, and might need constraints like 
// 'enable_if' to make it play nicely with overload resolution and produce
// better compiler errors.

//int main() {
//	dictionary d;
//	std::string s{ "Hello" };
//	d.add(s); // Should copy.
//	d.add(std::string{ "world" }); // should move
//}