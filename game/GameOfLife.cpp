#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "src/board/Board.h"
using namespace std;

int main()
{
    int x = 800;
    int y = 800;
    std::string title = "GameOfLife";
    Board board(x, y ,title, 10);
    board.Start_game();
    return 0;
}