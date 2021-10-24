#pragma once
#include "Tile.h"

Tile::Tile() 
	: tile_size(10), active(false), age(0), check_flag(false){}

Tile::Tile(int x, int y, int tile_size) : 
	pos(Point(x, y)), tile_size(tile_size), active(false), age(0), check_flag(false){
	Set_rectangle();
}

void Tile::Live() {
	active = true;
	Change_color(Colors::Blue);
	age++;
}

void Tile::Die() {
	active = false;
	age = 0;
	Change_color(Colors::White);
}

void Tile::Change_check_flag() {
	check_flag = !check_flag;
}

void Tile::Add_age() {
	age++;
}

sf::RectangleShape Tile::Get_tile() {
	return tile;
}

Point Tile::Get_pos() {
	return pos;
}

int Tile::Get_age() {
	return age;
}

bool Tile::Is_active() {
	return active;
}

bool Tile::Get_check_flag() {
	return check_flag;
}

void Tile::Set_rectangle() {
	tile.setSize(sf::Vector2f(tile_size, tile_size));
	tile.setFillColor(sf::Color(255, 255, 255));
	tile.setPosition(pos.Get_x(), pos.Get_y());
}

void Tile::Change_color(Colors color) {
	int shade = age * 20;
	switch (color)
	{
	case White:
		tile.setFillColor(sf::Color(255, 255, 255));
		break;
	case Black:
		tile.setFillColor(sf::Color(0, 0, 0));
		break;
	case Blue:
		tile.setFillColor(sf::Color(shade, 0, 255 - shade));
		break;
	default:
		break;
	}
}
