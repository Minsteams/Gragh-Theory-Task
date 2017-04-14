#include"dijkstra.h"
int* positions;//index to position in heap. return -1 when not in heap.
int* distances;//distances
int* paths;	//to record paths from original vertex.
void DijVertex ::operator =(const Vertex & rhs) {
	index = rhs.index;
	edge = rhs.edge;
}
bool DijVertex ::operator<(const Vertex & rhs)const {
	return (distances[index] < distances[rhs.index]);
}
bool DijVertex ::operator<(const int rhs)const {
	return (distances[index] < rhs);
}
void DijHeap::Swap(DijVertex &a, DijVertex &b) {
	int dc = positions[a.index];
	positions[a.index] = positions[b.index];
	positions[b.index] = dc;
	DijVertex c;
	c = a;
	a = b;
	b = c;
}
void DijHeap::push(const DijVertex &i) {
	if (currentSize == heap.size() - 1)heap.resize(heap.size() * 2);
	int hole = ++currentSize;
	heap[hole] = i;
	PercolateUp(hole);
}
void DijHeap::popTo(DijVertex **item) {
	if (isEmpty()) {
		//do nothing
		if (*item != NULL)delete *item;
	}
	else {
		if (*item == NULL)*item = new DijVertex();
		**item = heap[1];
		positions[(*item)->index] = -1;
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
			printf_s("\n%d \t\t%d \t\t%d", i, distances[i], paths[i]);
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
	paths[index] = index;
	DijVertex *top=NULL;
	while (!heap.isEmpty()) {
		heap.popTo(&top);
		if (top->index == -1)break;
		Edge *temp = top->edge;
		
		while (temp != NULL) {
			if (distances[temp->toV] == -1 || distances[temp->toV] > (distances[top->index] + temp->weight)) {
				distances[temp->toV] = distances[top->index] + temp->weight;
				paths[temp->toV] = top->index;
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