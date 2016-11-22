#pragma once
#include "stdafx.h"
#include "CityDatabase.h"
#include <functional>

class ArrayCityDatabase : public CityDatabase {
	// Inherited via CityDatabase
public:
	virtual bool Insert(std::string name, double x, double y) override;
	virtual bool Delete(std::string name) override;
	virtual bool Delete(double x, double y) override;
	virtual City* Search(std::string name) override;
	virtual City* Search(double x, double y) override;
	virtual void Search(std::string name, double dist) override;
	virtual void PrintAll() override;
private:
	bool Delete(int);
	int FindIndex(std::string name);
	int FindIndex(double x, double y);
	int FindIndex(std::function<bool(City*)> lambda);
};

