#include <fstream>

#include "Results.h"

Results Results::loadResults(const std::string& filename) {
	std::ifstream results_file(filename);
	Results results;								
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultValue>(result));
	}
	return results;  
}

void Results::saveResults(const std::string& filename, int score) {

	std::ofstream results_file(filename);
	results_file << results.size();
	//for (const auto& result : results) {
	//	//results_file << '\n' << result.first << ' ' << result.second;
	//	results_file << '\n' << result.iteration << ' ' << result.result;
	//}
	//results.clear();
	while (!(results.empty())) {
		//results_file << '\n' << result.first << ' ' << result.second;
		ResultEntry result = popResult();
		results_file << '\n' << result.iteration << ' ' << result.result;
	}
	results_file << '\n' << "Score gained in this stage: " << score;

	results_file.close();
}

//size_t Results::getNextBombIteration() const {
//	//if (!results.empty() && results.front().second == died) {
//	//	return results.front().first;
//	if (!results.empty() && results.front().result == died) {
//		return results.front().iteration;
//	}
//	else return 0;
//	// we use the fact that on iteration zero we cannot hit a bomb
//	// to indicate that there isn't any result left with a hit bomb event
//}

size_t Results::getDiedNextIteration() const {
	if (!results.empty() && results.front().result == died) {
		return results.front().iteration;
	}
	//else return 0;
	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}

