#pragma once
#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Point.h"

enum Colors {
	White = 0,
	Black,
	Blue,
};

class Tile {
private:
	Point pos;
	int tile_size;
	int age;
	bool active;
	bool check_flag;
	sf::RectangleShape tile;

public:
	Tile();
	Tile(int x, int y, int tile_size);

	void Live();
	void Die();
	void Change_check_flag();
	void Add_age();

	Point Get_pos();
	int Get_age();
	bool Is_active();
	bool Get_check_flag();
	sf::RectangleShape Get_tile();

private:
	void Set_rectangle();
	void Change_color(Colors color);
};
#endif