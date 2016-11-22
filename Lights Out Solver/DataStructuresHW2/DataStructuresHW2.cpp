
#include "stdafx.h"
#include "LightsOut.h"
#include <string>
#include <iostream>

int main()
{
	while (true) {
		int n;
		std::string sequence;
		std::cout << "Size of sequence: ";
		std::cin >> n;

		std::cout << "\nSequence: ";
		std::cin >> sequence;

		std::cout << "\n" << LightsOut::SolveSequence(sequence) << "\n";
	}

    return 0;
}

