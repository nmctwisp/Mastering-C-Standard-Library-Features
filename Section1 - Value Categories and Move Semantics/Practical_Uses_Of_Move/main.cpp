#include "0_std.h"
#include "1_move.h"
#include "2_ pbv_idiom.h"
#include "3_ pbv_idiom.h"
#include "4_ pbv_idiom.h"


int main() {
	// Move Semantics in the Standard Library
	// - Many classes in the standard library are "move aware"
	// - Some classes represent "unique ownership" and are move-only
	pair_and_tuple();
	containers();
	move_only();

	// Avoiding Unnecessary Performance Hits with std::move
	// - Moving objects into containers
	// - Moving containers instead of copying
	// - Acception rvalue references as function arguments
	moving_into_containers();
	moving_containers_instead_of_copying();
	return 0;
}