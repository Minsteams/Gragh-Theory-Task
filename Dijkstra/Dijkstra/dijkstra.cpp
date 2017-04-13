#include<iostream>
#include<vector>
#include<conio.h>
using namespace std;

//图声明
struct Edge {
	int toV;
	int weight;
	Edge *next;
	Edge(int to,Edge* n=NULL):toV(to), weight(1), next(n) {};
	Edge(int to,int w, Edge* n=NULL) :toV(to), weight(1), next(n) {};
};
class Vertex {
public:
	int index;
	Edge *edge;
	Vertex(int i = 0) :index(i), edge(NULL) {};
	void LinkTo(int i, int w = 1) {
		Edge **tempEdge = &edge;
		while (*tempEdge != NULL)
		{
			tempEdge = &((*tempEdge)->next);
		}
		*tempEdge = new Edge(i, w);
	}
	void operator=(const Vertex & rhs) {
		index = rhs.index;
		edge = rhs.edge;
	}
	void Clear() {
		Edge *p1,*p2 = edge;
		p1 = p2;
		while (p1 != NULL)
		{
			p2 = p2->next;
			delete p1;
			p1 = p2;
		}
	}
};
template<typename v>
class Graph {
public:
	Graph(int i) {
		vertexes.resize(i);
		for (int j = 0; j < i; j++) {
			vertexes[j].index = j;
			vertexes[j].edge = NULL;
		}
	}
	void Print() {
		for (int i = 0; i < vertexes.size(); i++) {
			printf_s("%d\t", vertexes[i].index);
			Edge *tempEdge = vertexes[i].edge;
			while (tempEdge != NULL)
			{
				printf_s("to %d(%d) ,", tempEdge->toV,tempEdge->weight);
				tempEdge = tempEdge->next;
			}
			printf_s("\n");
		}
	}
	size_t size()const {
		return vertexes.size();
	}
	void Link(int from, int to,int w=1) {
		if (from < vertexes.size() && to < vertexes.size()) {
			vertexes[from].LinkTo(to, w);
		}
	}
	const v & operator[](int i) const {
		return vertexes[i];
	}
	v & operator[](int i){
		return vertexes[i];
	}
	~Graph() {
		for (int i = 0; i < vertexes.size(); i++) {
			vertexes[i].Clear();
		}
	}
private:
	vector<v> vertexes;
};
//堆声明
template<typename Comparable>
class Heap {
protected:
	vector<Comparable> heap;
	int currentSize;
public:
	Heap():currentSize(0) {
		heap.resize(1);
	}
	bool isEmpty()const {
		return currentSize == 0;
	}
	void push(const Comparable &i) {
		if (currentSize == heap.size() - 1)heap.resize(heap.size() * 2);
		int hole = ++currentSize;
		heap[hole] = i;
		PercolateUp(hole);
	}
	void popTo(Comparable & item) {
		if (isEmpty()) {
			//do nothing
		}
		else {
			item = heap[1];
			if (currentSize != 1)
				heap[1] = heap[currentSize--];
			else currentSize--;
			PercolateDown(1);
		}
	}
	void PercolateUp(int hole) {
		for (; hole > 1 && heap[hole]< heap[hole / 2]; hole /= 2)
			Swap(heap[hole], heap[hole / 2]);
	}
	void PercolateDown(int hole) {
		int child=hole*2;
		int tmp = heap[hole].index;
		for (; child <= currentSize; hole = child) {
			printf_s("!");
			child = hole * 2;
			if (child != currentSize&&heap[child + 1] < heap[child])
				child++;
			if(heap[child]<tmp)
				Swap(heap[hole], heap[child]);
			else break;
		}
	}
	virtual void Swap(Comparable &a, Comparable &b) {
		Comparable c;
		c = a;
		a = b;
		b = c;
		//用子类重写加上更改position的代码
	}
	~Heap() {
	}
};

//算法声明
int* positions;//index to position in heap. return -1 when not in heap.
int* distances;//distances
int* paths;	//to record paths from original vertex.
class DijVertex :public Vertex {
public:
	bool operator<(const Vertex & rhs)const {
		//在这定义距离判断
		return (distances[index] < distances[rhs.index]);
	}
	bool operator<(const int rhs)const {
		//在这定义距离判断
		return (distances[index] < rhs);
	}
};
class DijHeap :public Heap<DijVertex> {
public:
	virtual void Swap(DijVertex &a, DijVertex &b) {
		int dc = distances[a.index];
		distances[a.index] = distances[b.index];
		distances[b.index] = dc;
		DijVertex c;
		c = a;
		a = b;
		b = c;
	}
	void popTo(DijVertex & item) {
		if (isEmpty()) {
			//do nothing
		}
		else {
			item = heap[1];
			positions[item.index] = -1;
			if (currentSize != 1)
				heap[1] = heap[currentSize--];
			else currentSize--;
			PercolateDown(1);
		}
	}

};
void ClearData() {
	//delete
	if (positions != NULL)delete[]positions;
	if (distances != NULL)delete[]distances;
	if (paths != NULL)delete[]paths;
}

void DijOutput(int size) {
	if (paths != NULL&&distances != NULL) {
		printf_s("\nIndex \t\tDistance\tPath");
		for (int i = 0; i < size; i++) {
			char d = distances[i] + '0';
			char p = paths[i] + '0';
			printf_s("\n%d \t\t%c \t\t%c", i, d , p);
		}
	}
}
void dijkstra(Graph<DijVertex> &graph, int index) {
	//delete
	if (positions != NULL)delete[]positions;
	if (distances != NULL)delete[]distances;
	if (paths != NULL)delete[]paths;
	//init
	positions = new int[graph.size()];
	distances = new int[graph.size()];
	paths = new int[graph.size()];
	memset(positions, -1, graph.size()*sizeof(int));
	memset(distances, -1, graph.size() * sizeof(int));
	memset(paths, -1, graph.size() * sizeof(int));
	DijHeap heap;
	//func
	distances[index] = 0;
	heap.push(graph[index]);
	DijVertex top;
	while (!heap.isEmpty()) {
		heap.popTo(top);
		Edge *temp = top.edge;
		while (temp != NULL) {
			if (distances[temp->toV] == -1 || distances[temp->toV] > distances[top.index] + temp->weight) {
				distances[temp->toV] = distances[top.index] + temp->weight;
				paths[temp->toV] = top.index;
				if (positions[temp->toV] == -1)
					heap.push(graph[temp->toV]);
				else
					heap.PercolateUp(positions[temp->toV]);
			}
			temp = temp->next;
		}
	}
	//output
	DijOutput(graph.size());
}


void main() {
	Graph<DijVertex> graph(5);
	graph.Link(0, 1);
	graph.Link(1, 2);
	dijkstra(graph, 0);
	_getch();
}