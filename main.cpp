#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Board.h"
using namespace std;

int main()
{
    int x = 800;
    int y = 800;
    std::string title = "GameOfLife";
    /*cout << "Width should measure ";
    cin>> x;
    cout << "Height should measure ";
    cin >> y;
    cout << "The name should be ";
    cin >> title;*/
    Board board(x, y ,title, 10);
    board.Start_game();
    return 0;
}