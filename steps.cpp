#include <fstream>

#include "Steps.h"

Steps Steps::loadSteps(const std::string& filename) {
	Steps steps;
	long _random_seed = 0;

	std::ifstream steps_file(filename);
	steps_file >> _random_seed;
	GameConfig::setRandomSeed(_random_seed);
	size_t size;
	steps_file >> size;
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		char step;
		steps_file >> iteration >> step;
		steps.addStep(iteration, step);
	}
	steps_file.close();
	return steps;
}

void Steps::saveSteps(const std::string& filename) {
	std::ofstream steps_file(filename);
	steps_file << GameConfig::getRandomSeed() << '\n' << steps.size();		// First row of the file will be the random seed
	for (const auto& step : steps) {
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
	steps.clear();
}
