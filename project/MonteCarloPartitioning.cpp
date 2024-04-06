#include "MonteCarloPartitioning.h"
#include <iostream>
#include <limits>

MonteCarloPartitioning::MonteCarloPartitioning(undirected_graph g, int numPartitions)
    : graph(g), k(numPartitions), partitionAssignment(g.getVertexCount(), 0) {}

void MonteCarloPartitioning::randomPartition() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, k - 1);

    for (int i = 0; i < k; ++i) {
        if (i < graph.getVertexCount()) {
            partitionAssignment[i] = i;
        }
    }

    for (int i = k; i < graph.getVertexCount(); ++i) {
        partitionAssignment[i] = distrib(gen);
    }
}

double MonteCarloPartitioning::evaluatePartition() {
    double cutSize = 0;
    int** adjMatrix = graph.create_adjMatrix();

    for (int i = 0; i < graph.getVertexCount(); ++i) {
        for (int j = 0; j < graph.getVertexCount(); ++j) {
            if (adjMatrix[i][j] == 1 && partitionAssignment[i] != partitionAssignment[j]) {
                cutSize++;
            }
        }
    }

    for (int i = 0; i < graph.getVertexCount(); ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;

    return cutSize;
}

std::vector<int> MonteCarloPartitioning::monteCarloPartition(int iterations) {
    std::vector<int> bestPartition;
    double bestQuality = std::numeric_limits<double>::max();

    for (int i = 0; i < iterations; ++i) {
        randomPartition();
        double currentQuality = evaluatePartition();

        if (currentQuality < bestQuality) {
            bestQuality = currentQuality;
            bestPartition = partitionAssignment;
        }
    }

    return bestPartition;
}

void MonteCarloPartitioning::printPartition() {
    for (int i = 0; i < k; ++i) {
        std::cout << "Partition " << i + 1 << ": ";
        for (int j = 0; j < graph.getVertexCount(); ++j) {
            if (partitionAssignment[j] == i) {
                std::cout << j << " ";
            }
        }
        std::cout << std::endl;
    }
}