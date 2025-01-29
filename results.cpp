#include <fstream>

#include "Results.h"

// The function was taken from what was learned in the lesson
// Loads results from a file and returns a Results object 
Results Results::loadResults(const std::string& filename) {
	std::ifstream results_file(filename);
	Results results;								
	size_t size;
	results_file >> size;

	while (!results_file.eof() && size-- != 0) {						// Ensure we do not read beyond file size
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultValue>(result));
	}
	return results;  
}

// The function was taken from what was learned in the lesson
// Saves the current results to a file, including the player's score 
void Results::saveResults(const std::string& filename, int score) 
{
	std::ofstream results_file(filename);
	results_file << results.size();

	while (!(results.empty())) {										// Write each result as "iteration resultValue"
		ResultEntry result = popResult();
		results_file << '\n' << result.iteration << ' ' << result.result;
	}

	if (score < 0)			// In case if mario loses life more he gained socres
		score = 0;

	results_file << '\n' << "Score gained in this stage: " << score;

	results_file.close();
}

// The function was taken from what was learned in the lesson
// Returns the iteration number when the next "died" event occurs 
size_t Results::getDiedNextIteration() const {
	if (!results.empty() && results.front().result == died) {
		return results.front().iteration;
	}
	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}

