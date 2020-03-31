#pragma once
#include <string>
#include <iostream>
#include <utility>

// Since C++11, we can support move operations for "sink arguments"
// to prevent unnecessary copies. 

// Here's a version of person with two overloads ctor 

struct person2 {
	std::string _name;
	person2(const std::string& name);
	person2(std::string&& name);
	void set_name(const std::string& name);
	void set_name(std::string&& name);
};