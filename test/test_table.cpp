#include "gtest.h"
#include "table.h"

TEST(UnorderedTable, can_create_unordered_table_empty)
{
	ASSERT_NO_THROW(UnorderedTable<int> a);
	UnorderedTable<int> a;
	EXPECT_EQ(0, a.getSize());
	EXPECT_EQ(1, a.isEmpty());
}
TEST(UnorderedTable, can_create_unordered_table_vector)
{
	std::vector<std::pair<std::size_t, int>> a = { {9,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(UnorderedTable<int> b(a.size(), a));
	UnorderedTable<int> b(a.size(), a);
	EXPECT_EQ(0, b.isEmpty());
	EXPECT_EQ(3, b.getSize());
}
TEST(UnorderedTable, can_find_in_unordered_table)
{
	std::vector<std::pair<std::size_t, int>> a = { {9,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(UnorderedTable<int> b(a.size(), a));
	UnorderedTable<int> b(a.size(), a);
	EXPECT_EQ(std::make_pair((std::size_t)9, 24), b.find(9));
	EXPECT_EQ(std::make_pair((std::size_t)2, -67), b.find(2));
	EXPECT_EQ(std::make_pair((std::size_t)3, 623), b.find(3));
}
TEST(UnorderedTable, can_create_unordered_table_table)
{
	std::vector<std::pair<std::size_t, int>> a = { {9,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(UnorderedTable<int> b(a.size(), a));
	UnorderedTable<int> b(a.size(), a);
	EXPECT_EQ(0, b.isEmpty());
	EXPECT_EQ(3, b.getSize());
	ASSERT_NO_THROW(UnorderedTable<int> ho(b));
	UnorderedTable<int> ho(b);
	EXPECT_EQ(0, ho.isEmpty());
	EXPECT_EQ(3, ho.getSize());
	EXPECT_EQ(b.find(9), ho.find(9));
	EXPECT_EQ(b.find(2), ho.find(2));
	EXPECT_EQ(b.find(3), ho.find(3));
}
TEST(UnorderedTable, can_insert_in_unordered_table_key_doesnt_exist)
{
	std::vector<std::pair<std::size_t, int>> a = { {9,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(UnorderedTable<int> b(a.size(), a));
	UnorderedTable<int> b(a.size(), a);
	ASSERT_NO_THROW(b.insert(6, 1553432));
	b.insert(6, 1553432);
	ASSERT_NO_THROW(b.find(6));
	EXPECT_EQ(std::make_pair((std::size_t)6,1553432), b.find(6));
	EXPECT_EQ(std::make_pair((std::size_t)9, 24), b.find(9));
	EXPECT_EQ(std::make_pair((std::size_t)2, -67), b.find(2));
	EXPECT_EQ(std::make_pair((std::size_t)3, 623), b.find(3));
}
TEST(UnorderedTable, cant_insert_in_unordered_table_key_does_exist)
{
	std::vector<std::pair<std::size_t, int>> a = { {9,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(UnorderedTable<int> b(a.size(), a));
	UnorderedTable<int> b(a.size(), a);
	EXPECT_EQ(0,b.insert(2, 1553432));
}
TEST(UnorderedTable, can_erase_in_unordered_table_key_does_exist)
{
	std::vector<std::pair<std::size_t, int>> a = { {9,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(UnorderedTable<int> b(a.size(), a));
	UnorderedTable<int> b(a.size(), a);
	ASSERT_NO_THROW(b.erase(2));
	EXPECT_EQ(std::make_pair((std::size_t)9, 24), b.find(9));
	EXPECT_EQ(std::make_pair((std::size_t)3, 623), b.find(3));
	ASSERT_ANY_THROW(b.find(2));
	EXPECT_EQ(2, b.getSize());
}
TEST(UnorderedTable, cant_erase_in_unordered_table_key_doesnt_exist)
{
	std::vector<std::pair<std::size_t, int>> a = { {9,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(UnorderedTable<int> b(a.size(), a));
	UnorderedTable<int> b(a.size(), a);
	EXPECT_EQ(0,b.erase(14));
}

TEST(OrderedTable, can_create_ordered_table_empty)
{
	ASSERT_NO_THROW(OrderedTable<int> b);
}

TEST(OrderedTable, can_create_ordered_table_vector)
{
	std::vector<std::pair<std::size_t, int>> a = { {1,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(OrderedTable<int> b(a.size(), a));
}
TEST(OrderedTable, can_find_in_ordered_table)
{
	std::vector<std::pair<std::size_t, int>> a = { {1,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(OrderedTable<int> b(a.size(), a));
	OrderedTable<int> b(a.size(), a);
	EXPECT_EQ(0, b.isEmpty());
	EXPECT_EQ(3, b.getSize());
	EXPECT_EQ(std::make_pair((std::size_t)1, 24), b.find(1));
	EXPECT_EQ(std::make_pair((std::size_t)2, -67), b.find(2));
	EXPECT_EQ(std::make_pair((std::size_t)3, 623), b.find(3));
}
TEST(OrderedTable, can_create_ordered_table_table)
{
	std::vector<std::pair<std::size_t, int>> a = { {1,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(OrderedTable<int> b(a.size(), a));
	OrderedTable<int> b(a.size(), a);
	EXPECT_EQ(0, b.isEmpty());
	EXPECT_EQ(3, b.getSize());
	ASSERT_NO_THROW(OrderedTable<int> ho(b));
	OrderedTable<int> ho(b);
	EXPECT_EQ(0, ho.isEmpty());
	EXPECT_EQ(3, ho.getSize());
	EXPECT_EQ(b.find(1), ho.find(1));
	EXPECT_EQ(b.find(2), ho.find(2));
	EXPECT_EQ(b.find(3), ho.find(3));
}
TEST(OrderedTable, can_insert_in_ordered_table_key_doesnt_exist)
{
	std::vector<std::pair<std::size_t, int>> a = { {1,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(OrderedTable<int> b(a.size(), a));
	OrderedTable<int> b(a.size(), a);
	ASSERT_NO_THROW(b.insert(6, 1553432));
	b.insert(6, 1553432);
	ASSERT_NO_THROW(b.find(6));
	EXPECT_EQ(std::make_pair((std::size_t)6, 1553432), b.find(6));
	EXPECT_EQ(std::make_pair((std::size_t)1, 24), b.find(1));
	EXPECT_EQ(std::make_pair((std::size_t)2, -67), b.find(2));
	EXPECT_EQ(std::make_pair((std::size_t)3, 623), b.find(3));
}
TEST(OrderedTable, cant_insert_in_ordered_table_key_does_exist)
{
	std::vector<std::pair<std::size_t, int>> a = { {1,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(OrderedTable<int> b(a.size(), a));
	UnorderedTable<int> b(a.size(), a);
	EXPECT_EQ(0, b.insert(2, 1553432));
}
TEST(OrderedTable, can_erase_in_ordered_table_key_does_exist)
{
	std::vector<std::pair<std::size_t, int>> a = { {1,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(OrderedTable<int> b(a.size(), a));
	OrderedTable<int> b(a.size(), a);
	ASSERT_NO_THROW(b.erase(2));
	EXPECT_EQ(std::make_pair((std::size_t)1, 24), b.find(1));
	EXPECT_EQ(std::make_pair((std::size_t)3, 623), b.find(3));
	ASSERT_ANY_THROW(b.find(2));
	EXPECT_EQ(2, b.getSize());
}
TEST(OrderedTable, cant_erase_in_ordered_table_key_doesnt_exist)
{
	std::vector<std::pair<std::size_t, int>> a = { {1,24}, {2,-67}, {3,623} };
	ASSERT_NO_THROW(OrderedTable<int> b(a.size(), a));
	OrderedTable<int> b(a.size(), a);
	EXPECT_EQ(0, b.erase(14));
}

TEST(HashTableOpenMix, can_create_hash_table_open_mix)
{
	ASSERT_NO_THROW(HashTableOpenMix<int> q);
}
TEST(HashTableOpenMix, can_find_in_hash_table_open_mix)
{
	ASSERT_NO_THROW(HashTableOpenMix<int> q);
	HashTableOpenMix<int> q;
	ASSERT_NO_THROW(q.insert(1, 25));
	q.insert(1, 25);
	EXPECT_EQ(1, q.find(1).first);
	EXPECT_EQ(25, q.find(1).second.first);
	EXPECT_EQ(0, q.find(1).second.second);
}
TEST(HashTableOpenMix, cant_find_in_hash_table_open_mix_element_doesnt_exist)
{
	ASSERT_NO_THROW(HashTableOpenMix<int> q);
	HashTableOpenMix<int> q;
	ASSERT_ANY_THROW(q.find(1));
}
TEST(HashTableOpenMix, can_insert_in_hash_table_open_mix)
{
	ASSERT_NO_THROW(HashTableOpenMix<int> q);
	HashTableOpenMix<int> q;
	ASSERT_NO_THROW(q.insert(1, 25));
	q.insert(1, 25);
	EXPECT_EQ(1, q.find(1).first);
	EXPECT_EQ(25, q.find(1).second.first);
	EXPECT_EQ(0, q.find(1).second.second);
}
TEST(HashTableOpenMix, cant_insert_in_hash_table_open_mix_same_key)
{
	ASSERT_NO_THROW(HashTableOpenMix<int> q);
	HashTableOpenMix<int> q;
	ASSERT_NO_THROW(q.insert(1, 25));
	EXPECT_EQ(0, q.insert(1,25));
}
TEST(HashTableOpenMix, can_avoid_collisions_in_hash_table_open_mix)
{
	ASSERT_NO_THROW(HashTableOpenMix<int> q);
	HashTableOpenMix<int> q;
	for (int i = 0; i < 14867 + 1024; i++) EXPECT_EQ(1, q.insert(i, i + 1));
}
TEST(HashTableOpenMix, cant_insert_in_full_table_in_hash_table_open_mix)
{
	ASSERT_NO_THROW(HashTableOpenMix<int> q);
	HashTableOpenMix<int> q;
	for (int i = 0; i < 14867 + 1024; i++) EXPECT_EQ(1, q.insert(i, i + 1));
	EXPECT_EQ(0, q.insert(20000, 1));
}
TEST(HashTableOpenMix, can_erase_in_hash_table_open_mix)
{
	ASSERT_NO_THROW(HashTableOpenMix<int> q);
	HashTableOpenMix<int> q;
	ASSERT_NO_THROW(q.insert(1, 25));
	EXPECT_EQ(1, q.erase(1));
}
TEST(HashTableOpenMix, can_insert_in_deleted_cell_in_hash_table_open_mix)
{
	ASSERT_NO_THROW(HashTableOpenMix<int> q);
	HashTableOpenMix<int> q;
	for (int i = 0; i < 14867 + 1024; i++) EXPECT_EQ(1,q.insert(i, i + 1));
	EXPECT_EQ(1,q.erase(14867));
	EXPECT_EQ(1, q.insert(20000, 1));
}