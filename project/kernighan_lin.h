#pragma once
#include "undirected_graph.h"
#include <unordered_map>
#include <set>
class kernighan_lin
{
	undirected_graph gr;
	std::unordered_map<int, std::set<int>> partitions;
	void init_part(int k);
	int calcDvalue(int vertex);
	void kernlinFor2Part(std::set<int>& part1, std::set<int>& part2);
	void printPartitions();
public:
	kernighan_lin(undirected_graph g,int k);
	

};

