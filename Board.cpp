#pragma
#include "Board.h"

Board::Board(int width, int height, std::string title, int tile_size)
    : window(sf::VideoMode(width, height), title), tile_size(tile_size), 
    tiles_num(window.getSize().x / tile_size), stop(false), speed(5) {
    b_sound.loadFromFile("./resources/bloop.wav");
    sound.setBuffer(b_sound);

    board = new Tile * [tiles_num];
    for (int y = 0; y < tiles_num; y++) {
        board[y] = new Tile[tiles_num];
        for (int x = 0; x < tiles_num; x++) {
            Tile tile(x * tile_size, y * tile_size, tile_size);
            board[y][x] = tile;
        }
    }
}

void Board::Start_game(){
    int counter = 0;
    while (window.isOpen())
    {
        if (stop) {
            counter++;
            if (counter >= speed * 1) {
                Check_board();
                Del_non_active();
                counter = 0;
            }
        }
        Event_handler();
        window.clear(sf::Color::White);
        for (int y = 0; y < tiles_num; y++) {
            for (int x = 0; x < tiles_num; x++) {
                window.draw(board[y][x].Get_tile());
            }
        }
        window.display();
    }
}

Point Board::Find_tile(Point coordinates) {
    int x = coordinates.Get_x() / tile_size;
    int y = coordinates.Get_y() / tile_size;
    return Point(x, y);
}

void Board::Event_handler() {
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                mouse.Set_x(int(event.mouseButton.x));
                mouse.Set_y(int(event.mouseButton.y));
                Tile_handler();
            }
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Enter) {
                Check_board();
                Del_non_active();
            }
            else if (event.key.code == sf::Keyboard::S) {
                stop = !stop;
            }
            else if (event.key.code == sf::Keyboard::O) {
                if (speed < 10) {
                    speed++;
                }
            }
            else if (event.key.code == sf::Keyboard::P) {
                if (speed > 1) {
                    speed--;
                }
            }
            break;
        default:
            break;
        }
    }
}

void Board::Del_non_active() {
    active_tiles.clear();
    for (int y = 0; y < tiles_num; y++) {
        for (int x = 0; x < tiles_num; x++) {
            if (board[y][x].Is_active()) {
                active_tiles.push_back(&board[y][x]);
            }
        }
    }
}

void Board::Tile_handler() {
    Point ids = Find_tile(mouse);
    Tile* buffor = &board[ids.Get_y()][ids.Get_x()];
    if (!buffor->Is_active()) {
        sound.play();
        buffor->Live();
        active_tiles.push_back(buffor);
    }
    else {
        buffor->Die();
    }
}

bool Board::Pos_in_range(Point pos) {
    if (pos.Get_x() >= 0 && pos.Get_x() < tiles_num) {
        if (pos.Get_y() >= 0 && pos.Get_y() < tiles_num) {
            return true;
        }
    }
    return false;
}

void Board::Check_board() {
    for (int i = 0; i < active_tiles.size(); i++) {
        Check_neighbours(active_tiles[i]);
        tiles_to_check.push_back(active_tiles[i]);
    }

    for (int i = 0; i < tiles_to_change.size(); i++) {
        if (tiles_to_change[i]->Is_active()) {
            tiles_to_change[i]->Die();
        }
        else {
            tiles_to_change[i]->Live();
            active_tiles.push_back(tiles_to_change[i]);
        }
        tiles_to_change[i]->Change_check_flag();
    }

    for (int i = 0; i < tiles_to_check.size(); i++) {
        if (tiles_to_check[i]->Get_check_flag()) {
            tiles_to_check[i]->Change_check_flag();
        }
    }
    tiles_to_check.clear();
    tiles_to_change.clear();
}

void Board::Check_neighbours(Tile* current) {
    if (!current->Get_check_flag()) {

        //current->Change_color(Colors::Black);
        //current->Change_check_flag();

        int alive_neigh = 0;
        Point coords;
        coords.Set_x(current->Get_pos().Get_x() + tile_size / 2);
        coords.Set_y(current->Get_pos().Get_y() + tile_size / 2);
        Point id = Find_tile(coords);
        current->Change_check_flag();
        for (int y = -1; y < 2; y++) {
            for (int x = -1; x < 2; x++) {
                if (!(!x && !y)) {
                    int new_x = id.Get_x() + x;
                    int new_y = id.Get_y() + y;
                    if (new_x >= 0 && new_x < tiles_num) {
                        if (new_y >= 0 && new_y < tiles_num) {
                            if (current->Is_active() && !board[new_y][new_x].Is_active()) {
                                
                                tiles_to_check.push_back(&board[new_y][new_x]);
                                Check_neighbours(&board[new_y][new_x]);
                            }
                            if(board[new_y][new_x].Is_active()){
                                alive_neigh++;
                            }
                        }
                    }
                }
            }
        }
        if (current->Is_active() && (alive_neigh < 2 || alive_neigh > 3)) {
            tiles_to_change.push_back(current);
        }
        else if (!current->Is_active() && alive_neigh == 3){
            tiles_to_change.push_back(current);
        }
    }
}

void Board::recolor() {
    for (int y = 0; y < tiles_num; y++) {
        for (int x = 0; x < tiles_num; x++) {
            if (board[y][x].Is_active()) {
                board[y][x].Change_color(Colors::Black);
                active_tiles.size();
            }
        }
    }
}