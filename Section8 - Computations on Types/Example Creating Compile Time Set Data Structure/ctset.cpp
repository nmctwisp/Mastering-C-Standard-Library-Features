#include <tuple>
#include <type_traits>
#include <utility>

// Using C++17's "'auto' non-type template parameters" and 'inline' variables we 
// can easily define convenient shorthand notation for 'std::integral_constant'.
template <auto X>
inline constexpr std::integral_constant<decltype(X), X> c{};

// Our 'ct_set' data structure will store items thanks to a variadic parameter
// pack 'Items ...'.
template <typename ... Items>
struct ct_set {
	// Since 'this' is not usable as part of a constant expression, we'll define
	// a 'static' 'self()' member function that return a new instance of a
	// current set.
	static constexpr auto self() noexcept {

		return ct_set<Items ...>{};
	}

	// In order to check whether or not an item is in the set, we'll define a 
	// 'contains' function that takes an arbitrary item of type 'T' and uses
	// 'std::disjunction' to check if any of the stored 'Items ...' match 'T'.
	template <typename T>
	constexpr bool contains(T) const noexcept {
		return std::disjunction_v<std::is_same<T, Items> ...>;
	}

	// Adding an item 'x' to the set will return a new instance of:
	// * The same set, if the item is already available.
	// * A new set of 'T, Items ...', if the item is not available.
	template <typename T>
	constexpr auto add(T x) const noexcept {

		if  constexpr (self().contains(x))
			return self();
		else
			return ct_set<T, Items ...>{};
	}

	// Removing an item 'x' from the set will return a new instance of:
	// * The same set, if the item is not available available.
	// * A new set of 'Items ... - {T}', if the item is already available.
	template <typename T>
	constexpr auto remove(T x) const noexcept {

		if constexpr (!self().contains(x))
			return self();
		else {
			// clang-format off
			// A simple way of removing a particular type from a type list is by
			// using 'std::tuple' and 'std::tuple_cat'. Firstly, we'll wrap
			// every item that's not 'T' in an 'std::tuple'. The item that
			// matches 'T' will be transformed to an empty tuple.
			// Then 'std::tuple_cat' will concatenate & flatten the tuples.
			constexpr auto filtered = std::tuple_cat(
				std::conditional_t<
				std::is_same_v<T, Items>,
				std::tuple<>,
				std::tuple<Items>
				>{} ...
			);

			// Now that we have a tuple containing all types except 'T', we can 
			// use 'std::apply' in order to extract those types and get back a 
			// new instance of 'ct_set' without 'T'.
			return std::apply(
				[](auto ... xs) {
					return ct_set<decltype(xs) ...>{};
				}, filtered);
			// clang-format on
		}
	}
};

int main() {

	constexpr auto s0 = ct_set{};
	static_assert(!s0.contains(c<42>));

	constexpr auto s1 = s0.add(c<42>);
	static_assert(s1.contains(c<42>));

	constexpr auto s2 = s1.add(c<100>);
	static_assert(s2.contains(c<42>));
	static_assert(s2.contains(c<100>));

	constexpr auto s3 = s2.add(c<42>);
	static_assert(s3.contains(c<42>));
	static_assert(s3.contains(c<100>));

}