#pragma once

#include <list>
#include <string>
#include "gameConfig.h"
#include <iostream>		//for cout

class Results 
{
public:
	enum ResultValue { died, finished, noResult };

	struct ResultEntry {
		size_t iteration;
		ResultValue result;
	};

private:
	//std::list<std::pair<size_t, ResultValue>> results; // pair: iteration, result
	std::list<ResultEntry> results;
public:
	static Results loadResults(const std::string& filename);
	void saveResults(const std::string& filename) const;
	void addResult(size_t iteration, ResultValue result) {
		results.push_back({ iteration, result });
	}
	//std::pair<size_t, ResultValue> popResult() {
	ResultEntry popResult() {
		if (results.empty()) return { 0, Results::noResult };
		auto result = results.front();
		results.pop_front();
		return result;
	}
	bool isFinishedBy(size_t iteration) const {
		//return results.empty() || results.back().first <= iteration;
		return results.empty() || results.back().iteration <= iteration;
	}
	size_t getNextBombIteration() const;
};

/*
#pragma once

#include <list>
#include <string>
#include "gameConfig.h"
#include <iostream>		//for cout

class Results
{
public:
	enum ResultValue { died, finished, noResult };

	struct ResultEntry {
		size_t iteration;
		ResultValue result;
		size_t score;
	};

private:
	//std::list<std::pair<size_t, ResultValue>> results; // pair: iteration, result
	std::list<ResultEntry> results;
public:
	static Results loadResults(const std::string& filename);
	void saveResults(const std::string& filename) const;
	void addResult(size_t iteration, ResultValue result, size_t score) {
		results.push_back({ iteration, result, score });
	}
	//std::pair<size_t, ResultValue> popResult() {
	ResultEntry popResult() {
		if (results.empty()) return { 0, Results::noResult, 0 };
		auto result = results.front();
		results.pop_front();
		return result;
	}
	bool isFinishedBy(size_t iteration) const {
		//return results.empty() || results.back().first <= iteration;
		return results.empty() || results.back().iteration <= iteration;
	}
	size_t getNextBombIteration() const;
};

*/