#pragma once
#include<vector>
using namespace std;
template<typename Comparable>
class Heap {
protected:
	vector<Comparable> heap;
	int currentSize;
public:
	Heap();
	char isEmpty()const;
	void push(const Comparable &i);
	void popTo(Comparable & item);
	void PercolateUp(int hole);
	void PercolateDown(int hole);
	virtual void Swap(Comparable &a, Comparable &b);
	~Heap() {}
};

//模板类实现放入同一文件

template<typename Comparable>
Heap<Comparable>::Heap() :currentSize(0) {
	heap.resize(1);
}
template<typename Comparable>
char Heap<Comparable>::isEmpty()const {
	return currentSize == 0;
}
template<typename Comparable>
void Heap<Comparable>::push(const Comparable &i) {
	if (currentSize == heap.size() - 1)heap.resize(heap.size() * 2);
	int hole = ++currentSize;
	heap[hole] = i;
	PercolateUp(hole);
}
template<typename Comparable>
void Heap<Comparable>::popTo(Comparable & item) {
	if (isEmpty()) {
		//do nothing
	}
	else {
		item = heap[1];
		if (currentSize != 1)
			heap[1] = heap[currentSize--];
		else currentSize--;
		PercolateDown(1);
	}
}
template<typename Comparable>
void Heap<Comparable>::PercolateUp(int hole) {
	for (; hole > 1 && heap[hole] < heap[hole / 2]; hole /= 2)
		Swap(heap[hole], heap[hole / 2]);
}
template<typename Comparable>
void Heap<Comparable>::PercolateDown(int hole) {
	int child = hole * 2;
	int tmp = heap[hole].index;
	for (; child <= currentSize; hole = child) {
		child = hole * 2;
		if (child != currentSize&&heap[child + 1] < heap[child])
			child++;
		if (heap[child] < tmp)
			Swap(heap[hole], heap[child]);
		else break;
	}
}
template<typename Comparable>
void Heap<Comparable>::Swap(Comparable &a, Comparable &b) {
	Comparable c;
	c = a;
	a = b;
	b = c;
}
