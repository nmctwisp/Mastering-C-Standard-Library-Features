#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

struct person {
	std::string _name;
	int _age;
	person(std::string name, int age)
		: _name{ name }, _age{ age }{};
};

std::vector<person> ps{ {"Jack",15}, {"Amy", 21}, {"Sara", 30}, /*{"", 50}*/ };

struct player_status {
	int _level;
	player_status(int level) : _level{ level } {};
	bool operator==(int rhs) {
		return _level == rhs;
	};
};

std::vector<player_status> players{ 1,2,3,4,5,7,1,2,21,10,10,10, 70};
std::vector<std::string> ids{ "U.1001", "U.1002", "G.AAAA", "G.AAAB", "U.1003" };

int main() {
	std::vector<int> v{ 0,1,2,3 };
	std::for_each(std::begin(v), std::end(v), 
		[](int x) { std::cout << x << std::endl; });

	std::for_each(std::execution::seq,
		std::begin(v), std::end(v),
		[](int x) { std::cout << x << std::endl; });

	const bool can_drink = std::all_of(std::begin(ps), std::end(ps), 
		[](const auto& x) {return x._age >= 21; });

	const bool all_have_name = std::none_of(
		std::execution::par_unseq,
		std::begin(ps), std::end(ps),
		[](const auto& x) {return x._name.empty(); });

	const bool any_over_21 = std::any_of(
		std::execution::par_unseq,
		std::begin(ps), std::end(ps),
		[](const auto& x) {return  x._age > 21; }
	);

	const auto cnt_player_levels = std::count(std::begin(players), std::end(players), 10);
	const auto high_level_players = std::count_if(std::begin(players), std::end(players),
		[](const auto& x) {return x._level > 10; }
	);
		

	const auto it = std::partition(
		std::begin(ids), std::end(ids),
		[](const auto& x) {
			return x.size() > 2 && x[0] == 'U' && x[1] == '.';
		}
	);

	std::for_each(std::begin(ids), it,
		[](const auto& uid) {
			std::cout << "userid: " << uid << '\n';
		}
	);

	std::for_each(it, std::end(ids),
		[](const auto& gid) {
			std::cout << "groupid: " <<  gid << std::endl;
		}
	);
	return 0;
}