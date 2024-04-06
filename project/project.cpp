
#include <iostream>
#include "undirected_graph.h"
<<<<<<< HEAD
#include "kwaypart.h"
#include "MonteCarloPartitioning.h"
=======
#include "kernighan_lin.h"


>>>>>>> 094234833080c57dc62d9191982e2f145577168a
int main()
{
    std::unordered_map<int, std::set<int>> g;
    undirected_graph graph(g);
<<<<<<< HEAD
    for (int i = 0; i < 5; ++i) {
        graph.add_vertex(i);
    }
    graph.add_edge(0, 1);
=======
  
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
>>>>>>> 094234833080c57dc62d9191982e2f145577168a
    graph.add_edge(0, 2);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
<<<<<<< HEAD
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);
    graph.printGraph();
    int k = 2;
    kwaypartitioning partfork(graph, k);
    partfork.kwaygraphpart();
    std::cout << std::endl;
    int n = 5;
    MonteCarloPartitioning partitioner(graph, n);
    int iterations = 100;
    std::vector<int> bestPartition = partitioner.monteCarloPartition(iterations);
    partitioner.printPartition();
=======
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
    kernighan_lin(graph,2);

=======
    graph.printGraph();
>>>>>>> eaff3edd8e1770f5e54f21903fbf8e81e8d380e3
=======
    graph.printGraph();
>>>>>>> eaff3edd8e1770f5e54f21903fbf8e81e8d380e3
=======
    graph.printGraph();
>>>>>>> eaff3edd8e1770f5e54f21903fbf8e81e8d380e3

>>>>>>> 094234833080c57dc62d9191982e2f145577168a
}
