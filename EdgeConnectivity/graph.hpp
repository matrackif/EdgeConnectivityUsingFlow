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

// Utility functions for filling the graph with default values
template<uint32_t N>
void fillValues(std::vector<uint32_t> & connections);
template<uint32_t N>
void fillGraph(Graph & g);

// Class that will calculate edge connectivity using flow
class EdgeConnectivityCalculator
{
private:
	Graph &g_; // Graph stored as an adjacency list
	Graph edgeCapacity_; // Stores edge capacity of graph (should be initialized to all ones)
	Graph currentFlow_; // Adjacency list of edges represting current amount of flow passing through an edge
	std::vector<uint32_t> residualCapacity_; // Adjacency list representing the amount of flow that can still pass through an edge
	std::vector<uint32_t> path_; // Vector that stores the current path between 2 vertices (usually source and sink in our case)
	uint32_t bfs(uint32_t source, uint32_t sink); // Finds a path between source and sink
	uint32_t edmondsKarp(uint32_t source, uint32_t sink); // Find maximal flow between source and sink
	uint32_t findEdgeConnectivity(); // Returns edge connectivity of the graph "g_"
public:
	EdgeConnectivityCalculator(Graph &g);
};

#endif // ifndef __GRAPH__HPP__
