#include "4_ pbv_idiom.h"

person3::person3(std::string name)
	: _name{ std::move(name) } {
}
void person3::set_name(std::string name) {
	_name = std::move(name);
}

// By taking "sink arguments" by value and then unconditionally
// moving them, we can achieve close-to-optimal behavior:
// * LValue => 1 copy + 1 move
// * RValue => 2 moves

// Since moves are cheap, the extra move is worth not having to 
// provide 2^N overloads.