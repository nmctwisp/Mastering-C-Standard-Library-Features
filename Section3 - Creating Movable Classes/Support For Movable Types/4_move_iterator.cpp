#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

// The Standard Library provides a huge number of general-purpose algorithms in the <algorithm> header.
// These algorithms mostly operate on iterator points.

// Some new move-aware algorithms have been introduced in C++11:
// * move
// * move_backward

// But most of the existing algorithms are not move-aware. Fortunately, std::move_iterator and
// std::make_move_iterator have been added to the <iterator> header. This allows users to adapt existing
// iterators so hat they move upon dereference.

bool has_five_chars(const std::string& s) {
	return s.size() == 5;
}

// The example below will copy all the strings with five characters from src to dest.
void example_copy() {
	std::vector<std::string> src{ "hello", "world", "aaa" };
	std::vector<std::string> dest;
	
	std::copy_if(std::begin(src), std::end(src), std::back_inserter(dest), has_five_chars);
}

// By wrapping the src iterators with std::make_move_iterator, the objects satisfying the has_five_chars
// predicate will be moved instead.
void example_move() {
	std::vector<std::string> src{ "hello", "world", "aaa" };
	std::vector<std::string> dest;

	std::copy_if(std::make_move_iterator(std::begin(src)),
				std::make_move_iterator(std::end(src)),
				std::back_inserter(dest),
				has_five_chars);
}