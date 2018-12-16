#include "graph.hpp"

int main(int argc, char **argv)
{
	// create test graph
	Graph g(6);
	g[0] = { 1, 2 };
	g[1] = { 0, 2 };
	g[2] = { 0, 1, 3 };
	g[3] = { 2, 4, 5 };
	g[4] = { 3, 5 };
	g[5] = { 3, 4 };
	std::cout << g;
	EdgeConnectivityCalculator ecc(g);
	return 0;
}