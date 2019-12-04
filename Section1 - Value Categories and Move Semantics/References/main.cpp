#include <iostream>

void foo(int& num) {
	std::cout << "Non-Const L-Value Reference" << std::endl;
}

void foo(int&& num) {
	std::cout << "Non-Const R-Value Reference" << std::endl;
}

void foo(const int& num) {
	std::cout << "Const L-Value Reference" << std::endl;
}

void bar(const int&) {
	std::cout << "Const L-Value Reference" << std::endl;
}

int* func1(int& a) {
	return &a;
}

int& func2(int& a) {
	return a;
}

int main() {
	int a = 0;

	foo(a); // Non-Const L-Value Reference
	foo(5); // Non-Const R-Value Reference
	
	const int b = 0;
	foo(b); // Const L-Value Reference

	bar(a); // Const L-Value Reference
	bar(5); // Const L-Value Reference

	int* y = func1(a);
	int* x = &func2(a);
}