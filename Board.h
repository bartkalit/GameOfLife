#pragma
#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tile.h"
#include "Point.h"

class Board {
	typedef std::vector<Tile*> Tile_list;

private:
	Tile** board;
	sf::RenderWindow window;
	sf::Event event;
	sf::Sound sound;
	sf::SoundBuffer b_sound;
	Tile_list active_tiles;
	Tile_list tiles_to_change;
	Point mouse;
	int tile_size;
	int tiles_num;

public:
	
	Board(int width, int height, std::string title, int tile_size);

	void Start_game();
private:
	Point Find_tile(Point coordinates);
	void Event_handler();
	void Del_non_active();
	void Tile_handler();
	void Add_age();
	void Check_neighbours(Tile* current);
	void Check_board();
};

#endif
