#pragma once
#include "undirected_graph.h"

class kwaypartitioning {
private:
    undirected_graph graph;
    int k;
    std::vector<int> partitionAssignment;
    int calculateCutSize();
    int findMinCutVertex(int vertex);
    int calculateCutSizeP(int partition) const;
   
public:
    kwaypartitioning(undirected_graph g, int numPartitions);
    void kwaygraphpart();
    void printPartition();
    void balancePart();
};
