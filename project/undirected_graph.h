#pragma once
#include <unordered_map>
#include <iostream>
#include <set>

class undirected_graph {
private:
    int** adjMatrix;
    int vertNum;
    std::set<int> vertices;
    std::unordered_map<int, std::set<int>> adjacencyList;
public:
<<<<<<< HEAD
    undirected_graph(std::unordered_map<int, std::set<int>>);
    ~undirected_graph();
    void add_vertex(int v);
    void add_edge(int first, int second);
    void delete_vertex(int v);
    void delete_edge(int first, int second);
    int** create_adjMatrix();
    void printGraph();
    int getVertexCount() const;
    const std::set<int>& getAdjacencyList(int v) const;
=======
	undirected_graph();
	undirected_graph(std::unordered_map<int, std::set<int>>);
	~undirected_graph();
	std::set<int> getVertices();
	int getVertNum();
	void getAdjacencyList(std::set<int>& adjList,int vertex);
	void add_vertex(int v);
	void add_edge(int first, int second);
	void delete_vertex(int v);
	void delete_edge(int first, int second);
	int** create_adjMatrix();
	void printGraph();
>>>>>>> 094234833080c57dc62d9191982e2f145577168a
};
