#include "gtest/gtest.h"
#include "hash_table/hash_table.h"

using namespace hash_table;
using std::cout, std::endl;

TEST(Print, First) {
	HashTable<int, float> table(10);
	table.insert(1, 0.1);
	table.insert(2, 0.2);
	table.insert(3, 0.3);
	table.print();
	cout << table.search(4) << ": " << endl;
}