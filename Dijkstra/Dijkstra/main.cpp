#include<iostream>
#include<conio.h>
#include"dijkstra.h"
#include"my_matrix.h"
#include"ShortestPathTree.h"

void main() {
	Graph<DijVertex> graph(5);
	graph.Link(0, 1);
	graph.Link(1, 3);
	dijkstra(graph, 0);
	bool **m = GraphToMatrix(graph);
	int n = graph.size();
	PrintMatrix(m,n);
	MatrixToTransitiveClosure(m, n);
	PrintMatrix(m,n);
	bool **temp = PathsToMatrix(paths, n);
	myTree tree(MatrixToTreeRoot(temp, n, 0));
	tree.ListAll();
	_getch();
}