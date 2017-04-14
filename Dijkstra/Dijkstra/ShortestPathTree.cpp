#include<iostream>
#include"ShortestPathTree.h"
#include"myFilePrint.h"

myTree::myTree(myNode*r) :root(r) {}
myTree::~myTree() {
	ClearBranch(root);
}
void myTree::ListAll (FILE*out) {
	List(*root, 0 ,out);
}
void myTree::List(myNode&node, int order, FILE*out) {
	mfprint(out,"\n");
	for (int i = 0; i < order; i++)
		mfprint(out,"\t");
	mfprint(out,"--%d", node.element);
	if (node.firstSon != NULL)List(*node.firstSon, order + 1, out);
	if (node.next != NULL)List(*node.next, order, out);
}
void myTree::ClearBranch(myNode * branch) {
	if (branch != NULL) {
		ClearBranch(branch->firstSon);
		ClearBranch(branch->next);
		delete branch;
	}
}
char** PathsToMatrix(int *path, int n) {
	char** m = new char*[n];
	for (int i = 0; i <n; i++)
		m[i] = new char[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			m[i][j] = false;
	for (int i = 0; i < n; i++) {
		if (path[i] != -1)
			m[path[i]][i] = true;
	}
	return m;
}
myNode* MatrixToTreeRoot(char**matrix, int &n, int root) {
	myNode* r = new myNode(root);
	BuildBranch(*r, matrix, n);
	return r;
}
void BuildBranch(myNode &node, char**matrix, int &n) {
	int e = node.element;
	myNode * current = NULL;
	for (int i = 0; i < n; i++) {
		if (matrix[e][i]!=0&&e!=i) {
			if (node.firstSon == NULL) {
				node.firstSon = new myNode(i);
				current = node.firstSon;
			}
			else {
				current->next = new myNode(i);
				current = current->next;
			}
			BuildBranch(*current, matrix, n);
		}
	}
}