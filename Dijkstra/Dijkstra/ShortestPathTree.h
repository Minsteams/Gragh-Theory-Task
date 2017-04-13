#pragma once
class myNode {
public:
	int element;
	myNode *next;
	myNode *firstSon;
	myNode(int e) :element(e),next(NULL),firstSon(NULL){};
};
class myTree {
protected:
	myNode *root;
public:
	myTree(myNode*r);
	~myTree();
	void ListAll();
private:
	void List(myNode&node, int order);
	void ClearBranch(myNode * branch);
};

bool** PathsToMatrix(int *path, int n);
myNode* MatrixToTreeRoot(bool**matrix, int &n, int root);
void BuildBranch(myNode &node, bool**matrix, int &n);