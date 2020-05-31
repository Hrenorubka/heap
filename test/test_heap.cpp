#include "Heap.h"
#include <gtest.h>


TEST(_Heap, can_create_heap)
{
	ASSERT_NO_THROW(Binary_Heap<int> h);
}

TEST(_Heap, can_create_heap_with_custom_size)
{
	ASSERT_NO_THROW(Binary_Heap<int> h(10));
}
TEST(_Heap, can_create_cop_heap)
{
	Binary_Heap<int> h1(12);
	ASSERT_NO_THROW(Binary_Heap<int> h2(h1));
}
TEST(_Heap, can_insert_elem_to_heap)
{
	Binary_Heap<int> h;
	PriorVal<int> t = { 12, 15 };
	ASSERT_NO_THROW(h.insert(t));
}
TEST(_Heap, can_insert_additional_elem_to_heap)
{
	Binary_Heap<int> h;
	h.insert({ 12, 15 });
	h.insert({ 3, 136 });
	h.insert({ 4, -76 });
	h.insert({ 10, -46 });
	h.insert({ 1, 7 });
	ASSERT_NO_THROW(h.print());
}
TEST(_Heap, can_delete_elem_from_heap)
{
	Binary_Heap<int> h;
	h.insert({ 12, 15 });
	h.insert({ 3, 136 });
	h.insert({ 4, -76 });
	h.insert({ 10, -46 });
	h.insert({ 1, 7 });
	h.delelete(0);
	ASSERT_NO_THROW(h.print());
}