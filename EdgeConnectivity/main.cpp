#include "graph.hpp"
#include "graph_io.hpp"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " input_graph.txt" << std::endl;
		return 1;
	}

	Graph g = readGraph(argv[1]);
	EdgeConnectivityCalculator ecc;
	std::cout << ecc.findEdgeConnectivity(g) << std::endl;
	return 0;
}
