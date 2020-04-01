/*
MOVABLE TYPES - WHY?
--------------------
- Writing classes that support move operations can greatly increase performance, safety and 
expressiveness of your code
- The Standard Library provides many utilities that make use of move semantics where possible,
even for user-defined types

OTHER CONTAINERS
----------------
- All the commonly used Standard Library containers are move-aware and support emplacement
- Examples: std::vector, std::map, std::set and std::list.

UTILITY FUNCTIONS AND CLASSES
-----------------------------
- Many utility functions and classes support or are defined in terms of move semantics
- Common utilities: std::swap and std::Exchange
- Wrappers: std::pair and std::tuple
- Algorithms: std::move_iterator
*/