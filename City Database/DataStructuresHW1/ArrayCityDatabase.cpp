#include "stdafx.h"
#include "CityDatabase.h"
#include "ArrayCityDatabase.h"
#include <functional>

const int ARRAY_COUNT = 20000;

City cities[ARRAY_COUNT];
int currentIndex = 0;

bool ArrayCityDatabase::Insert(std::string name, double x, double y)
{
	if (Search(x, y) == nullptr) {
		City city{
			name,
			x,
			y
		};
		cities[currentIndex] = city;
		++currentIndex;
		return true;
	}
	return false;
}

bool ArrayCityDatabase::Delete(std::string name)
{
	return Delete(FindIndex(name));
}

bool ArrayCityDatabase::Delete(double x, double y)
{
	return Delete(FindIndex(x, y));
}

bool ArrayCityDatabase::Delete(int index)
{
	if (index >= 0) {
		for (int i = index; i < currentIndex - 1; ++i) {
			cities[i] = cities[i + 1];
		}
		--currentIndex;
		return true;
	}
	return false;

}

City* ArrayCityDatabase::Search(std::string name)
{
	int index = FindIndex(name);
	return (index >= 0) ? &cities[index] : nullptr;
}

City* ArrayCityDatabase::Search(double x, double y)
{
	int index = FindIndex(x, y);
	return (index >= 0) ? &cities[index] : nullptr;
}

void ArrayCityDatabase::Search(std::string name, double dist)
{
	City* city = this->Search(name);
	for (int i = 0; i < currentIndex; ++i) {
		if (Distance(cities[i], city->x, city->y) <= dist) {
			std::cout << cities[i].ToString() << std::endl;
		}
	}
}

int ArrayCityDatabase::FindIndex(std::string name)
{
	return FindIndex([&name](City* city) { return name.compare((*city).name) == 0; });
}

int ArrayCityDatabase::FindIndex(double x, double y)
{
	return FindIndex([&x, &y](City* city) { return (*city).x == x && (*city).y == y;  });
}

int ArrayCityDatabase::FindIndex(std::function<bool(City*)> lambda)
{
	for (int i = 0; i <= currentIndex; i++) {
		if (lambda(&cities[i])) {
			return i;
		}
	}
	return -1;
}

void ArrayCityDatabase::PrintAll() {
	for (int i = 0; i < currentIndex; ++i) {
		std::cout << cities[i].ToString() << "\n";
	}
}
