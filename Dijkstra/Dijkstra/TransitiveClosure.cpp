#include<iostream>
#include"dijkstra.h"
#include"my_matrix.h"
#include"myFilePrint.h"
using namespace std;


char** GraphToMatrix(Graph<DijVertex> &g) {
	int n = g.size();
	char** m = new char *[n];
	for (int i = 0; i <n; i++)
		m[i] = new char[n];
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
void ClearMatrix(char*** m, int n) {
	for (int i = 0; i < n; i++) {
		delete []((*m)[i]);
	}
	delete [] (*m);
	*m=NULL;
}
void PrintMatrix(char** m, int n,FILE*out) {
	for (int i = 0; i < n; i++) {
		mfprint(out,"\n");
		for (int j = 0; j < n; j++) {
			mfprint(out,"%-5d", m[i][j]);
		}

	}
	mfprint(out,"\n");
}
void MatrixToTransitiveClosure(char **a, int n) {
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
