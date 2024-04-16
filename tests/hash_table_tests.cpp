#include "gtest/gtest.h"
#include "hash_table/hash_table.h"

using namespace hash_table;
using std::cout, std::endl;

TEST(Print, First) {
	HashTable<int, float> table(3);
	table.insert(1, 0.1);
	table.insert(2, 0.2);
	table.print();
	HashTable<int, float> table2(3);
	table2.insert(3, 0.3);
	table2.insert(4, 0.4);
	table2.print();

	table2 = table;

	table.erase(1);

	table.print();
	table2.print();
}