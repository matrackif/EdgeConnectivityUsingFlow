#include "graph.hpp"

int main(int argc, char **argv)
{
	// create test graph
	Graph g = { { 1, 2 },  { 0, 2 }, { 0, 1, 3 }, { 2, 4, 5 }, { 3, 5 },  { 3, 4 } };
	std::cout << g;
	EdgeConnectivityCalculator ecc(g);
	return 0;
}