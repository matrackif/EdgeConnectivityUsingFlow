#include "graph_io.hpp"

#include <fstream>
#include <iterator>
#include <sstream>

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str);

Graph readGraph(const std::string &filename)
{
	Graph result{};

	std::ifstream file{filename};

	for (std::vector<std::string> cells = getNextLineAndSplitIntoTokens(file);
	     !cells.empty();
	     cells = getNextLineAndSplitIntoTokens(file))
	{
		size_t vertex = std::stoi(cells[0]);

		if (result.size() < vertex + 1)
			result.resize(vertex + 1);

		std::transform(++cells.begin(), cells.end(),
			       std::back_inserter(result[vertex]),
			       [](const std::string& str) {
				       return std::stoi(str);
			       });
	}

	return result;
}

// https://stackoverflow.com/a/1120224/795068
std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
{
	std::vector<std::string>   result;
	std::string                line;
	std::getline(str, line);
	if (line.empty())
		return result;

	std::stringstream          lineStream(line);
	std::string                cell;

	while (std::getline(lineStream, cell, ','))
	{
		result.push_back(cell);
	}
	// This checks for a trailing comma with no data after it.
	if (!lineStream && cell.empty())
	{
		// If there was a trailing comma then add an empty element.
		result.push_back("");
	}
	return result;
}
