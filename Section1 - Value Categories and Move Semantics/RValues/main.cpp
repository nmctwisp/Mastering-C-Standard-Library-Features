int bar() { return 5; }

int main() {

	// R-values can NOT appear on the left side of the
	// built-in assignment operator:
	// >> 5 = 0;
	// >> bar() = 0;

	// the address of r-values CANNOT be taken:
	// >> &5;
	// >> &bar;

	// R-values do NOT bing to l-value references:
	// >> int& lv_ref0 = 5;
	// >> int& lv_ref1 = bar();

	//R-values bind to r-value references, introduced in C++11:
	
	int&& rv_ref0 = 5;
	int&& rv_ref1 = bar();

	// Examples of R-Values:
	// (1) Numeric Literals
	5;
	10.33f;

	// (2) Built-in arithmetic expressions:
	5 + 10 * 3;

	// (3) Function calls returning non-references;
	bar();
}