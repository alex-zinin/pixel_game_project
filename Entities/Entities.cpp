#include"Entities.h"


std::ostream& operator<<(std::ostream &os, const Wall& wall){
    os << "Wall: " << "pos_x = " << wall.abs_pos_x << "pos_y = " << wall.abs_pos_y;
    return os;
}


std::ostream& operator<<(std::ostream &os, const Fireball& f){
    os << "Fireball: " << "speed_x= " << f.vector_speed.x << " speed_y= " << f.vector_speed.y <<
       " pos_x = " << f.abs_pos_x << " pos_y = " << f.abs_pos_y;
    return os;
}


std::ostream& operator<<(std::ostream &os, const Player& p){
    os << "Player: " << "pos_x = " << p.abs_pos_x << "pos_y = " << p.abs_pos_y;
    return os;
}

std::ostream& operator<<(std::ostream &os, const Fire_Shooter& f){
    os << "Fire_Shooter: " << "pos_x = " << f.abs_pos_x << "pos_y = " << f.abs_pos_y;
    return os;
}

std::ostream& operator<<(std::ostream &os, const Entity& f){
    os << "Entity: " << "speed_x= " << f.vector_speed.x << " speed_y= " << f.vector_speed.y <<
       " pos_x = " << f.abs_pos_x << " pos_y = " << f.abs_pos_y;
    return os;
}


void Entity::Set_Entity_Direction(const Entity& entity){
        return;
}

Entity::Entity(int x, int y, int health0, Type_Of_Animation type_an, Type_Of_Moving type_mv): sprite(), type_of_animation(type_an), type_of_moving(type_mv)
{
    int size_ent_x = SIZE_ENT_X, size_ent_y = SIZE_ENT_Y;
    sprite.setPosition(x, y);
    entity_speed = 0;
    vector_speed = {0,0};
    sprite.setSize(sf::Vector2f(size_ent_x,size_ent_y));
    // sprite.setScale(4, 4);
    size_x = size_ent_x;
    size_y = size_ent_y;
    abs_pos_x = x;
    abs_pos_y = y;
    num_of_texture = 0;
    max_num_of_texture = 0;
    pos_x = x;
    pos_y = y;
    max_health = health0;
    health = health0;
    damage = 0;
}



std::string Entity::From_Entity_To_String() const {
    std::string result;
    result += "TYPE=";
    result += From_Entity_Type_To_String(this->entity_type);
    result += ':';
    result += "speed={";
    result += std::to_string(this->vector_speed.x);
    result += ',';
    result += std::to_string(this->vector_speed.y);
    result += "};";
    result += "absx=";
    result += std::to_string(this->abs_pos_x);
    result += ",absy=";
    result += std::to_string(this->abs_pos_y);
    result += ',';
    result += std::to_string(health);
    result += "&&";
    return result;
}


void Entity::Set_Pos(int x, int y)
{
    pos_x = x;
    pos_y = y;
    sprite.setPosition(x, y);
}


void Entity::Set_Speed(const Vector2 &speed){
    vector_speed = speed;
}


Vector2 Entity::Get_Position() const{
    return {(double) abs_pos_x, (double) abs_pos_y};
}


Vector2 Entity::Get_Position_On_Screen() const{
    return {(double) pos_x, (double) pos_y};
}


void Entity::move_entity(Direction dir, int speed)
{
    if(speed == 0)
        speed = entity_speed;
    int x = pos_x, y = pos_y;
    switch(dir)
    {
        case Direction::RIGHT: {pos_x += speed; abs_pos_x += speed; vector_speed.x = 1;} break;
        case Direction::LEFT: {pos_x -= speed;  abs_pos_x -= speed; vector_speed.x = -1;} break;
        case Direction::UP: {pos_y -= speed;  abs_pos_y -= speed;} break;
        case Direction::DOWN: {pos_y += speed; abs_pos_y += speed;} break;
        case Direction ::NODIRECTION: break;
    }

    sprite.setPosition(pos_x, pos_y);
}


void Entity::move_entity(){
    abs_pos_x += (int) vector_speed.x;
    abs_pos_y += (int) vector_speed.y;
    pos_x += (int) vector_speed.x;
    pos_y += (int) vector_speed.y;
    sprite.setPosition(pos_x, pos_y);

}

void Entity::move_entity(Vector2 speed){
    abs_pos_x += (int) speed.x;
    abs_pos_y += (int) speed.y;
    pos_x += (int) speed.x;
    pos_y += (int) speed.y;
    sprite.setPosition(pos_x, pos_y);

}

bool Entity::Has_Collised(const Entity& rhs)const {
    if(this->abs_pos_x + this->size_x >= rhs.abs_pos_x && this->abs_pos_x  <= rhs.abs_pos_x &&
       this->abs_pos_y+this->size_y >= rhs.abs_pos_y && this->abs_pos_y <= rhs.abs_pos_y ||
       this->abs_pos_x + this->size_x >= rhs.abs_pos_x+rhs.size_x && this->abs_pos_x  <= rhs.abs_pos_x+rhs.size_x &&
       this->abs_pos_y+this->size_y >= rhs.abs_pos_y && this->abs_pos_y <= rhs.abs_pos_y ||
       this->abs_pos_x + this->size_x >= rhs.abs_pos_x+rhs.size_x && this->abs_pos_x  <= rhs.abs_pos_x+rhs.size_x &&
       this->abs_pos_y+this->size_y >= rhs.abs_pos_y + rhs.size_y && this->abs_pos_y <= rhs.abs_pos_y + rhs.size_y ||
       this->abs_pos_x + this->size_x >= rhs.abs_pos_x && this->abs_pos_x  <= rhs.abs_pos_x &&
       this->abs_pos_y+this->size_y >= rhs.abs_pos_y + rhs.size_y && this->abs_pos_y <= rhs.abs_pos_y + rhs.size_y
       )
        return true;
    else
        return false;
}


int Entity::Set_Sprite_Position(int x, int y){
    sprite.setPosition(x, y);

    return 0;
}


int Entity::Get_Damage_From_Entity(const Entity& entity){
    health -= entity.damage;
    return 0;
}

int Entity::Process_Collision(const Entity& entity){
    move_entity(Vector2((this->abs_pos_x-entity.abs_pos_x)/15, (this->abs_pos_y-entity.abs_pos_y)/15));
    return 0;

}

Entity_Type From_String_To_Entity_Type(const std::string& type){
    if(type == "WALL")
        return Entity_Type::WALL;
    if(type == "PLAYER")
        return Entity_Type::PLAYER;
    if(type == "WOLF")
        return Entity_Type::WOLF;
    if(type == "BON_FIRE")
        return Entity_Type::BON_FIRE;
    if(type == "FIREBALL")
        return Entity_Type::FIREBALL;
    if(type == "FIRE_SHOOTER")
        return Entity_Type::FIRE_SHOOTER;


}


std::string From_Entity_Type_To_String(Entity_Type entity_type){
    if(entity_type ==Entity_Type::WALL)
        return "WALL";
    if(entity_type ==Entity_Type::PLAYER)
        return "PLAYER";
    if(entity_type ==Entity_Type::WOLF)
        return "WOLF";
    if(entity_type ==Entity_Type::BON_FIRE)
        return "BON_FIRE";
    if(entity_type ==Entity_Type::FIREBALL)
        return "FIREBALL";
    if(entity_type ==Entity_Type::FIRE_SHOOTER)
        return "FIRE_SHOOTER";
    else
        return "WALL";
}



Wall::Wall(int x, int y): Entity(x, y, 10000000, Type_Of_Animation::STATIC, Type_Of_Moving::STATIC) {
    this->has_collisions = true;
    entity_type = Entity_Type::WALL;
}


Hospital_House::Hospital_House(int x, int y): Entity(x, y, HOSPITAL_HOUSE_HEALTH, Type_Of_Animation::STATIC, Type_Of_Moving::STATIC)
{
    entity_speed = 5;
    max_num_of_texture = 1;
    entity_type = Entity_Type::HOSPITAL_HOUSE;
    size_x = 200;
    size_y = 200;
    sprite.setSize(sf::Vector2f(size_x,size_y));
}


Player::Player(int x, int y): Entity(x, y, PLAYER_HEALTH, Type_Of_Animation::NONSTATIC, Type_Of_Moving::NONSTATIC)
{
    sprite.setSize(sf::Vector2f(SIZE_ENT_X + 50,SIZE_ENT_Y));
    entity_speed = 5;
    max_num_of_texture = 16;
    entity_type = Entity_Type::PLAYER;
}

Player::Player(int x, int y, int hlth): Entity(x, y, PLAYER_HEALTH, Type_Of_Animation::NONSTATIC, Type_Of_Moving::NONSTATIC)
{
    entity_speed = 5;
    max_num_of_texture = 16;
    health = hlth;
    entity_type = Entity_Type::PLAYER;
}

int Player::Get_Medication(){
    health += HOSPITAL_MEDICATION;
    if(health >= max_health)
        health = max_health;
}


Bon_Fire::Bon_Fire(int x, int y): Entity(x, y, BON_FIRE_HEALTH, Type_Of_Animation::NONSTATIC, Type_Of_Moving::STATIC) {
    this->has_collisions = true;
    max_num_of_texture = 3;
    entity_type = Entity_Type::BON_FIRE;
    damage = 10;
}


Fire_Shooter::Fire_Shooter(int x, int y): Entity(x, y, 100, Type_Of_Animation::NONSTATIC, Type_Of_Moving::NONSTATIC){
    this->has_collisions = true;
    max_num_of_texture = 89;
    entity_type = Entity_Type::FIRE_SHOOTER;
    damage = 10;
}

Fireball::Fireball(int x, int y, int speed_x, int speed_y): Entity(x, y, FIREBALL_HEALTH, Type_Of_Animation::NONSTATIC, Type_Of_Moving::STATIC){
    this->has_collisions = true;
    vector_speed = Vector2(speed_x, speed_y);
    max_num_of_texture = 3;
    entity_type = Entity_Type::FIREBALL;
    damage = FIREBALL_DAMAGE;
    entity_speed = 2;
}


Magic::Magic(int x, int y, int speed_x, int speed_y): Entity(x, y, MAGIC_HEALTH, Type_Of_Animation::NONSTATIC, Type_Of_Moving::STATIC){
    this->has_collisions = true;
    vector_speed = Vector2(speed_x, speed_y);
    max_num_of_texture = 3;
    entity_type = Entity_Type::MAGIC;
    damage = FIREBALL_DAMAGE;
    entity_speed = 2;
}



Zombie::Zombie(int x, int y, int speed_x, int speed_y): Entity(x, y, ZOMBIE_HEALTH, Type_Of_Animation::NONSTATIC, Type_Of_Moving::NONSTATIC){
    this->has_collisions = true;
    vector_speed = Vector2(speed_x, speed_y);
    max_num_of_texture = 89;
    entity_type = Entity_Type::ZOMBIE;
    damage = ZOMBIE_DAMAGE;
    entity_speed = 2;
}

void Zombie::Set_Entity_Direction(const Entity& entity){
    Vector2 vect_speed(entity.abs_pos_x - abs_pos_x,
                       entity.abs_pos_y - abs_pos_y);
    vect_speed.Norm();
    Set_Speed(vect_speed*entity_speed);
}


Witch::Witch(int x, int y, int speed_x, int speed_y): Entity(x, y, WITCH_HEALTH, Type_Of_Animation::NONSTATIC, Type_Of_Moving::NONSTATIC){
    this->has_collisions = true;
    vector_speed = Vector2(speed_x, speed_y);
    max_num_of_texture = 89;
    entity_type = Entity_Type::WITCH;
    damage = WITCH_DAMAGE;
    entity_speed = 2;
}

void Witch::Set_Entity_Direction(const Entity& entity){
    int distance_to_entity = 500;

    Vector2 vector_to_enitity(entity.abs_pos_x - abs_pos_x,
                              entity.abs_pos_y - abs_pos_y);
    Vector2 vector_distance(vector_to_enitity);
    vector_distance = vector_distance*(-1);
    vector_distance.Norm();
    vector_distance = distance_to_entity*vector_distance;
    vector_to_enitity =  vector_to_enitity + vector_distance;
    Vector2 vect_speed(vector_to_enitity);
    vect_speed.Norm();
    Set_Speed(vect_speed*entity_speed);
}

