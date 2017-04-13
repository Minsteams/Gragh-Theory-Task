#pragma once

#include"my_heap.h"
#include"my_graph.h"
extern int* positions;//index to position in heap. return -1 when not in heap.
extern int* distances;//distances
extern int* paths;	//to record paths from original vertex.
class DijVertex :public Vertex {
public:
	bool operator<(const Vertex & rhs)const;
	bool operator<(const int rhs)const;
};
class DijHeap :public Heap<DijVertex> {
public:
	virtual void Swap(DijVertex &a, DijVertex &b);
	void popTo(DijVertex & item);
};
void ClearData();

void DijOutput(int size);
void dijkstra(Graph<DijVertex> &graph, int index);