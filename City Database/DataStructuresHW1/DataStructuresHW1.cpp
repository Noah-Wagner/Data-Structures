// DataStructuresHW1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ListCityDatabase.h"
#include "ArrayCityDatabase.h"
#include <cassert>
#include <ctime>

int main()
{
	ArrayCityDatabase database1;
	ListCityDatabase database2;
	while (true) {
		std::cout << "*************************************:" <<
			"Implementation Options:\n" <<
			"A.Use an array-based list implementation\n" <<
			"B.Use a linked-list implementation\n\n" <<
			"Operation Options:\n" <<
			"1. Insert a record\n" <<
			"2. Search for a record by name\n" <<
			"3. Search for a record by coordinate\n" <<
			"4. Delete a record by name\n" <<
			"5. Delete a record by coordinate\n" <<
			"6. Print records within a given distance of a specified location\n" <<
			"7. Print all records\n" <<
			"8. Exit\n\n";

		std::cout << "Enter your implementation option: ";
		char implementation;
		int operation;
		std::cin >> implementation;
		std::cout << "Enter your operation option: ";
		std::cin >> operation;

		CityDatabase* db;
		

		if (implementation == 'A' || implementation == 'a') {
			db = &database1;
		}
		else {
			db = &database2;
		}

		switch (operation) {
		case 1: {
			std::string name;
			double x = 0.0;
			double y = 0.0;
			std::cout << "Enter name of the city: ";
			std::cin.ignore();
			std::getline(std::cin, name);
			std::cout << "Enter x coordinate of the city: ";
			std::cin >> x;
			std::cout << "Enter y coordinate of the city: ";
			std::cin >> y;
			if (db->Insert(name, x, y)) {
				std::cout << "Record inserted successfully.\n";
			}
			else {
				std::cout << "No need to insert again, as this record exists in the existing data set.\n";
			}
			break;
		}
		case 2: {
			std::string name;
			std::cout << "Enter name of the city to be searched: ";
			std::cin.ignore();
			std::getline(std::cin, name);
			City* city = db->Search(name);
			if (city != nullptr) {
				std::cout << "Output:\n" << city->ToString();
			}
			else {
				std::cout << "No such record exists in the existing data set.\n";
			}
			break;
		}
		case 3: {
			double x = 0;
			double y = 0;
			std::cout << "Enter x coordinate of the city to be searched: ";
			std::cin >> x;
			std::cout << "Enter y coordinate of the city to be searched: ";
			std::cin >> y;
			City* city = db->Search(x, y);
			if (city != nullptr) {
				std::cout << "Output:\n" << city->ToString();
			}
			else {
				std::cout << "No such record exists in the existing data set.\n";
			}
			break;
		}
		case 4: {
			std::string name;
			std::cout << "Enter name of the city to be deleted: ";
			std::cin.ignore();
			std::getline(std::cin, name);
			if (db->Delete(name)) {
				std::cout << "Deleted successfully";
			}
			else {
				std::cout << "No such record exists in the existing data set.\n";
			}
			break;
		}
		case 5: {
			double x = 0;
			double y = 0;
			std::cout << "Enter x coordinate of the city to be searched: ";
			std::cin >> x;
			std::cout << "Enter y coordinate of the city to be searched: ";
			std::cin >> y;
			if (db->Delete(x, y)) {
				std::cout << "Deleted successfully";
			}
			else {
				std::cout << "No such record exists in the existing data set.\n";
			}
			break;
		}
		case 6: {
			std::string name;
			double dist;
			std::cout << "Enter name of the specified location: ";
			std::cin.ignore();
			std::getline(std::cin, name);
			std::cout << "Enter distance: ";
			std::cin >> dist;
			db->Search(name, dist);
			break;
		}
		case 7: {
			db->PrintAll();
			break;
		}
		case 8: {
			return 0;
		}
		}

	}

	
	return -1;
}

