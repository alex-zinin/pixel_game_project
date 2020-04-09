#pragma once

#include<SFML/Window.hpp>
#include<iostream>
#include <SFML/System/Vector2.hpp>
#include"../vector2/vector2.h"
#include <SFML/Graphics.hpp>




const int WALL_HEALTH = 200000;
const int HOSPITAL_HOUSE_HEALTH = 10000;
const int HOSPITAL_MEDICATION = 100;
const int PLAYER_HEALTH = 100;
const int BON_FIRE_HEALTH = 10011;
const int FIRE_SHOOTER_HEALTH = 40;
const int FIREBALL_HEALTH = 10;
const int FIREBALL_DAMAGE = 5;
const int ZOMBIE_HEALTH = 10000;
const int ZOMBIE_DAMAGE = 10;

const int WITCH_HEALTH = 1000;
const int WITCH_DAMAGE = 1000;
const int MAGIC_DAMAGE = 5;
const int MAGIC_HEALTH = 10000;


enum class Entity_Type{
    PLAYER,
    WALL,
    WOLF,
    BON_FIRE,
    WITCH,
    KIT,
    FIREBALL,
    FIRE_SHOOTER,
    HOSPITAL_HOUSE,
    ZOMBIE,
    MAGIC,
};


Entity_Type From_String_To_Entity_Type(const std::string& type);
std::string From_Entity_Type_To_String(Entity_Type entity_type);

enum class Direction{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NODIRECTION,
};

enum class Type_Of_Animation{
    STATIC,
    NONSTATIC,
};

enum class Type_Of_Moving{
    STATIC,
    NONSTATIC,
};

enum class Texture_Orientation{
    LEFT,
    RIGHT,
};


class Entity{
public:
    static const int SIZE_ENT_X = 100, SIZE_ENT_Y = 100;
    Type_Of_Animation type_of_animation;
    Type_Of_Moving type_of_moving;
    bool has_collisions = true;
    int pos_x, pos_y;
    int abs_pos_x, abs_pos_y;
    int size_x, size_y;
    int health;
    int max_health;
    int damage;
    int entity_speed;
    Vector2 vector_speed;
    sf::RectangleShape sprite;
    int num_of_texture, max_num_of_texture;
    Entity_Type entity_type;

public:
    Entity(int x, int y, int health0, Type_Of_Animation type_an, Type_Of_Moving type_mv);
    std::string From_Entity_To_String() const;
    void Set_Pos(int x, int y);
    void Set_Speed(const Vector2 &speed);
    void move_entity(Direction dir, int speed = 0);
    void move_entity();
    int Get_Damage_From_Entity(const Entity& entity);
    int Process_Collision(const Entity& entity);
    virtual void Set_Entity_Direction(const Entity& entity);
    void move_entity(Vector2 speed);
    bool Has_Collised(const Entity& rhs)const;
    int Set_Sprite_Position(int x, int y);
    Vector2 Get_Position() const;
    Vector2 Get_Position_On_Screen() const;


};



class Wall: public Entity{
public:
    static const int MAX_NUM_OF_TEXTURE = 1;

public:
    Wall(int x, int y);


};


class Hospital_House: public Entity{
public:
    static const int MAX_NUM_OF_TEXTURE = 1;

public:
    Hospital_House(int x, int y);

};

class Player: public Entity {
public:
    static const int MAX_NUM_OF_TEXTURE = 16;

public:
     Player(int x, int y);
     Player(int x, int y, int hlth);
     int Get_Medication();


};


class Bon_Fire: public Entity{
public:
    static const int MAX_NUM_OF_TEXTURE = 3;

public:

    Bon_Fire(int x, int y);


};



class Fire_Shooter: public Entity{
public:
    static const int MAX_NUM_OF_TEXTURE = 89;

public:

    Fire_Shooter(int x, int y);





};

class Fireball: public Entity{
public:
    static const int MAX_NUM_OF_TEXTURE = 3;

public:

    Fireball(int x, int y, int speed_x, int speed_y);


};

class Magic: public Entity{
public:
    static const int MAX_NUM_OF_TEXTURE = 3;

public:

    Magic(int x, int y, int speed_x, int speed_y);


};

class Zombie: public Entity{
public:
    static const int MAX_NUM_OF_TEXTURE = 89;

public:
    Zombie(int x, int y, int speed_x, int speed_y);
    void Set_Entity_Direction(const Entity& entity) override;
};



class Witch: public Entity{
public:
    static const int MAX_NUM_OF_TEXTURE = 89;

public:
    Witch(int x, int y, int speed_x, int speed_y);
    void Set_Entity_Direction(const Entity& entity) override;
};

std::ostream& operator<<(std::ostream &os, const Wall& wall);
std::ostream& operator<<(std::ostream &os, const Fireball& f);
std::ostream& operator<<(std::ostream &os, const Player& p);
std::ostream& operator<<(std::ostream &os, const Fire_Shooter& f);
std::ostream& operator<<(std::ostream &os, const Entity& f);





