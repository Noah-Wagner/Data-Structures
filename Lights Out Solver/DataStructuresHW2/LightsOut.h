#pragma once
#include <string>
#include <vector>

class LightsOut {
public:
	static std::string SolveSequence(std::string);
private:
	static std::vector<int> Solve(std::string, std::vector<int>, int);
	static std::string Push(std::string, const int&);
};