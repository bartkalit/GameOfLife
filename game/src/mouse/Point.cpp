#pragma
#include "Point.h"

Point::Point() 
	: x(-1), y(-1) {}

Point::Point(int x, int y) 
	: x(x), y(y) {}

void Point::Set_x(int x) {
	this->x = x;
}

void Point::Set_y(int y) {
	this->y = y;
}

int Point::Get_x() {
	return x;
}

int Point::Get_y() {
	return y;
}