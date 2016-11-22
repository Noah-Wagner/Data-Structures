#include "stdafx.h"
#include "CityDatabase.h"

City city;

const double EQUATOR_DIST = 3963.191;


double deg_to_rad(double deg)
{
	return deg * (3.1415926535 / 180.0);
}

double CityDatabase::Distance(City city, double x, double y)
{
	return Distance(city.x, city.y, x, y);
}

double CityDatabase::Distance(double x1, double y1 , double x2, double y2) {
	x1 = deg_to_rad(x1);
	x2 = deg_to_rad(x2);
	y1 = deg_to_rad(y1);
	y2 = deg_to_rad(y2);
	return EQUATOR_DIST * acos(sin(y1)*sin(y2) + cos(y1)*cos(y2)*cos(x2 - x1));
}

