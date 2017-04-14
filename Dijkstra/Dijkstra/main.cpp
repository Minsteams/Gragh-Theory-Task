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
		printf_s("����������㣺");
		scanf_s("%d", &root);
	}

	remove("out_graph.txt");
	fopen_s(&out, "out_graph.txt", "w");
	char **m;//����
	mfprint(out, "�ڽӱ�\n");
	graph->Print(out);
	mfprint(out, "ԭʼ��ϵ����:\n");
	m = GraphToMatrix(*graph);
	PrintMatrix(m, n, out);
	fclose(out);
	

	remove("out_graphTree.txt");
	fopen_s(&outtree, "out_graphTree.txt", "w");
	mfprint(outtree, "������С·�����£�\n");
	dijkstra(*graph, root);
	char **temp = PathsToMatrix(paths, n);
	myTree tree(MatrixToTreeRoot(temp, n, root));
	tree.ListAll(outtree);
	ClearMatrix(&temp, n);
	fclose(outtree);

	
	remove("out_graphMatrix.txt");
	fopen_s(&outMatrix, "out_graphMatrix.txt", "w");
	mfprint(outMatrix, "\n���󴫵ݱհ����£�\n");
	MatrixToTransitiveClosure(m, n);
	PrintMatrix(m, n,outMatrix);
	ClearMatrix(&m, n);
	fclose(outMatrix);


	
	_getch();
}