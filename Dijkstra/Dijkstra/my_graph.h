#pragma once
#include<vector>
#include"myFilePrint.h"
//类模板实现于头文件
using namespace std;
struct Edge {
	int toV;
	int weight;
	Edge *next;
	Edge(int to, Edge* n = NULL) :toV(to), weight(1), next(n) {};
	Edge(int to, int w, Edge* n = NULL) :toV(to), weight(w), next(n) {};
};
class Vertex {
public:
	int index;
	Edge *edge;
	Vertex(int i = 0) :index(i), edge(NULL) {};
	void LinkTo(int i, int w);
	void operator=(const Vertex & rhs);
	void Clear();
};
template<typename v>
class Graph {
public:
	Graph(int i);
	void Print(FILE*out=NULL);
	size_t size()const;
	void Link(int from, int to, int w = 1);
	const v & operator[](int i) const;
	v & operator[](int i);
	~Graph();
private:
	vector<v> vertexes;
};

//模板类实现放入同一文件
template<typename v>
Graph<v>::Graph(int i) {
	if (i == -1)i = 0;
	vertexes.resize(i);
	for (int j = 0; j < i; j++) {
		vertexes[j].index = j;
		vertexes[j].edge = NULL;
	}
}
template<typename v>
void Graph<v>::Print(FILE*out) {
	if (size() == 0)mfprint(out,"Empty!\n");
	else for (int i = 0; i < vertexes.size(); i++) {
		mfprint(out, "%d\t", vertexes[i].index);
		Edge *tempEdge = vertexes[i].edge;
		while (tempEdge != NULL)
		{
			mfprint(out, "to %d(%d) ,", tempEdge->toV, tempEdge->weight);
			tempEdge = tempEdge->next;
		}
		mfprint(out, "\n");
	}
}
template<typename v>
size_t Graph<v>::size()const {
	return vertexes.size();
}
template<typename v>
void Graph<v>::Link(int from, int to, int w = 1) {
	if (from < vertexes.size() && to < vertexes.size()) {
		vertexes[from].LinkTo(to, w);
	}
}
template<typename v>
const v & Graph<v>::operator[](int i) const {
	return vertexes[i];
}
template<typename v>
v &Graph<v>::operator[](int i) {
	return vertexes[i];
}
template<typename v>
Graph<v>::~Graph() {
	for (int i = 0; i < vertexes.size(); i++) {
		vertexes[i].Clear();
	}
}