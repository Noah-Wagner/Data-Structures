#include "stdafx.h"
#include "CityDatabase.h"
#include <functional>
#include "ListCityDatabase.h"


Node* head;

ListCityDatabase::ListCityDatabase()
{
	head = nullptr;
}

bool ListCityDatabase::Insert(std::string name, double x, double y)
{
	if (Search(x, y) == nullptr) {
		City city = {
			name,
			x,
			y
		};
		Node *node = new Node{
			city,
			head,
		};
		head = node;
		return true;
	}
	return false;
}

bool ListCityDatabase::Delete(std::string name)
{
	return BaseDelete([&name](City* city) { return name.compare((*city).name) == 0; });
}

bool ListCityDatabase::Delete(double x, double y)
{
	return BaseDelete([&x, &y](City* city) { return (*city).x == x && (*city).y == y;  });
}

bool ListCityDatabase::BaseDelete(std::function<bool(City*)> lambda) 
{
	Node* ptr = head;
	if (ptr == nullptr) {
		return false;
	}
	if (lambda(&(*ptr).data)) {
		head = (*ptr).next;
		return true;
	}
	while ((*ptr).next != nullptr) {
		if (lambda(&(*(*ptr).next).data)) {
			(*ptr).next = (*(*ptr).next).next;
			return true;
		}
		ptr = (*ptr).next;
	}
	return false;
}

City* ListCityDatabase::Search(std::string name)
{
	return BaseSearch([&name](City* city) { return name.compare((*city).name) == 0; });
}

City* ListCityDatabase::Search(double x, double y)
{
	return BaseSearch([&x, &y](City* city) { return (*city).x == x && (*city).y == y;  });
}

City* ListCityDatabase::BaseSearch(std::function<bool (City*)> lambda) 
{
	Node* ptr = head;
	while (ptr != nullptr) {
		if (lambda(&(*ptr).data)) {
			return &(*ptr).data;
		}
		ptr = (*ptr).next;
	}
	return nullptr;
}

void ListCityDatabase::Search(std::string name, double dist)
{
	City* city = this->Search(name);
	if (city != nullptr) {
		Node* ptr = head;
		while (ptr != nullptr) {
			if (Distance((*ptr).data, city->x, city->y) <= dist) {
				std::cout << (*ptr).data.ToString() << "\n";
			}
			ptr = (*ptr).next;
		}
	}
}

void ListCityDatabase::PrintAll() {
	Node* ptr = head;
	while (ptr != nullptr) {
		std::cout << ptr->data.ToString() << "\n";
		ptr = (*ptr).next;
	}
}

