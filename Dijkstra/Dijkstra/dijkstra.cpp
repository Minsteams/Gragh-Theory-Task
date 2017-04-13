#include"dijkstra.h"
int* positions;//index to position in heap. return -1 when not in heap.
int* distances;//distances
int* paths;	//to record paths from original vertex.
bool DijVertex ::operator<(const Vertex & rhs)const {
	return (distances[index] < distances[rhs.index]);
}
bool DijVertex ::operator<(const int rhs)const {
	return (distances[index] < rhs);
}
void DijHeap::Swap(DijVertex &a, DijVertex &b) {
	int dc = distances[a.index];
	distances[a.index] = distances[b.index];
	distances[b.index] = dc;
	DijVertex c;
	c = a;
	a = b;
	b = c;
}
void DijHeap::popTo(DijVertex & item) {
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
			printf_s("\n%d \t\t%c \t\t%c", i, d, p);
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
	memset(positions, -1, graph.size() * sizeof(int));
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
	DijOutput((int)graph.size());
}