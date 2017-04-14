#include<iostream>
#include"my_graph.h"

void Vertex::LinkTo(int i, int w) {
	Edge **tempEdge = &edge;
	bool existed = false;
	while (*tempEdge != NULL)
	{
		if (i == (*tempEdge)->toV) {
			(*tempEdge)->weight = w;
			existed = true;
			break;
		}
		tempEdge = &((*tempEdge)->next);
	}
	if(!existed)
		*tempEdge = new Edge(i, w);
}
void Vertex::operator=(const Vertex & rhs) {
	index = rhs.index;
	edge = rhs.edge;
}
void Vertex::Clear() {
	Edge *p1, *p2 = edge;
	p1 = p2;
	while (p1 != NULL)
	{
		p2 = p2->next;
		delete p1;
		p1 = p2;
	}
}
