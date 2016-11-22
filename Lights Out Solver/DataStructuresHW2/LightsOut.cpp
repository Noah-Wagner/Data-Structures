#include "stdafx.h"
#include "LightsOut.h"
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

std::string LightsOut::SolveSequence(std::string str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	std::vector<int> gameGrid(str.length());
	for (int i = 0; i < str.length(); i++) {
		if (str[i] < '0' || str[i] > '9') {
			throw std::invalid_argument("Invalid sequence");
		}
		gameGrid[i] = str[i] - '0';
	}

	std::vector<int> push;
	std::vector<int> result = Solve(str, push, 0);

	if (result[0] == -1) {
		return "NO SOLUTION";
	}
	else {
		std::stringstream stream;
		std::copy(result.begin(), result.end(), std::ostream_iterator<int>(stream, " "));
		return stream.str();
	}
}

std::vector<int> LightsOut::Solve(std::string str, std::vector<int> prevPush, int push) {
	
	if (str.find("1") == std::string::npos) {
		return prevPush;
	}

	if (push >= str.length()) {
		prevPush.clear();
		prevPush.push_back(-1);
		return prevPush;
	}

	std::vector<int> temp = prevPush;
	temp.push_back(push + 1);
	std::vector<int> v1 = Solve(Push(str, push), temp, push + 1);
	if (v1[0] != -1) {
		return v1;
	}
	return Solve(str, prevPush, push + 1);
}

std::string LightsOut::Push(std::string str, const int& pos) {
	if (pos == 0) {
		str[pos] = (str[pos] == '1') ? '0' : '1';
		str[pos + 1] = (str[pos + 1] == '1') ? '0' : '1';
	}
	else if (pos == str.length() - 1) {
		str[pos] = (str[pos] == '1') ? '0' : '1';
		str[pos - 1] = (str[pos - 1] == '1') ? '0' : '1';
	}
	else {
		str[pos] = (str[pos] == '1') ? '0' : '1';
		str[pos - 1] = (str[pos - 1] == '1') ? '0' : '1';
		str[pos + 1] = (str[pos + 1] == '1') ? '0' : '1';
	}
	return str;
}
