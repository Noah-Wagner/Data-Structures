#pragma once

struct City {
	std::string name;
	double x;
	double y;

	// Equality for classes is defined as when two cities share coordinates
	bool City::operator== (const City &other) const;

	std::string ToString();

};