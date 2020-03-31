#include <memory>
#include <unordered_map>
#include <string>

template <typename T>
struct linked_list {
	T _value;
	std::unique_ptr<linked_list<T>> _next;
};

template <typename T>
struct binary_tree {
	T _value;
	std::unique_ptr<binary_tree<T>> _left;
	std::unique_ptr<binary_tree<T>> _right;
	binary_tree<T>* _parent;
};

struct texture;
struct mesh;
struct game_object {
	std::shared_ptr<texture> _texture;
	std::shared_ptr<mesh> _mesh;
};

template <typename T>
struct cache {
	std::unordered_map<std::string, std::weak_ptr<T>> _items;
};

int main() {
}