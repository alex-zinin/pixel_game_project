#pragma once

#include"../Game_World/Game_World.h"
#include"../Entities/Entities.h"
#include<iostream>
#include"../Drawer/Drawer.h"
#include"../vector2/vector2.h"
#include<memory>

using namespace std;



void Entity_Shoot(Game_World& game_world, Entity& fire_shooter, const Vector2& speed);
void Fire_Shooter_Entity_Shoot(Game_World& game_world, Entity& fire_shooter, const Vector2& speed);
int Make_Entity_Action(Game_World& game_world, Entity& entity);

class Entity_Handler {
public:
    sf::RenderWindow &window;
    Game_World &game_world;
    Drawer &drawer;

public:

    Entity_Handler(Game_World& gm, Drawer &dr, sf::RenderWindow& wind): window(wind), game_world(gm), drawer(dr) {}
    Direction GetReverseDirection(Direction dir);
    Direction Take_Controll_Button_Direction();
    int Get_Mouse_Action();
    void World_Process();
};

