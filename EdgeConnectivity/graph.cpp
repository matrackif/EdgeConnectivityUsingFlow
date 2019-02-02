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
/*	
 * Generates graph with "numOfVertices" number of vertices
 * Probability of any 2 vertices being connected is given by "probability"
 */
Graph generateGraph(uint32_t numOfVertices, double probability)
{
	Graph ret(numOfVertices); // Randomly generated graph to be returned
	static std::random_device rd; // random device engine, usually based on /dev/random on UNIX-like systems
	static std::mt19937 rng(rd()); // initialize Mersennes' twister using rd to generate the seed
	std::bernoulli_distribution bernoulliDistribution(probability); // operator() returns true with probability, and false with 1 - probability
	double cnt = 0;
	// Loop through all rows
	for (unsigned i = 0; i < ret.size(); ++i)
	{
		// Loop through all other vertices, we only have to loop through top half of the adjacency "matrix" because it is symmetric
		// Since if vertex i is connected to j, then j is connected to i
		for (unsigned j = i + 1; j < numOfVertices; ++j)
		{
			// This if statement has a "probability" of being true
			// For example if probability = 0.55 then it will return true 0.55 * 100 = 55% of the time
			// And it returns false (1 - 0.55) * 100 = 45% of the time
			if (bernoulliDistribution(rng))
			{
				// We connect vertex i with j, and j with i
				ret[i].push_back(j);
				ret[j].push_back(i);
			}
		}
	}
	return ret;
}

template<typename Vec, typename VecType>
void fill1DVec(Vec & vec, VecType vt)
{
	vec.assign(vec.size(), vt);
}

template<typename Vec, typename VecType>
void fill2DVec(Vec & vec, VecType vt)
{
	for (auto & row : vec)
	{
		fill1DVec(row, vt);
	}
}

uint32_t EdgeConnectivityCalculator::bfs(uint32_t u, uint32_t v)
{
	uint32_t vertexCount = g_.size();
	std::queue<uint32_t> queue;
	queue.push(u);

	while (!queue.empty())
	{
		const uint32_t i = queue.front();
		queue.pop();
		for (uint32_t j = 0; j < g_[i].size(); ++j)
		{
			uint32_t neighbor = g_[i][j];
			uint32_t currentResidualCapacity = edgeCapacity_[i][j] - currentFlow_[i][j];
			if (path_[neighbor] == -1 && (currentResidualCapacity > 0))
			{
				path_[neighbor] = i;
				residualCapacity_[neighbor] = std::min(residualCapacity_[i], currentResidualCapacity);
				if (neighbor != v)
				{
					queue.push(neighbor);
				}
				else
				{
					return residualCapacity_[v];
				}
			}
		}
	}

	return 0;
}

uint32_t EdgeConnectivityCalculator::edmondsKarp(uint32_t source, uint32_t sink)
{
	clearData();
	uint32_t pathFlow = 0, maxFlow = 0;
	while (true)
	{
		fill1DVec(residualCapacity_, 0);
		fill1DVec(path_, -1);
		residualCapacity_[source] = std::numeric_limits<uint32_t>::max();
		path_[0] = -2;
		pathFlow = bfs(source, sink);
		if (pathFlow <= 0)
		{
			break;
		}
		maxFlow += pathFlow;
		uint32_t s = sink;
		while (s != source)
		{
			uint32_t prev = path_[s];
			// Workaround, maybe we should use a matrix instead of a 2d list after all?
			uint32_t indexOfPrev = std::distance(g_[s].begin(), std::find(g_[s].begin(), g_[s].end(), prev));
			uint32_t indexOfS = std::distance(g_[prev].begin(), std::find(g_[prev].begin(), g_[prev].end(), s));
			currentFlow_[prev][indexOfS] += pathFlow;
			currentFlow_[s][indexOfPrev] -= pathFlow;
			s = prev;
		}
	}
	return maxFlow;
}

uint32_t EdgeConnectivityCalculator::findEdgeConnectivity()
{
        if (g_.size() < 1)
            return 0;
	uint32_t result = g_[0].size();
	for (uint32_t i = 1; i < g_.size(); i++)
	{
		result = std::min(result, edmondsKarp(0, i));
	}
	return result;
}

void EdgeConnectivityCalculator::clearData()
{
	fill2DVec(currentFlow_, 0);
	fill2DVec(edgeCapacity_, 1);
	fill1DVec(path_, -1);
	fill1DVec(residualCapacity_, 0);
	residualCapacity_[0] = std::numeric_limits<uint32_t>::max(); // not necessary here?
	path_[0] = -2; // so we can visit the first vertex in BFS
}

void EdgeConnectivityCalculator::initializeDataFromGraph(Graph & g)
{
	// Copy graph structure 
	g_ = Graph(g);
	edgeCapacity_ = Graph(g);
	currentFlow_ = FlowVecType(g.size());
	for (uint32_t i = 0; i < currentFlow_.size(); i++)
	{
		currentFlow_[i].resize(g_[i].size(), 0);
	}
	residualCapacity_ = std::vector<uint32_t>(g.size());
	path_ = std::vector<int>(g.size());
	//clearData();
}

EdgeConnectivityCalculator::EdgeConnectivityCalculator() 
{
}

uint32_t EdgeConnectivityCalculator::findEdgeConnectivity(Graph & g)
{
	initializeDataFromGraph(g);
	return findEdgeConnectivity();
}
