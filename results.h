#pragma once

#include <list>
#include <string>
#include "gameConfig.h"

class Results 
{
public:
	enum ResultValue { died, finished, noResult };

	struct ResultEntry {
		size_t iteration;
		ResultValue result;

		bool operator!=(const ResultEntry& other) const {
			return (iteration != other.iteration || result != other.result);
		}
	};

private:
	std::list<ResultEntry> results;
public:
	static Results loadResults(const std::string& filename);
	void saveResults(const std::string& filename, int score);
	void addResult(size_t iteration, ResultValue result) {
		results.push_back({ iteration, result });
	}
	ResultEntry popResult() {
		if (results.empty()) return { 0, ResultValue::noResult };
		auto result = results.front();
		results.pop_front();
		return result;
	}

	ResultEntry myFront() { return results.front(); }
	bool isFinishedBy(size_t iteration) const {
		return results.empty() || results.back().iteration < iteration;
	}
	size_t getDiedNextIteration() const;
};