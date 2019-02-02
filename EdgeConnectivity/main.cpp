#include "graph.hpp"
#include "graph_io.hpp"
#include <chrono>
#include <math.h>

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		// if (argc == 3) it means we wish to generate random graphs and test them
		// argv[1] is number of vertices in each graph
		// argv[2] is the probability in range [0.0, 1.0] of vertex i being connected to vertex j
		// We output the results to a CSV file
		unsigned numVertices = std::stoi(argv[1]);
		double probability = std::stod(argv[2]);
		probability = (probability > 1.0) ? 1.0 : probability;
		probability = (probability < 0.0) ? 0.0 : probability;
		EdgeConnectivityCalculator ecc;
		std::ofstream output("exec_time_results.txt");
		// Write header
		output << "NumVertices,Probability,ExecTimeMicrosec" << std::endl;
		// Fix probability and vary number of vertices from 2..numVertices
		for (unsigned i = 2; i <= numVertices; ++i)
		{
			Graph gen = generateGraph(i, probability);
			auto started = std::chrono::high_resolution_clock::now();
			ecc.findEdgeConnectivity(gen);
			auto done = std::chrono::high_resolution_clock::now();
			unsigned execTimeMicrosec = std::chrono::duration_cast<std::chrono::microseconds>(done - started).count();
			output << i << "," << probability << "," << execTimeMicrosec << std::endl;
		}
		// Fix number of vertices = numVertices and vary probability from 0.05, 0.1, 0.15, ..., 1.0
		for (double p = 0.05; p <= 1.0; p += 0.05)
		{
			Graph gen = generateGraph(numVertices, p);
			auto started = std::chrono::high_resolution_clock::now();
			ecc.findEdgeConnectivity(gen);
			auto done = std::chrono::high_resolution_clock::now();
			unsigned execTimeMicrosec = std::chrono::duration_cast<std::chrono::microseconds>(done - started).count();
			output << numVertices << "," << p << "," << execTimeMicrosec << std::endl;
		}
	}

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
