#include "3_ pbv_idiom.h"



person2::person2(const std::string& name)
	: _name{ name } {
}

person2::person2(std::string&& name)
	: _name{ std::move(name) } {
}

void person2::set_name(const std::string& name) {
	_name = name;
}

void person2::set_name(std::string&& name) {
	_name = std::move(name);
}

// This is optimal for the users of person2:
// * If they pass by lvalue, it will be copies
// * If they pass by rvalue, it will be moved

// This quickly gets out of hand, as we need to write 2^N 
// overloads for N arguments!