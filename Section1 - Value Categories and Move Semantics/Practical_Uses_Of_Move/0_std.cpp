#include "0_std.h"

struct foo {};

void pair_and_tuple() {
	// General-purpose utulity classes such as std::pair and std::tuple
	// are move-aware.

	std::pair<foo, int> p;
	auto p_copy = p;
	auto p_move = std::move(p);

	// If the items contained in them have valid move operations, they will
	// properly used when moving the pair/tuple.

	std::tuple<foo, int, char> t;
	auto t_copy = t;
	auto t_move = std::move(t);
}

void containers() {
	// Every container in C++ is move-aware one way or another. The entire 
	// container can be moved to a destination, or items can be moved
	// inside the containers.

	std::vector<foo> v{ foo() };
	auto v_copy = v;
	auto v_move = std::move(v);

	// Moves the temporary inside the vector.
	v.push_back(foo{});

	// Copies "f" inside the vector.
	foo f;
	v.push_back(f);

	// Moves "f" inside the vector.
	v.push_back(std::move(f));
}

void move_only() {

	// Some classes provided by the Standard Library can only be 
	// moved. These classes represent "unique ownership" over a
	// a resource: copying them would be nonsensival.

	std::thread t{ [] {std::cout << "hello!"; } };
	//auto t_copy = t;		// Does not compile
	auto t_move = std::move(t);
	//t_move.detach();
	t_move.join();

	// Similarly, "unique_lock" and "unique_ptr" are move-only.

	std::mutex m;
	std::unique_lock<std::mutex> ul{ m };
	//auto ul_copy = ul;	// Does not compile
	auto ul_move = std::move(ul);

	std::unique_ptr<int> up = std::make_unique<int>(1);
	//auto up_copy = up;	// Does not compile
	auto up_move = std::move(up);

}