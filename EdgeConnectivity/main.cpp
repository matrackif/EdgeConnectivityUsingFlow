#include "graph.hpp"

int main(int argc, char **argv)
{
	// create test graph
	Graph g = { { 1, 2 },  { 0, 2 }, { 0, 1, 3 }, { 2, 4, 5 }, { 3, 5 },  { 3, 4 } };
	Graph g2 = { { 1, 2 },  { 0, 2 }, { 0, 1, 3, 4 }, { 2, 4, 5 }, { 2, 3, 5 },  { 3, 4 } };
	std::cout << g;
	EdgeConnectivityCalculator ecc;
	std::cout << " g edge connectivity: " << ecc.findEdgeConnectivity(g) << std::endl;
	std::cout << " g2 edge connectivity: " << ecc.findEdgeConnectivity(g2) << std::endl;
	return 0;
}
