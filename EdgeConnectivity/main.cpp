#include "graph.hpp"
#include "graph_io.hpp"
#include <chrono>
#include <math.h>

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
	
	// Uncomment below in order to test execution time
	/*
	EdgeConnectivityCalculator ecc;
	for (int i = 0; i < 10; i++)
	{
		//uint32_t numvertices = pow(10, (i + 1));
		uint32_t numvertices = 100 * (i + 1);
		Graph gr;
		gr.push_back({0});
		for (uint32_t j = 1; j < numvertices - 1; j += 2)
		{
			gr.push_back({ j - 1, j + 1 });
		}
		gr.push_back({ numvertices - 2 });
		auto started = std::chrono::high_resolution_clock::now();
		ecc.findEdgeConnectivity(gr);
		auto done = std::chrono::high_resolution_clock::now();
		std::cout << "numvertices: " << numvertices << " time: " << std::chrono::duration_cast<std::chrono::milliseconds>(done - started).count() << std::endl;
	}
	*/
	return 0;
}
