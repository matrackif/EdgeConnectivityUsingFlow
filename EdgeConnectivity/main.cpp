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

		// Initialize hardcoded constant variables
		const unsigned MAX_ITERS = 50;
		const unsigned VERTEX_INCREMENT = numVertices / MAX_ITERS;
		const double PROB_INCREMENT = probability / MAX_ITERS;
		const unsigned remainder = numVertices % MAX_ITERS;
		const std::string HEADER = "NumVertices,Probability,ExecTimeMicrosec";

		EdgeConnectivityCalculator ecc;
		
		
		std::ofstream output1("num_vertices_test.txt");
		output1 << HEADER << std::endl;
		unsigned vertexIncrement = (remainder == 0) ? VERTEX_INCREMENT : VERTEX_INCREMENT + 1;
		// Fix probability and vary number of vertices linearly from vertexIncrement to numVertices
		for (unsigned i = 0, j = vertexIncrement; i < MAX_ITERS; ++i, j += vertexIncrement)
		{
			vertexIncrement = (i < remainder - 1) ? VERTEX_INCREMENT + 1 : VERTEX_INCREMENT;
			Graph gen = generateGraph(j, probability);
			auto started = std::chrono::high_resolution_clock::now();
			ecc.findEdgeConnectivity(gen);
			auto done = std::chrono::high_resolution_clock::now();
			long long execTimeMicrosec = std::chrono::duration_cast<std::chrono::microseconds>(done - started).count();
			output1 << j << "," << probability << "," << execTimeMicrosec << std::endl;
		}
		// Fix number of vertices = numVertices and vary probability evenly from 0 to 1
		std::ofstream output2("probability_test.txt");
		for (double p = PROB_INCREMENT; p < 1 + PROB_INCREMENT; p += PROB_INCREMENT)
		{
			double prob = (p > 1 ? 1 : p);
			Graph gen = generateGraph(numVertices, prob);
			auto started = std::chrono::high_resolution_clock::now();
			ecc.findEdgeConnectivity(gen);
			auto done = std::chrono::high_resolution_clock::now();
			long long execTimeMicrosec = std::chrono::duration_cast<std::chrono::microseconds>(done - started).count();
			output2 << numVertices << "," << prob << "," << execTimeMicrosec << std::endl;
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
