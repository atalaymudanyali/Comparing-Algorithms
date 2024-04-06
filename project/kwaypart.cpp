#include "kwaypart.h"
#include <limits>
#include <iostream>
#include <unordered_set>


kwaypartitioning::kwaypartitioning(undirected_graph g, int numPartitions)
    : graph(g), k(numPartitions), partitionAssignment(g.getVertexCount(), 0) {}

void kwaypartitioning::kwaygraphpart() {
    for (int i = 1; i < k; ++i) {
        int minCutVertex = findMinCutVertex(i);
        if (minCutVertex == -1) {
            std::cout << "Skipping partition\n";
            continue;
        }
        partitionAssignment[minCutVertex] = i;
    }
    balancePart();
}

int kwaypartitioning::calculateCutSizeP(int partition) const {
    int cutSize = 0;
    int** adjMatrix = const_cast<undirected_graph*>(&graph)->create_adjMatrix();
    for (int i = 0; i < graph.getVertexCount(); ++i) {
        for (int j = i + 1; j < graph.getVertexCount(); ++j) {
            if (partitionAssignment[i] == partition && partitionAssignment[j] != partition && adjMatrix[i][j] == 1) {
                cutSize++;
            }
        }
    }
    delete[] adjMatrix;
    return cutSize;
}

void kwaypartitioning::balancePart() {
    const int maxBalanceDifference = 1;  
    while (true) {
        for (int p = 0; p < k; ++p) {
            auto verticesInPartition = std::count(partitionAssignment.begin(), partitionAssignment.end(), p);
            for (int q = 0; q < k; ++q) {
                if (p != q) {
                    auto verticesInOtherPartition = std::count(partitionAssignment.begin(), partitionAssignment.end(), q);
                    if (verticesInPartition > verticesInOtherPartition + maxBalanceDifference) {
                        for (int i = 0; i < graph.getVertexCount(); ++i) {
                            if (partitionAssignment[i] == p) {
                                partitionAssignment[i] = q;
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
        bool partitionsBalanced = true;
        for (int p = 0; p < k; ++p) {
            auto verticesInPartition = std::count(partitionAssignment.begin(), partitionAssignment.end(), p);
            for (int q = 0; q < k; ++q) {
                if (p != q) {
                    auto verticesInOtherPartition = std::count(partitionAssignment.begin(), partitionAssignment.end(), q);
                    if (verticesInPartition > verticesInOtherPartition + maxBalanceDifference) {
                        partitionsBalanced = false;
                        break;
                    }
                }
            }
            if (!partitionsBalanced) {
                break;
            }
        }
        if (partitionsBalanced) {
            break;
        }
    }
    printPartition();
}

int kwaypartitioning::calculateCutSize() {
    int cutSize = 0;
    int** adjMatrix = graph.create_adjMatrix();
    for (int i = 0; i < graph.getVertexCount(); ++i) {
        for (int j = i + 1; j < graph.getVertexCount(); ++j) {
            if (partitionAssignment[i] != partitionAssignment[j] && adjMatrix[i][j] == 1) {
                cutSize++;
            }
        }
    }
    delete[] adjMatrix;
    return cutSize;
}

int kwaypartitioning::findMinCutVertex(int vertex) {
    int minCutSize = std::numeric_limits<int>::max();
    int minCutVertex = -1;
    for (int i = 0; i < graph.getVertexCount(); ++i) {
        if (partitionAssignment[i] == 0) {
            partitionAssignment[i] = vertex;
            int currentCutSize = calculateCutSize();
            if (currentCutSize < minCutSize) {
                minCutSize = currentCutSize;
                minCutVertex = i;
            }
            partitionAssignment[i] = 0;
        }
    }
    if (minCutVertex == -1) {
        for (int i = 0; i < graph.getVertexCount(); ++i) {
            if (partitionAssignment[i] == 0) {
                minCutVertex = i;
                break;
            }
        }
    }
    return minCutVertex;
}

void kwaypartitioning::printPartition() {
    std::vector<std::set<int>> partitions(k);
    for (int i = 0; i < graph.getVertexCount(); ++i) {
        int partition = partitionAssignment[i];
        if (partition != -1) {
            partitions[partition].insert(i);
        }
    }
    for (int partition = 0; partition < k; ++partition) {
        const std::set<int>& vertices = partitions[partition];
        std::cout << "Partition " << partition + 1 << ": {";
        bool first = true;
        for (int vertex : vertices) {
            if (!first) {
                std::cout << ", ";
            }
            std::cout << vertex;
            first = false;
        }
        std::cout << "}\n";
    }
}