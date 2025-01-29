#pragma once

#include <list>
#include "gameConfig.h"

class Steps
{
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step
public:
	static Steps loadSteps(const std::string& filename);
	void saveSteps(const std::string& filename);

	void addStep(size_t iteration, char step) {
		steps.push_back({ iteration, step });
	}
	bool isNextStepOnIteration(size_t iteration) const {				// Return true if steps's list isn't empty and the iteration of the first value in the list is the same so we need to change action
		return !steps.empty() && steps.front().first == iteration;
	}
	char popStep(/*size_t iteration*/) {
		char step = steps.front().second;
		steps.pop_front();
		return step;
	}

	size_t frontIteration() { return steps.front().first; }
	bool isStepEmpty() { return steps.empty(); }
};
