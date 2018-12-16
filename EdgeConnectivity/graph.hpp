#ifndef __GRAPH__HPP__
#define __GRAPH__HPP__

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
// Graph typedefs
typedef std::vector<std::vector<uint32_t>> Graph;
typedef Graph::iterator GraphIterator;
typedef Graph::const_iterator GraphConstIterator;

// Operator overloads
std::ostream & operator<<(std::ostream &stream, const Graph &g);
template<uint32_t N>
void fillValues(std::vector<uint32_t> & connections);
template<uint32_t N>
void fillGraph(Graph & g);
// Class that will calculate edge connectivity using flow
class EdgeConnectivityCalculator
{
private:
	Graph &g_;
	Graph edgeCapacity_;
	Graph currentFlow_;
	std::vector<uint32_t> residualCapacity_;
	std::vector<uint32_t> path_;
	uint32_t bfs();
	uint32_t edmondsKarp(uint32_t source, uint32_t sink);
	uint32_t findEdgeConnectivity();

public:
	EdgeConnectivityCalculator(Graph &g);
	
};

#endif // ifndef __GRAPH__HPP__
