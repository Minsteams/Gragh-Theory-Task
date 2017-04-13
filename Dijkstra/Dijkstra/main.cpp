#include<iostream>
#include<conio.h>
#include"dijkstra.h"
#include"my_matrix.h"

void main() {
	Graph<DijVertex> graph(5);
	graph.Link(0, 1);
	graph.Link(1, 2);
	dijkstra(graph, 0);
	bool **m = GraphToMatrix(graph);
	int n = graph.size();
	PrintMatrix(m,n);
	MatrixToTransitiveClosure(m, n);
	PrintMatrix(m,n);

	_getch();
}