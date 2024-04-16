#pragma once
#include<iostream>

namespace hash_table {
	template<class K, class V>
	class HashTable {
	public:
		struct Pair {
			int _key;
			V _value;
			Pair(K key, V value) : _key(key), _value(value) {}
			Pair():_key(K()), _value(V()) {}
		};
		HashTable(size_t capacity) : _capacity(capacity), _size(0), _data(new Pair[capacity]) {
			for (size_t i = 0; i < capacity; i++)
			{
				_data[i] = Pair();
			}
		}
		void insert(K key, V value) {
			int index = hash(key);
			int i = 0;
			bool full_cycle = false;
			while (!full_cycle) {
				if (_data[(index + i) % _capacity]._key == K()) {
					_data[index] = Pair(key, value);
					++_size;
					return;
				}
				++i;
				if ((index + i) % _capacity == index) full_cycle = true;
			}
		}
		void insert_or_assign(K key, V value) {
			int index = hash(key);
			if (_data[index]._key == K()) _data[index] = Pair(key, value);
			else _data[index]._value = value;
		}
		void print() const {
			for (size_t i = 0; i < _capacity; i++)
			{
				std::cout << "Key: " << _data[i]._key << ", " << "Value: " << _data[i]._value << std::endl;
			}
			std::cout << std::endl;
		}
		bool contains(V value) {
			for (size_t i = 0; i < _capacity; i++)
			{
				if (_data[i]._value == value) return true;
			}
			return false;
		}
		V* search(K key) {
			int index = hash(key);
			int i = 0;
			bool full_cycle = false;
			while (!full_cycle) {
				if (_data[(index + i) % _capacity]._key == key) return &_data[(index + i) % _capacity]._value;
				else ++i;
				if ((index + i) % _capacity == index) full_cycle = true;
			}
			return nullptr;
		}
	private:
		int _size;
		int _capacity;
		Pair* _data;
		int hash(K key) {
			float a;
			return (int)_capacity * modf(key * 2654435761 / pow(2, 32), &a);
		}
	};
}