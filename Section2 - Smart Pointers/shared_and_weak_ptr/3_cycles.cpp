#include <iostream>
#include <cassert>
#include <memory>

// std::weak_ptr can be used to break dependency cycles of std::shared_ptr

void cycle() {
	struct b;
	struct a {
		std::shared_ptr<b> _b;
		~a() {
			std::cout << "~a()\n";
		}
	};

	struct b {
		std::shared_ptr<a> _a;
		~b() {
			std::cout << "~b()\n";
		}
	};

	auto sa = std::make_shared<a>();
	auto sb = std::make_shared<b>();
	sb->_a = sa;
	sa->_b = sb;
}

void weak_cycle() {
	struct b;
	struct a {
		std::shared_ptr<b> _b;
		~a() {
			std::cout << "~a()\n";
		}
	};

	struct b {
		std::weak_ptr<a> _a;
		~b() {
			std::cout << "~b()\n";
		}
	};

	auto sa = std::make_shared<a>();
	auto sb = std::make_shared<b>();
	sb->_a = sa;
	sa->_b = sb;
}

int main() {
	std::cout << "cycle()\n";
	cycle();

	std::cout << '\n';
	std::cout << "weak_cycle()\n";
	weak_cycle();
}