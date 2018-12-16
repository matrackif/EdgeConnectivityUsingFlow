#include "graph.hpp"

// Operator overloads
std::ostream & operator<<(std::ostream &stream, const Graph &g)
{
	stream << "Number of vertices in graph: " << g.size() << std::endl;
	for (uint32_t i = 0; i < g.size(); ++i)
	{
		std::cout << "Vertex: " << i << " has neighbors: " << std::endl;
		for (auto &neighbor : g[i])
		{
			stream << neighbor << ", ";
		}
		stream << std::endl;
	}
	return stream;
}

template<uint32_t N>
void fillValues(std::vector<uint32_t> & connections)
{
	connections.assign(connections.size(), N);
}
template<uint32_t N>
void fillGraph(Graph & g)
{
	std::for_each(g.begin(), g.end(), fillValues<N>);
}
// TODO
uint32_t EdgeConnectivityCalculator::bfs(uint32_t source, uint32_t sink)
{
	return uint32_t();
}
// TODO
uint32_t EdgeConnectivityCalculator::edmondsKarp(uint32_t source, uint32_t sink)
{
	return uint32_t();
}

uint32_t EdgeConnectivityCalculator::findEdgeConnectivity()
{
	uint32_t result = g_[0].size();
	for (uint32_t i = 1; i < g_.size(); i++)
	{
		result = std::min(result, edmondsKarp(0, i));
	}
	return result;
}

EdgeConnectivityCalculator::EdgeConnectivityCalculator(Graph & g)
	: g_(g),
	edgeCapacity_(g),
	currentFlow_(g),
	residualCapacity_(g.size(), std::numeric_limits<uint32_t>::infinity()),
	path_(g.size(), -1)
{
	uint32_t maxFlow = 0, pathFlow = 0;
	fillGraph<1>(edgeCapacity_);
	fillGraph<0>(currentFlow_);
	std::cout << "Found edge connectivity: " << findEdgeConnectivity();

}
