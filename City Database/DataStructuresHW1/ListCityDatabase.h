#pragma once
#include "CityDatabase.h"
#include <functional>

struct Node {
	City data;
	Node* next;
};


class ListCityDatabase : public CityDatabase {
	// Inherited via CityDatabase
public:
	ListCityDatabase();
	virtual bool Insert(std::string name, double x, double y) override;
	virtual bool Delete(std::string name) override;
	virtual bool Delete(double x, double y) override;
	
	virtual City* Search(std::string name) override;
	virtual City* Search(double x, double y) override;
	virtual void Search(std::string name, double dist) override;

	virtual void PrintAll() override;
private:
	City* BaseSearch(std::function<bool(City*)> lambda);
	bool BaseDelete(std::function<bool(City*)> lambda);
};

