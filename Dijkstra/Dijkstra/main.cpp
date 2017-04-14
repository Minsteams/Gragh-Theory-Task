#include<iostream>
#include<conio.h>

#include"ShortestPathTree.h"
#include"dijkstra.h"
#include"my_matrix.h"
#include"myFilePrint.h"


void main() {
	int n=-1;
	Graph<DijVertex> *graph = NULL;
	FILE *in;
	fopen_s(&in, "in_graph.txt", "r");
	if (in != NULL) {
		fscanf_s(in, "%d", &n);
		graph = new Graph<DijVertex>(n);
		int en = 0;
		int index = 0;
		while (!feof(in)) {
			fscanf_s(in, "%d", &index);
			fscanf_s(in, "%d", &en);
			int to;
			int weight;
			for (int i = 0; i < en; i++) {
				fscanf_s(in, "%d", &to);
				fscanf_s(in, "%d", &weight);
				graph->Link(index, to, weight);
			}
		}
		fclose(in);
	}
	if (graph == NULL)exit(1);
	FILE *out;
	FILE *outtree;
	FILE *outMatrix;



	//Main
	int root = -1;
	while (!(root >= 0 && root < n)) {
		printf_s("请输入出发点：");
		scanf_s("%d", &root);
	}

	remove("out_graph.txt");
	fopen_s(&out, "out_graph.txt", "w");
	char **m;//矩阵
	mfprint(out, "邻接表：\n");
	graph->Print(out);
	mfprint(out, "原始关系矩阵:\n");
	m = GraphToMatrix(*graph);
	PrintMatrix(m, n, out);
	fclose(out);
	

	remove("out_graphTree.txt");
	fopen_s(&outtree, "out_graphTree.txt", "w");
	mfprint(outtree, "生成最小路树如下：\n");
	dijkstra(*graph, root);
	char **temp = PathsToMatrix(paths, n);
	myTree tree(MatrixToTreeRoot(temp, n, root));
	tree.ListAll(outtree);
	ClearMatrix(&temp, n);
	fclose(outtree);

	
	remove("out_graphMatrix.txt");
	fopen_s(&outMatrix, "out_graphMatrix.txt", "w");
	mfprint(outMatrix, "\n矩阵传递闭包如下：\n");
	MatrixToTransitiveClosure(m, n);
	PrintMatrix(m, n,outMatrix);
	ClearMatrix(&m, n);
	fclose(outMatrix);


	
	_getch();
}