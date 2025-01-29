#pragma once

#include <list>
#include "gameConfig.h"

class Steps
{
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step
public:
	static Steps loadSteps(const std::string& filename);				// Loads steps from a file and returns a Steps object
	void saveSteps(const std::string& filename);						// Saves the current steps to a file

	void addStep(size_t iteration, char step) {							// Adds a step to the list with a given iteration number and step character 
		steps.push_back({ iteration, step });
	}
	bool isNextStepOnIteration(size_t iteration) const {				// Return true if steps's list isn't empty and the iteration of the first value in the list is the same so we need to change action
		return !steps.empty() && steps.front().first == iteration;
	}
	char popStep() {													// Removes and returns the next step in the list  
		char step = steps.front().second;
		steps.pop_front();
		return step;
	}

	size_t frontIteration() { return steps.front().first; }				// Returns the iteration number of the first step in the list
	bool isStepEmpty() { return steps.empty(); }						// Checks if there are no remaining steps in the list 
};
