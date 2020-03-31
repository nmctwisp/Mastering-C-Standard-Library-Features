/*
NO ALLOCATION IS BETTER THAN ALLOCATION
---------------------------------------
- Making use of the stack and value semantic types should be preferred to dynamic allocation
- Objects on the stack are easier to reason about and more "predictable"
- Dynamic memory usage can have a significant cost: allocations are not free, they can 
reduce locality, and the compiler is often not able to aggressively optimize
- Sometimes allocations are necessary - allocate only when you need to
- Always use smart pointers - do not use new/delete

STD::UNIQUE_PTR AS YOUR FIRST CHOICE
------------------------------------
- If dynamic allocation is necessary, std::unique_ptr should be first choice.
- It is a zero-cost abstraction over new/delete (except for some rare cases).
- It models unique ownership, which is simple and easy to reason about.

STD:SHARED_PTR SHOULD BE USED SPARINGLY
---------------------------------------
- std::shared_ptr should be used sparingly.
- It is not a zero-cost abstraction over new/delete - it can have significant overhead due 
to atomic reference counting operations.
- Shared ownership can be harder to reason about.

ALWAYS USE STD::MAKE_XXX FUNCTIONS TO CREATE SMART POINTERS
-----------------------------------------------------------
- They prevent potential memory leaks
- They make the code terser and more readable
- They do not require new to be explicilty called
- They can greatly improve performance for std::shared_ptr

ROLE OF RAW POINTERS IN MODERN C++
----------------------------------
- In Modern C++, raw pointers are "optional references" to an object
- A raw pointer should never imply ownership
- As long as raw pointers are not managing memory, they're fine to use

SECTION SUMMARY
---------------
- Learn to follow the rule of zero and the rule of five
- Understood that the smart pointers can hold generic resources thanks to custom deleters
- Used "= default" where possible to let the compiler implicitly genereate a copy/move
operation.
*/