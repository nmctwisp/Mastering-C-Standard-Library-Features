#pragma once
#include <iostream>
#include <string>
#include <utility>

// Fortunately, the pass-by-value and move idiom comes to our rescue.

struct person3 {
	std::string _name;
	person3(std::string name);
	void set_name(std::string name);
};