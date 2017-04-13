#include<iostream>
#include"ShortestPathTree.h"

myTree::myTree(myNode*r) :root(r) {}
myTree::~myTree() {
	ClearBranch(root);
}
void myTree::ListAll() {
	List(*root, 0);
}
void myTree::List(myNode&node, int order) {
	printf_s("\n");
	for (int i = 0; i < order; i++)
		printf_s("\t");
	printf_s("--%d", node.element);
	if (node.firstSon != NULL)List(*node.firstSon, order+1);
	if (node.next != NULL)List(*node.next, order);
}
void myTree::ClearBranch(myNode * branch) {
	if (branch != NULL) {
		ClearBranch(branch->firstSon);
		ClearBranch(branch->next);
		delete branch;
	}
}
bool** PathsToMatrix(int *path, int n) {
	bool** m = new bool*[n];
	for (int i = 0; i <n; i++)
		m[i] = new bool[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			m[i][j] = false;
	for (int i = 0; i < n; i++) {
		if (path[i] != -1)
			m[path[i]][i] = true;
	}
	return m;
}
myNode* MatrixToTreeRoot(bool**matrix, int &n, int root) {
	myNode* r = new myNode(root);
	BuildBranch(*r, matrix, n);
	return r;
}
void BuildBranch(myNode &node, bool**matrix, int &n) {
	int e = node.element;
	myNode * current = NULL;
	for (int i = 0; i < n; i++) {
		if (matrix[e][i]&&e!=i) {
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