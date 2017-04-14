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
	void ListAll(FILE*out = NULL);
private:
	void List(myNode&node, int order,FILE*out=NULL);
	void ClearBranch(myNode * branch);
};

char** PathsToMatrix(int *path, int n);
myNode* MatrixToTreeRoot(char**matrix, int &n, int root);
void BuildBranch(myNode &node, char**matrix, int &n);