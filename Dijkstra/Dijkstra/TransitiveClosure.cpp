#include<iostream>
#include"dijkstra.h"
#include"my_matrix.h"
using namespace std;


bool** GraphToMatrix(Graph<DijVertex> g) {
	int n = g.size();
	bool** m = new bool*[n];
	for (int i = 0; i <n; i++)
		m[i] = new bool[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			m[i][j] = false;
	for (int i = 0; i < n; i++) {
		Edge *tempEdge = g[i].edge;
		while (tempEdge != NULL) {
			m[i][tempEdge->toV] = true;
			tempEdge = tempEdge->next;
		}
	}
	return m;
}
void ClearMatrix(bool** m, int n) {
	for (int i=0; i < n; i++) {
		delete[]m[i];
	}
	delete m;
}
void PrintMatrix(bool** m, int n) {
	for (int i = 0; i < n; i++) {
		printf_s("\n");
		for (int j = 0; j < n; j++) {
			printf_s("%-5d", m[i][j]);
		}

	}
	printf_s("\n");
}
void MatrixToTransitiveClosure(bool **a, int n) {
	int i, j, k;
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (a[i][k])
					a[i][j] = a[i][j] || a[k][j];
			}
		}
	}
}