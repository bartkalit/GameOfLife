#pragma
#include "Board.h"

Board::Board(int width, int height, std::string title, int tile_size) 
    : window(sf::VideoMode(width, height), title), tile_size(tile_size), 
    tiles_num(window.getSize().x / tile_size), sound(){
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
    while (window.isOpen())
    {
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
            break;
        default:
            break;
        }
    }
}

void Board::Del_non_active() {
    std::vector<int> ids;
    int ba = active_tiles.size();
    for (int i = 0; i < active_tiles.size(); i++) {
        if (!active_tiles[i]->Is_active()) {
            ids.push_back(i);
        }
        else {
        }
    }
    if (ids.size() == active_tiles.size()) {
        active_tiles.clear();
    }
    else {
        for (int i = 0; i < ids.size(); i++) {
            std::cout << ids[i];
            active_tiles.erase(active_tiles.begin() + ids[i]);
        }
    }
    ids.clear();
    for (int y = 0; y < tiles_num; y++) {
        for (int x = 0; x < tiles_num; x++) {
            if (board[y][x].Is_active()) {
                std::cout << board[y][x].Get_pos().Get_x() << " , " << board[y][x].Get_pos().Get_y() << std::endl;
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

void Board::Check_board() {
    for (int i = 0; i < active_tiles.size(); i++) {
        Check_neighbours(active_tiles[i]);
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
    tiles_to_change.clear();
    for (int y = 0; y < tiles_num; y++) {
        for (int x = 0; x < tiles_num; x++) {
            if (board[y][x].Get_check_flag()) {
                board[y][x].Change_check_flag();
            }
        }
    }
}

void Board::Check_neighbours(Tile* current) {
    if (!current->Get_check_flag()) {
        std::cout << "checking (" << current->Get_pos().Get_x() << ", " << current->Get_pos().Get_y() << ")\n";
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