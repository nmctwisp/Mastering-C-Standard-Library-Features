#include "2_ pbv_idiom.h"


person1::person1(const std::string& name)
	: _name{ name } {
	// when initializing with an rvalue, the class is initalized with
	// a copy of the rvalue, which in unnecessary
}
void person1::set_name(const std::string& name) {
	_name = name;
	// when setting with an rvalue, setter essentially makes a
	// a copy of the rvalue, which in unnecessary
}
