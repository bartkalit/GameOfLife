#pragma once
#ifndef POINT_H
#define POINT_H

class Point {

private:
	int x;
	int y;

public:
	Point();
	Point(int x, int y);

	void Set_x(int x);
	void Set_y(int y);

	int Get_x();
	int Get_y();
};

#endif
