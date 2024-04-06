
#pragma once
#include "undirected_graph.h"
#include <vector>
#include <random>

class MonteCarloPartitioning {
private:
    undirected_graph graph;
    int k;
    std::vector<int> partitionAssignment;

    void randomPartition();
    double evaluatePartition();

public:
    MonteCarloPartitioning(undirected_graph g, int numPartitions);
    std::vector<int> monteCarloPartition(int iterations = 1000);
    void printPartition();
};

