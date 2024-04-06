#include "kernighan_lin.h"

kernighan_lin::kernighan_lin(undirected_graph g,int k) { 
	gr = g;
	init_part(k);


	for (int x = 0; x < k; x++) {
		for (int y = x + 1; y < k; y++) {
			gr = g;

			kernlinFor2Part(partitions[x], partitions[y]);
		}
	}
	printPartitions();
}
void kernighan_lin::init_part(int k) {
	std::set<int>vertices;
	vertices= gr.getVertices();
	auto m = vertices.begin();
	int t = 0;
	while (m != vertices.end()) {
		partitions[t % k].insert(*m);
		t++;
		m++;
	}
		
	
	vertices.clear();
}
int kernighan_lin::calcDvalue(int vertex) {
	int cost=0,inC=0;
	int i=0;
	for (auto k=partitions.begin();k!=partitions.end(); i++) {
		if (partitions[i].find(vertex) != partitions[i].end()) {
		
			break;
		}k++;
	};
	std::set<int>adjList;
	gr.getAdjacencyList(adjList, vertex);
	for (auto a = adjList.begin(); a != adjList.end(); a++) {
		cost++;
		if (partitions[i].find(*a) != partitions[i].end()) {
			inC++;
		}
	}
	cost = cost - 2 * inC;
	return cost;
}
void kernighan_lin::kernlinFor2Part(std::set<int>& part1, std::set<int>& part2) {
	std::unordered_map<int, int> Dvalue1, Dvalue2;
	undirected_graph initialGraph = gr;
	std::list<int> gv, av, bv;

	std::set<int>::iterator forLoop1Ind, forLoop2Ind;
	int maxGain = 0;
	
	do {
		
		forLoop1Ind = part1.begin();
		forLoop2Ind = part2.begin();
		int start1 = INT16_MAX, start2 = INT16_MAX, end1 = 0, end2 = 0;
		while (forLoop1Ind != part1.end()) {
			int key = *forLoop1Ind;
			Dvalue1.insert({ key,calcDvalue(key) });
			start1 = std::min(start1, key);
			end1 = std::max(end1, key);
			forLoop1Ind++;
		}
		
		while (forLoop2Ind != part2.end()) {
			int key = *forLoop2Ind;
			Dvalue2.insert({ key,calcDvalue(key) });
			start2 = std::min(start2,key);
			end2 = std::max(end2, key);
			forLoop2Ind++;
		}
		int index1 = start1, index2 = start2, maxG = 0, gValue, temp, at, bt;
		std::set<int> adjList;
		bool initiliazed = false;
		if (part1.empty()) {
			break;
		}
		if (part2.empty()) {
				break;
		}
		for(int runinTime = 0;runinTime<=part1.size();runinTime++){
			while (index1 <= end1) {
				if (part1.find(index1) == part1.end()) {
					index1++;
					continue;
				}
				index2 = start2;
				while (index2 <= end2) {
					if (part2.find(index2) == part2.end()) {
						index2++;
						continue;
					}
					gr.getAdjacencyList(adjList, index1);
					if (adjList.find(index2) != adjList.end()) {
						gValue = -2;

					}
					else {
						gValue = 0;
					}

					gValue = gValue + Dvalue1[index1] + Dvalue2[index2];

					temp = maxG;
					maxG = std::max(maxG, gValue);

					if (temp != maxG) {
						initiliazed = true;
						at = index1;
						bt = index2;
					}
					index2++;
				}
				index1++;
			}
		}
		gv.push_back(maxG);
		if (initiliazed) {
			av.push_back(at);
			bv.push_back(bt);
			part1.erase(at);
			part2.erase(bt);
			gr.delete_vertex(at);
			gr.delete_vertex(bt);
		}
		for (auto i = gv.begin(); i != gv.end(); i++) {
			maxGain += *i;
		}
		

	} while (maxGain>0 );
	gr = initialGraph;
	for (auto fillingInd = av.begin(); fillingInd != av.end(); fillingInd++) {
		part2.insert(*fillingInd);
	}
	for (auto fillingInd = bv.begin(); fillingInd != bv.end(); fillingInd++) {
		part1.insert(*fillingInd);
	}

}
void kernighan_lin::printPartitions() {
	std::unordered_map<int,std::set<int>>::iterator printInd = partitions.begin();
	std::set<int>::iterator printInd2;
	while (printInd != partitions.end()) {
		std::cout << "Partition number:" << printInd->first << " Vertices:";
		printInd2 = printInd->second.begin();
		while (printInd2 != printInd->second.end()) {
			std::cout << *printInd2 << " ";
			printInd2++;
		} 
		printInd++;
		std::cout << std::endl;
	}
	}