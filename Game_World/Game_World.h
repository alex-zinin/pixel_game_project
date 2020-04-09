#pragma once

#include "../Entities/Entities.h"
#include<iostream>
#include <vector>
#include<future>
#include <SFML/Graphics.hpp>
#include<memory>

const int GAME_WORLD_SIZE = 3000;
const int MAX_TIME = 100000;
class Game_World{
public:
    Game_World(int x_size, int y_size);
    int Add_Entity(Entity entity);
    std::vector<std::shared_ptr<Entity>>& Get_Entities();
    Player& Get_Player();
    Player& Get_Second_Player();
    int Get_Time();
    int Increment_Time();

public:
   // std::vector<std::shared_ptr<Entity>> entities;
    int world_x_size;
    int world_y_size;
    sf::RectangleShape world;

private:
    std::vector<std::shared_ptr<Entity>> entities;
    Player player;
    Player player2;
    int time;


};
