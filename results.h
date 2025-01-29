#pragma once

#include <list>
#include <string>
#include "gameConfig.h"

class Results 
{
public:
	enum ResultValue { died, finished, noResult };  // Enum representing possible results of an iteration

	struct ResultEntry {							// Structure to store an individual result entry 
		size_t iteration;
		ResultValue result;

		bool operator!=(const ResultEntry& other) const {	// Operator to compare two ResultEntry objects
			return (iteration != other.iteration || result != other.result);
		}
	};

private:
	std::list<ResultEntry> results;									// List storing all results
public:
	static Results loadResults(const std::string& filename);		// Loads results from a file and returns a Results object
	void saveResults(const std::string& filename, int score);		// Saves the current results to a file, including the player's score
	void addResult(size_t iteration, ResultValue result) {			// Adds a new result to the list with a given iteration number and result type
		results.push_back({ iteration, result });
	}	
	ResultEntry myFront() { return results.front(); }				// Retrieves the first result without removing it
	ResultEntry popResult() {										// Retrieves and removes the first result from the list 
		if (results.empty()) return { 0, ResultValue::noResult };
		auto result = results.front();
		results.pop_front();
		return result;
	}
	bool isFinishedBy(size_t iteration) const {						// Checks if all results occurred before a given iteration
		return results.empty() || results.back().iteration < iteration;
	}
	size_t getDiedNextIteration() const;							// Retrieves the iteration number when the next "died" event occurs (to be implemented)
};