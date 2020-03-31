/*
SHARED OWNERSHIP
* Some resources need to be shared between multiple owners
* After acquisition of a resource, multiple objects can take/lose ownership of it.When resource 
has no more owners, it is automatically released
* Useful where there isn't a clear lifetime for a particular resource (for example the lifetime
might be depend on run-time conditions).
*/