#include "undirected_graph.h"

undirected_graph::undirected_graph() {
	vertNum = 0;
}
undirected_graph::undirected_graph(std::unordered_map<int, std::set<int>> adjList) {
	vertNum = 0;
	for (auto i = adjList.begin(); i != adjList.end(); i++) {
		vertices.insert(i->first);
		if (i->first > vertNum) {
			vertNum = i->first;
		}
	}
	adjacencyList = adjList;
}
undirected_graph::~undirected_graph() {
	adjacencyList.clear();
}
std::set<int> undirected_graph::getVertices() {
	return vertices;
}
void undirected_graph::getAdjacencyList(std::set<int>& adjList,int vertex) {
	adjList=adjacencyList[vertex];
}
int undirected_graph::getVertNum() { return vertNum; }
void undirected_graph::add_vertex(int v) {
	vertices.insert(v);
	vertNum++;
}
void undirected_graph::add_edge(int first, int second) {
	if (adjacencyList[first].empty())
		vertNum++;
	if (adjacencyList[second].empty())
		vertNum++;
	{
		adjacencyList[first].insert(second);
		adjacencyList[second].insert(first);
	}
}
void undirected_graph::delete_vertex(int v) {
	vertNum--;
	vertices.erase(v);
	adjacencyList[v].clear();
	for (auto index = adjacencyList.begin(); index != adjacencyList.end(); index++) {
		std::set<int> checkPair = index->second;
		if (checkPair.find(v) != checkPair.end()) {
			int key = *checkPair.find(v);
			adjacencyList[key].erase(v);
	}
	}
}
void undirected_graph::delete_edge(int first, int second) {
	adjacencyList[first].erase(second);
	adjacencyList[second].erase(first);
}
int size = 0;
int** undirected_graph::create_adjMatrix() {
	

	for (auto i = vertices.begin(); i != vertices.end(); i++) {
		if (*i > size) {
			size = *i;
		}
	}
	adjMatrix = new int* [size+1 ];
	for (int i = 0; i < size+1; i++) {
		adjMatrix[i] = new int[size + 1];
	}
	for (int k = 0; k <= size; k++) {
		for (int j = 0; j <= size; j++) {
			adjMatrix[k][j] = 0;
		}
	}

	for (auto i = adjacencyList.begin(); i != adjacencyList.end(); i++) {
		int firstVertex = i->first;
		std::set<int>adjList = i->second;
		for (auto k = adjList.begin(); k != adjList.end(); k++) {
			int secondVertex = *k;
			adjMatrix[firstVertex][secondVertex] = 1;
		}

	}
	return adjMatrix;
}
void undirected_graph::printGraph() {
	adjMatrix = this->create_adjMatrix();
	for (int i = 0; i < size + 1; i++) {
		for (int k = 0; k < size+ 1; k++) {
			std::cout << adjMatrix[i][k];
		}
		std::cout << std::endl;
	}

}
int undirected_graph::getVertexCount() const {
	return vertices.size();
	std::cout << vertices.size();
}
const std::set<int>& undirected_graph::getAdjacencyList(int v) const {
	return adjacencyList.at(v);
}
