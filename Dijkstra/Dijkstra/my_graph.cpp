#include<iostream>
#include"my_graph.h"

void Vertex::LinkTo(int i, int w = 1) {
	Edge **tempEdge = &edge;
	while (*tempEdge != NULL)
	{
		tempEdge = &((*tempEdge)->next);
	}
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
