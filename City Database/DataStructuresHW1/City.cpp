#include "stdafx.h"
#include "CityDatabase.h"
#include <string>
#include "City.h"

std::string name;
double x;
double y;

// Equality for classes is defined as when two cities share coordinates
bool City::operator== (const City &other) const {
	return CityDatabase::Distance(*this, other.x, other.y) < 0.1;
}

std::string City::ToString() {
	return name + " (" + std::to_string(x) + "," + std::to_string(y) + ")";
}