#include "1_move.h"

std::string read_large_file(int index) {
	std::string greeting{ "hello" };
	size_t i{ (index % greeting.size()) };
	std::string result{ greeting.at(i) };
	return result;
}

std::vector<int> get_multiples(int x) { return std::vector<int>{x}; }

void consume_multiples(std::map<int, std::vector<int>> m) {};

void moving_into_containers() {
	// As briefly mentioned earlier, moving into containers can
	// be a huge performance win.Consider the case where we read 
	// large files into an std::string, then put the string inside 
	// an std::vector.

	std::vector<std::string> files;
	files.reserve(10);
	for (int i = 0; i < 10; ++i) {
		std::string s = read_large_file(i);
		// ... do some processing on "s" ...

		// Original Version
		// files.push_back(s); 

		// What is wrong with the code above? How can we improve it?
		// Answer: s is being copied and placed inside the file vector

		// Improved Version
		files.push_back(std::move(s));
	}
}

void moving_containers_instead_of_copying() {
	// std::string is a container of characters. The example we looked at 
	// above applies to any other container, but sometimes it is less obvious.
	// It is fairly common to have an std::map where the value is another
	// container.

	std::map<int, std::vector<int>> multiples_of;

	for (int i = 0; i < 100; ++i) {
		auto i_multiples = get_multiples(i);

		// Original Version
		// multiples_of[i] = i_multiples;

		// What is wrong with the code above? How can we improve it?
		// Answer: i_multiples is being copied and placed inside the map

		// Improved Version
		multiples_of[i] = std::move(i_multiples);

		// Alternate Version
		// multiples_of[i] = get_multiples(i);
	}

	// Original Version
	// consume_multiples(multiples_of);

	// What is wrong with the code above? How can we improve it?
	// Answer: multiples_of is being copied and pass by value

	consume_multiples(std::move(multiples_of));
}