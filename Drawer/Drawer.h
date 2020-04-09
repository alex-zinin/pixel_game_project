#pragma once

#include"../Game_World/Game_World.h"
#include<map>
#include"../Entities/Entities.h"
#include<memory>
#include<iostream>
#include<string>
#include<SFML/Window.hpp>
#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<pthread.h>
#include<thread>


const int SCREEN_X_SIZE = 2000, SCREEN_Y_SIZE = 900;
const int TABLE_X_SIZE = SCREEN_X_SIZE/2, TABLE_Y_SIZE = 200;
const int MAX_NUM_OF_HEARTS = 10;

class Screen{
public:
    int pos_x, pos_y;
    int size_x, size_y;

public:
    Screen(int x, int y);
    void move(int x, int y);
    void Set_Pos(int x, int y);


};


class Info_Table{
public:
    sf::RenderWindow &window;
    Game_World &game_world;
    sf::RectangleShape table;
    sf::Texture info_table_texture;
    sf::Texture heart_texture;
    std::vector<sf::RectangleShape> hearts;
    int x_size, y_size;
    sf::Text text;
    sf::Font font;//шрифт


public:
    Info_Table(int size_x, int size_y, sf::RenderWindow &wind, Game_World &gm);
    void Show_Table();
};


class Drawer{
public:

    class Mini_Map{
    public:
        sf::RectangleShape map;
        int size_x, size_y;
        int pos_x, pos_y;
        Game_World& game_world;
        Drawer& drawer;
        double relative_map_to_world;
        sf::Texture map_texture;

    public:
        Mini_Map(int size, Game_World& gm, int x_pos, int y_pos, Drawer& dr);
        void Draw_Map();

    };

public:
    Drawer(sf::RenderWindow& wind, Game_World& gm);
    void Draw_Health(sf::RenderWindow& window, const Entity& entity);
    void Show_Player_Table();
    void Draw_World();
    void Move_Screen_To_Player();


public:
    Game_World &game_world;
    Info_Table info_table;
    Screen screen;
    sf::RenderWindow &window;
    std::map<Entity_Type, sf::Texture> static_textures;
    std::map<Entity_Type, std::vector<sf::Texture>> animation_texture;
    std::map<Entity_Type, std::vector<sf::Texture>> reversed_animation_texture;
    sf::Texture game_world_texture;
    Mini_Map mini_map;
    sf::Texture heart_texture;
    int heart_size = 10;
    std::vector<sf::RectangleShape> hearts;

};
