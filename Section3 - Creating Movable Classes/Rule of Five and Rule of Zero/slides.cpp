/*
Rule of Three
-------------
- Before C++11, the rule of three claims that:
	- If you have a class explicitly defining one of the following:
		- Destructor
		- Copy Constructor
		- Copy Assignment
	- Then it should probably define all three
- This prevents mistakes and oversights when implementing classes that manage resources
- After C++11, the "rule of three" was extended to the "rule of five"

Rule of Five
------------
- The rule of five claims that:
	- If you have a class explicitly defining one of the following
		- Destructor
		- Copy Constructor
		- Copy Assignment
		- Move Constructor
		- Move Assignment
	- Then it should probably define all five

Rule of Zero
------------
- The rule of zero encourages you to avoid implementing any copy/move operations for your
classes, and to rely on the value semantics of existing types.
- The idea is that custom copy.move/dtor are usually implemented to deal with resource 
management and ownership - If that's the case, then the SRP encourages to extract this 
functonality to a separate class
*/