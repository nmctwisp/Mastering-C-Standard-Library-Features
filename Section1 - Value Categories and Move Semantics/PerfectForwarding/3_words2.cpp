#include <utility>
#include <vector>
#include <string>

// Let's say we are writing a class that represents a vector of words

class dictionary {
private:
	std::vector<std::string> _words;
public:
	// We could use the "pass-by-value and move" idiom
	void add(std::string s) {
		_words.push_back(std::move(s));
	}
};

// This works, but not optimal. An extra move is executed on every
// invocation of "add".

//int main() {
//	dictionary d;
//	std::string s{ "Hello" };
//	d.add(s); // Should copy.
//	d.add(std::string{ "world" }); // should move
//}