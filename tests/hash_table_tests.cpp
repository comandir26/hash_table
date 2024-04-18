#include "gtest/gtest.h"
#include "hash_table/hash_table.h"

using namespace hash_table;
using std::cout, std::endl, std::string;



TEST(Create, First) {
	HashTable<int, float> table(10);
	table.print();
}

TEST(Insert, First) {
	HashTable<int, float> table(10);
	table.insert(1, 0.1);
	table.insert(11, 0.21);
	table.insert(2, 0.2);
	table.insert(32, 0.32);
	table.insert(5, 0.5);
	table.insert(7, 0.7);
	table.insert(4, 0.4);
	table.insert(13, 0.133);
	table.insert(17, 0.71);
	table.print();
}

TEST(InsertAssign, First) {
	HashTable<int, float> table(10);
	table.insert(1, 0.1);
	table.insert_or_assign(11, 0.21);
	table.insert_or_assign(2, 0.2);
	table.print();
	table.insert_or_assign(2, 0.777);
	table.print();
}

TEST(Contains, First) {
	HashTable<int, float> table(10);
	table.insert(1, 0.1);
	table.insert(11, 0.21);
	table.insert(2, 0.2);
	table.insert(32, 0.32);
	table.insert(5, 0.5);
	table.insert(7, 0.7);
	table.insert(4, 0.4);
	table.insert(13, 0.133);
	table.insert(17, 0.71);
	cout << table.contains(0.133) << endl;
	cout << table.contains(12.5) << endl;
}

TEST(Search, First) {
	HashTable<int, float> table(10);
	table.insert(1, 0.1);
	table.insert(11, 0.21);
	table.insert(2, 0.2);
	table.insert(32, 0.32);
	table.insert(5, 0.5);
	table.insert(7, 0.7);
	table.insert(4, 0.4);
	table.insert(13, 0.133);
	table.insert(17, 0.71);
	auto value1 = table.search(11);
	if (value1) {
		cout << *value1 << endl;
	}
	else {
		cout << "No value with that key" << endl;
	}
	auto value2 = table.search(1000);
	if (value2) {
		cout << *value2 << endl;
	}
	else {
		cout << "No value with that key" << endl;
	}
}

TEST(Search, Second) {
	HashTable<int, float> table(10);
	table.insert(1, 0.1);
	table.insert(11, 0.21);
	table.insert(2, 0.2);
	table.insert(32, 0.32);
	table.insert(3, 0.5);
	table.insert(7, 0.13);
	table.insert(7, 0.17);
	table.insert(13, 0.133);
	table.insert(17, 0.71);
	table.print();
	auto value1 = table.search(7);
	if (value1) {
		cout << *value1 << endl;
	}
	else {
		cout << "No value with that key" << endl;
	}
	table.erase(7);
	auto value2 = table.search(7);
	if (value2) {
		cout << *value2 << endl;
	}
	else {
		cout << "No value with that key" << endl;
	}
}

TEST(Erase, First) {
	HashTable<int, float> table(7);
	table.insert(1, 0.1);
	table.insert(11, 0.21);
	table.insert(2, 0.2);
	table.insert(32, 0.32);
	table.print();
	table.erase(32);
	table.erase(121);
	table.print();
}

TEST(Count, First) {
	HashTable<int, float> table(10);
	table.insert(1, 0.1);
	table.insert(11, 0.21);
	table.insert(11, 0.2);
	table.insert(32, 0.32);
	table.insert(11, 0.5);
	table.insert(7, 0.7);
	table.insert(7, 0.4);
	table.insert(13, 0.133);
	table.insert(17, 0.71);
	table.erase(7);
	cout << table.count(11) << endl;
	cout << table.count(7) << endl;
	cout << table.count(1) << endl;
}

TEST(Pearson, First) {
	string s = "Dortmund";
	cout << pearson_hash(s) << endl;
}

TEST(Pearson, Second) {
	string s = "Dortmund";
	auto hash = pearson_hash(s);
	cout << compare_string(hash, "Paris") << endl;
}

TEST(Fill, First) {
	HashTable<int, string> table(10, 5);
	table.print();
}