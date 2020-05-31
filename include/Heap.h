#pragma once
#ifndef __HEAP_H__
#define __HEAP_H__

#include <iostream>

template <class ValType>
struct PriorVal
{
	int prior;
	ValType val;
	PriorVal()
	{
		prior = INFINITY;
	}
	PriorVal(int inp_pr, ValType inp_val)
	{
		prior = inp_pr;
		val = inp_val;
	}
	~PriorVal() {}
	bool operator>(PriorVal &r)
	{
		return (prior > r.prior);
	}
	bool operator<(PriorVal &r)
	{
		return (prior < r.prior);
	}
	bool operator==(PriorVal &r)
	{
		return (prior == r.prior);
	}
	bool operator!=(PriorVal &r)
	{
		return (prior != r.prior);
	}
};

template <class ValType>
class Binary_Heap
{
private:
	int max_size;
	int cur_size;
	PriorVal<ValType> *b_heap;
	void repacking()
	{
		int prev_size = max_size;
		max_size = max_size + max_size * 0.5 + 5;
		PriorVal<ValType> *obl_b_heap = new PriorVal<ValType>[max_size];
		for (int i = 0; i < prev_size; i++)
		{
			obl_b_heap[i] = b_heap[i];
		}
		delete[] b_heap;
		b_heap = obl_b_heap;
	}
	int get_ind_parent(int i)
	{
		return (i - 1) / 2;
	}
	int get_ind_left_child(int i)
	{
		if (i * 2 + 1 < cur_size)
			return i * 2 + 1;
		return -1;
	}
	int get_ind_right_child(int i)
	{
		if (i * 2 + 2 < cur_size)
			return i * 2 + 2;
		return -1;
	}
	int get_ind_min_child(int i)
	{
		int l = get_ind_left_child(i);
		int r = get_ind_right_child(i);
		if (l == -1)
		{
			if (r == -1)
				return -1;
			return r;
		}
		if (r == -1)
			return l;
		if (b_heap[l] > b_heap[r])
		{
			return r;
		}
		else
		{
			return l;
		}
	}
	void emersion(int i)
	{
		if (i == 0)
			return;
		int ind_parent = get_ind_parent(i);
		if (b_heap[i] < b_heap[ind_parent])
		{
			PriorVal<ValType> obl = b_heap[i];
			b_heap[i] = b_heap[ind_parent];
			b_heap[ind_parent] = obl;
			emersion(ind_parent);
		}
	}
	void diving(int i)
	{
		int min = get_ind_min_child(i);
		if (min == -1)
			return;
		if (b_heap[i] > b_heap[min])
		{
			PriorVal<ValType> obl = b_heap[i];
			b_heap[i] = b_heap[min];
			b_heap[min] = obl;
		}
		diving(min);
	}

public:
	Binary_Heap()
	{
		max_size = 10;
		cur_size = 0;
		b_heap = new PriorVal<ValType>[max_size];
	}
	Binary_Heap(int inp_size)
	{
		max_size = inp_size;
		cur_size = 0;
		b_heap = new PriorVal<ValType>[max_size];
	}
	Binary_Heap(const Binary_Heap<ValType> &cop)
	{
		max_size = cop.max_size;
		cur_size = cop.cur_size;
		b_heap = new PriorVal<ValType>[max_size];
		for (int i = 0; i < cur_size; i++)
		{
			b_heap[i] = cop.b_heap[i];
		}
	}
	~Binary_Heap()
	{
		delete[] b_heap;
	}
	void insert(PriorVal<ValType> inp)
	{
		b_heap[cur_size] = inp;
		emersion(cur_size);
		cur_size++;
		if (cur_size == max_size)
			repacking();
	}
	void decrease_weight(int ind, int weight)
	{
		b_heap[ind].prior = b_heap[ind].prior - weight;
		emersion(ind);
	}
	void delete_min()
	{
		cur_size--;
		if (cur_size > 0)
		{
			PriorVal<ValType> obl = b_heap[0];
			b_heap[0] = b_heap[cur_size];
			b_heap[cur_size] = obl;
			diving(0);
		}
		if (cur_size < 0)
			throw 1;
	}
	void delelete(int i)
	{
		decrease_weight(i, INFINITY);
		delete_min();
	}
	void makeheap(PriorVal<ValType> *inp_mas, int inp_size)
	{
		delete[] b_heap;
		max_size = inp_size + inp_size * 0.5;
		b_heap = new PriorVal<ValType>[max_size];
		cur_size = inp_size;
		b_heap[0] = inp_mas[0];
		for (int i = 1; i < inp_size; i++)
		{
			b_heap[i] = inp_mas[i];
			emersion(i);
		}
	}
	void get_head()
	{
		if (cur_size != 0)
			return b_heap[0].val;
		else
			throw 1;
	}
	void print()
	{
		for (int i = 0; i < cur_size; i++)
		{
			std::cout << b_heap[i].val << ' ';
		}
	}
};
#endif
