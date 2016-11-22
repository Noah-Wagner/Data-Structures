#pragma once
#include "stdafx.h"
#include <vector>



class CityDatabase {
public:
	virtual bool Insert(std::string name, double x, double y) = 0;
	virtual bool Delete(std::string name) = 0;
	virtual bool Delete(double x, double y) = 0;

	virtual City* Search(std::string name) = 0;
	virtual City* Search(double x, double y) = 0;

	virtual void Search(std::string name, double dist) = 0;

	virtual void PrintAll() = 0;

//protected:
	static double Distance(City city, double x, double y);
	static double Distance(double, double, double, double);
};


