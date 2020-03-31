#pragma once
#include <iostream>
#include <string>
#include <utility>

// Before C++11, it was common to tak "sink arguments"
// as const& and copy.

struct person1 {
	std::string _name;
	person1(const std::string& name);
	void set_name(const std::string& name);
};