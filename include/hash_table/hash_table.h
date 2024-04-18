#pragma once
#include<iostream>
#include<string>
#include<random>

namespace hash_table {
	const char T[256] = {
			 98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,
			 61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,
			 90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,
			237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121,
			123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55,
			 59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,
			197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,
			 39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,
			154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,
			133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139,
			189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,
			183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12,
			221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166,
			  3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,
			238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110,
			 43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239
	};

	const std::string CHARS = "abcdefghijklmnopqrstuvwxyz";

	int pearson_hash(std::string s) {
		char hash = 0;
		for (const char& c : s) {
			hash = T[hash ^ c];
		}
		return (int)hash;
	}

	bool compare_string(int hash, std::string s) {
		return hash == pearson_hash(s);
	}

	template<class K, class V>
	class HashTable {
	public:
		struct Pair {
			bool _del;
			K _key;
			V _value;
			Pair(K key, V value) : _key(key), _value(value), _del(false) {}
			Pair():_key(K()), _value(V()), _del(false) {}
		};
		HashTable(size_t capacity) : _capacity(capacity), _data(new Pair[capacity]) {
			for (size_t i = 0; i < capacity; i++)
			{
				_data[i] = Pair();
			}
		}
		HashTable(size_t capacity, size_t size_of_string) : _capacity(capacity), _data(new Pair[capacity]) {
			for (size_t i = 0; i < capacity; i++)
			{
				_data[i] = Pair();
			}
			std::random_device rd;
			std::mt19937 generator(rd());
			std::uniform_int_distribution<int> distribution(0, CHARS.size() - 1);
			for (size_t i = 0; i < _capacity; i++)
			{
				std::string s = "";
				for (size_t j = 0; j < size_of_string; j++)
				{
					s += CHARS[distribution(generator)];
				}
				insert(distribution(generator), s);
			}
		}
		HashTable(const HashTable& rhs) {
			_capacity = rhs.get_capacity();
			_data = new Pair[_capacity];
			for (size_t i = 0; i < _capacity; i++)
			{
				_data[i] = rhs[i];
			}
		}
		HashTable& operator=(const HashTable& rhs) {
			HashTable copy(rhs);
			swap(copy);
			return *this;
		}
		void insert(K key, V value) {
			int index = hash(key);
			int i = 0;
			bool full_cycle = false;
			while (!full_cycle) {
				if (_data[(index + i) % _capacity]._key == K() || _data[(index + i) % _capacity]._del == true) {
					_data[(index + i) % _capacity] = Pair(key, value);
					return;
				}
				++i;
				if ((index + i) % _capacity == index) full_cycle = true;
			}
		}
		void insert_or_assign(K key, V value) {
			int index = hash(key);
			if (_data[index]._key == K()) {
				_data[index] = Pair(key, value);
			}
			else {
				_data[index]._value = value;
				_data[index]._del = false;
			}
		}
		void print() const {
			for (size_t i = 0; i < _capacity; i++)
			{
				std::cout << "Key: " << _data[i]._key << ", Value: " << _data[i]._value << ", Del: " << _data[i]._del << std::endl;
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
			while (_data[(index + i) % _capacity]._key != K() && !full_cycle) {
				Pair current = _data[(index + i) % _capacity];
				if (current._key == key && current._del == false) {
					return &current._value;
				}
				++i;
				if ((index + i) % _capacity == index) full_cycle = true;
			}
			return nullptr;
		}
		bool erase(K key) {
			int index = hash(key);
			int i = 0;
			while (true) {
				Pair current = _data[(index + i) % _capacity];
				if (current._key == key && current._del == false) break;
				++i;
				if ((index + i) % _capacity == index) return false;
			}
			_data[(index + i) % _capacity]._del = true;
			return true;
		}
		int get_capacity() const {
			return _capacity;
		}
		int count(K key) {
			int index = hash(key);
			int i = 0;
			int counter = 0;
			bool full_cycle = false;
			while (_data[(index + i) % _capacity]._key != K() && !full_cycle) {
				Pair current = _data[(index + i) % _capacity];
				if (current._key == key && current._del == false) {
					++counter;
				}
				++i;
				if ((index + i) % _capacity == index) full_cycle = true;
			}
			return counter;
		}
		/*void random_fill(size_t size){
			std::random_device rd;
			std::mt19937 generator(rd());
			std::uniform_int_distribution<int> distribution(0, CHARS.size() - 1);
			for (size_t i = 0; i < _capacity; i++)
			{
				std::string result = "";
				for (size_t j = 0; j < size; j++)
				{
					result += CHARS[distribution(generator)];
				}
				int index = pearson_hash(result);
				int k = 0;
				while (true) {
					if (_data[(index + k) % _capacity]._key == K() || _data[(index + k) % _capacity]._del == true) {
						_data[(index + k) % _capacity] = Pair(index, result);
						break;
					}
					++k;
				}
			}
		}*/
		~HashTable(){
			delete[] _data;
		}
	private:
		int _capacity;
		Pair* _data;
		int hash(K key) {
			float a;
			return (int)_capacity * modf(key * 2654435761 / pow(2, 32), &a);
		}
		Pair& operator[](int index){
			return _data[index];
		}
		const Pair& operator[](int index) const{
			return _data[index];
		}
		int& get_capacity() {
			return _capacity;
		}
		Pair*& get_data() {
			return _data;
		}
		void swap(HashTable& rhs){
			std::swap(_capacity, rhs.get_capacity());
			std::swap(_data, rhs.get_data());
		}
	};
}