#pragma once

#include "RedBlackTree.h"

template<typename Key, typename T, typename Compare = std::less<Key>>
class Map
{
private:
	using Tree = RedBlackTree<Key, T, Compare>;

	Tree _tree;

public:
	using key_type = Key;
	using mapped_type = T;
	using value_type = typename Tree::value_type;
	using size_type = typename Tree::size_type;
	using iterator = typename Tree::iterator;
	using const_iterator = typename Tree::const_iterator;
	using reference = typename Tree::reference;
	using const_reference = typename Tree::const_reference;

	using iterator = typename Tree::iterator;
	using const_iterator = typename Tree::const_iterator;
	using reverse_iterator = typename Tree::reverse_iterator;
	using const_reverse_iterator = typename Tree::const_reverse_iterator;


	Map();
	explicit Map(const Compare& comp);
	Map(std::initializer_list<value_type> init);
	Map(const Map& other);
	Map(Map&& other) noexcept;
	~Map();

	Map& operator=(const Map& other);
	Map& operator=(Map&& other) noexcept;

	size_type size() const;
	bool empty() const;
	void clear();

	mapped_type& operator[](const key_type& key);
	const mapped_type& operator[](const key_type& key) const;

	mapped_type& at(const key_type& key);
	const mapped_type& at(const key_type& key) const;

	std::pair<iterator, bool> insert(const value_type& value);

	std::pair<iterator, bool> insert_or_assign(const key_type& key, const T& value);
	std::pair<iterator, bool> insert_or_assign(const key_type& key, T&& value);

	bool erase(const key_type& key);

	iterator find(const key_type& key);
	const_iterator find(const key_type& key) const;

	bool contains(const key_type& key) const;

	iterator lower_bound(const key_type& key);
	const_iterator lower_bound(const key_type& key) const;

	iterator upper_bound(const key_type& key);
	const_iterator upper_bound(const key_type& key) const;

	void swap(Map& other) noexcept;

	void merge(Map& other);

	template<typename... Args>
	std::pair<iterator, bool> emplace(Args&&... args);

	template<typename... Args>
	std::pair<iterator, bool> try_emplace(const key_type& key, Args&&... args);

	template<typename... Args>
	std::pair<iterator, bool> try_emplace(key_type&& key, Args&&... args);

	value_type extract(const key_type& key);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;

	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	// --- Comparison operators ---
	template<typename K, typename V, typename C>
	friend bool operator==(const Map<K, V, C>&, const Map<K, V, C>&);

	template<typename K, typename V, typename C>
	friend bool operator!=(const Map<K, V, C>&, const Map<K, V, C>&);

	template<typename K, typename V, typename C>
	friend bool operator<(const Map<K, V, C>&, const Map<K, V, C>&);

	template<typename K, typename V, typename C>
	friend bool operator<=(const Map<K, V, C>&, const Map<K, V, C>&);

	template<typename K, typename V, typename C>
	friend bool operator>(const Map<K, V, C>&, const Map<K, V, C>&);

	template<typename K, typename V, typename C>
	friend bool operator>=(const Map<K, V, C>&, const Map<K, V, C>&);

	template<typename K, typename V, typename C>
	friend void swap(Map<K, V, C>&, Map<K, V, C>&) noexcept;
};

template<typename Key, typename T, typename Compare>
inline Map<Key, T, Compare>::Map() = default;

template<typename Key, typename T, typename Compare>
inline Map<Key, T, Compare>::Map(const Compare& comp)
	: _tree(comp)
{
}

template<typename Key, typename T, typename Compare>
inline Map<Key, T, Compare>::Map(std::initializer_list<value_type> init)
	: _tree()
{
	for (const auto& value : init)
		_tree.insert(value);
}

template<typename Key, typename T, typename Compare>
inline Map<Key, T, Compare>::Map(const Map& other)
	: _tree(other._tree)
{
}

template<typename Key, typename T, typename Compare>
inline Map<Key, T, Compare>::Map(Map&& other) noexcept
	: _tree(std::move(other._tree))
{
}

template<typename Key, typename T, typename Compare>
inline Map<Key, T, Compare>::~Map() = default;

template<typename Key, typename T, typename Compare>
inline Map<Key, T, Compare>& Map<Key, T, Compare>::operator=(const Map& other)
{
	if (this != &other)
		_tree = other._tree;
	return *this;
}

template<typename Key, typename T, typename Compare>
inline Map<Key, T, Compare>& Map<Key, T, Compare>::operator=(Map&& other) noexcept
{
	if (this != &other)
		_tree = std::move(other._tree);
	return *this;
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::size_type Map<Key, T, Compare>::size() const
{
	return _tree.size();
}

template<typename Key, typename T, typename Compare>
bool Map<Key, T, Compare>::empty() const
{
	return _tree.empty();
}

template<typename Key, typename T, typename Compare>
void Map<Key, T, Compare>::clear()
{
	_tree.clear();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::mapped_type& Map<Key, T, Compare>::operator[](const key_type& key)
{
	auto [it, inserted] = _tree.insert({ key, T{} });
	return it->second;
}

template<typename Key, typename T, typename Compare>
const typename Map<Key, T, Compare>::mapped_type& Map<Key, T, Compare>::operator[](const key_type& key) const
{
	auto [it, inserted] = _tree.insert({ key, T{} });
	return it->second;
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::mapped_type& Map<Key, T, Compare>::at(const key_type& key)
{
	auto it = _tree.find(key);
	if (it == end())
		throw std::out_of_range("Map::at: key not found");
	return it->second;
}

template<typename Key, typename T, typename Compare>
const typename Map<Key, T, Compare>::mapped_type& Map<Key, T, Compare>::at(const key_type& key) const
{
	auto it = _tree.find(key);
	if (it == end())
		throw std::out_of_range("Map::at: key not found");
	return it->second;
}

template<typename Key, typename T, typename Compare>
std::pair<typename Map<Key, T, Compare>::iterator, bool> Map<Key, T, Compare>::insert(const value_type& value)
{
	return _tree.insert(value);
}

template<typename Key, typename T, typename Compare>
inline std::pair<typename Map<Key, T, Compare>::iterator, bool> 
		Map<Key, T, Compare>::insert_or_assign(const key_type& key, const T& value)
{
	auto [it, inserted] = _tree.insert({ key, value });
	if (!inserted)
		it->second = value;
	return { it, inserted };
}

template<typename Key, typename T, typename Compare>
inline std::pair<typename Map<Key, T, Compare>::iterator, bool> 
		Map<Key, T, Compare>::insert_or_assign(const key_type& key, T&& value)
{
	auto [it, inserted] = _tree.insert({ key, std::move(value) });
	if (!inserted)
		it->second = std::move(value);
	return { it, inserted };
}

template<typename Key, typename T, typename Compare>
bool Map<Key, T, Compare>::erase(const key_type& key)
{
	return _tree.erase(key);
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::find(const key_type& key)
{
	return _tree.find(key);
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::find(const key_type& key) const
{
	return _tree.find(key);
}

template<typename Key, typename T, typename Compare>
bool Map<Key, T, Compare>::contains(const key_type& key) const
{
	return _tree.contains(key);
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::lower_bound(const key_type& key)
{
	return _tree.lower_bound(key);
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::lower_bound(const key_type& key) const
{
	return _tree.lower_bound(key);
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::upper_bound(const key_type& key)
{
	return _tree.upper_bound(key);
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::upper_bound(const key_type& key) const
{
	return _tree.upper_bound(key);
}

template<typename Key, typename T, typename Compare>
inline void Map<Key, T, Compare>::swap(Map& other) noexcept
{
	std::swap(_tree, other._tree);
}

template<typename Key, typename T, typename Compare>
inline void Map<Key, T, Compare>::merge(Map& other)
{
	for (auto it = other.begin(); it != other.end(); )
	{
		auto current = it++;
		if (!_tree.contains(current->first))
		{
			_tree.insert(*current);
			other._tree.erase(current->first);
		}
	}
}

template<typename Key, typename T, typename Compare>
template<typename... Args>
std::pair<typename Map<Key, T, Compare>::iterator, bool> Map<Key, T, Compare>::emplace(Args&&... args)
{
	return _tree.emplace(std::forward<Args>(args)...);
}

template<typename Key, typename T, typename Compare>
template<typename... Args>
inline std::pair<typename Map<Key, T, Compare>::iterator, bool> 
		Map<Key, T, Compare>::try_emplace(const key_type& key, Args&&... args)
{
	auto [it, inserted] = _tree.insert({ key, T{} });
	if (inserted)
		it->second = T(std::forward<Args>(args)...);
	return { it, inserted };
}

template<typename Key, typename T, typename Compare>
template<typename... Args>
inline std::pair<typename Map<Key, T, Compare>::iterator, bool> Map<Key, T, Compare>::try_emplace(key_type&& key, Args&&... args)
{
	auto [it, inserted] = _tree.insert({ key, T{} });
	if (inserted)
		it->second = T(std::forward<Args>(args)...);
	return { it, inserted };
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::value_type Map<Key, T, Compare>::extract(const key_type& key)
{
	auto it = _tree.find(key);
	if (it == _tree.end())
		throw std::out_of_range("Map::extract: key not found");

	value_type result = *it;
	_tree.erase(key);
	return result;
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::begin()
{
	return _tree.begin();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::iterator Map<Key, T, Compare>::end()
{
	return _tree.end();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::begin() const
{
	return _tree.begin();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::end() const
{
	return _tree.end();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::cbegin() const
{
	return _tree.cbegin();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_iterator Map<Key, T, Compare>::cend() const
{
	return _tree.cend();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::reverse_iterator Map<Key, T, Compare>::rbegin()
{
	return _tree.rbegin();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::reverse_iterator Map<Key, T, Compare>::rend()
{
	return _tree.rend();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_reverse_iterator Map<Key, T, Compare>::rbegin() const
{
	return _tree.rbegin();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_reverse_iterator Map<Key, T, Compare>::rend() const
{
	return _tree.rend();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_reverse_iterator Map<Key, T, Compare>::crbegin() const
{
	return _tree.crbegin();
}

template<typename Key, typename T, typename Compare>
typename Map<Key, T, Compare>::const_reverse_iterator Map<Key, T, Compare>::crend() const
{
	return _tree.crend();
}

template<typename K, typename V, typename C>
bool operator==(const Map<K, V, C>& lhs, const Map<K, V, C>& rhs)
{
	return lhs._tree == rhs._tree;
}

template<typename K, typename V, typename C>
bool operator!=(const Map<K, V, C>& lhs, const Map<K, V, C>& rhs)
{
	return !(lhs == rhs);
}

template<typename K, typename V, typename C>
bool operator<(const Map<K, V, C>& lhs, const Map<K, V, C>& rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename K, typename V, typename C>
bool operator<=(const Map<K, V, C>& lhs, const Map<K, V, C>& rhs)
{
	return !(rhs < lhs);
}

template<typename K, typename V, typename C>
bool operator>(const Map<K, V, C>& lhs, const Map<K, V, C>& rhs)
{
	return rhs < lhs;
}

template<typename K, typename V, typename C>
bool operator>=(const Map<K, V, C>& lhs, const Map<K, V, C>& rhs)
{
	return !(lhs < rhs);
}

template<typename K, typename V, typename C>
void swap(Map<K, V, C>& lhs, Map<K, V, C>& rhs) noexcept
{
	lhs.swap(rhs);
}