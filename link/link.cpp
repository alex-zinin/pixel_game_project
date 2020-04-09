#include"link.h"


std::string mass_to_string(char *mass){
    std::string result;
    int i = 0;
    if(mass[0] != '$')
        return result;
    while(mass[i] != '#'  || i < 50){
        result.push_back(mass[i]);
        i++;
    }
    result.push_back(mass[i]);
    return result;
}


Entity From_String_Entity(const std::string& str){
    std::istringstream is(str);
    std::string type;
    char trash;
    for(int i = 0; i < 12; i++)
        is >> trash;
    getline(is, type, ':');
    Entity_Type entityType = From_String_To_Entity_Type(type);
    std::string str2;
    getline(is, str2);
    if(entityType == Entity_Type::WALL)
        return From_String_To_Wall(str2);
    if(entityType == Entity_Type::FIRE_SHOOTER)
        return From_String_To_Fire_Shooter(str2);
    if(entityType == Entity_Type::FIREBALL)
        return From_String_To_Fireball(str2);
}


void Change_Game_World_From_String(const std::string& str, Game_World& game_world) {
    std::vector<Entity> result;
    std::istringstream is(str);
    char trash;
    Player& player2 = game_world.Get_Second_Player();
    std::vector<std::shared_ptr<Entity>> &entities = game_world.Get_Entities();

    std::string tr_string;
    getline(is, tr_string, '$');
    getline(is, tr_string, '&');
    if (tr_string == "BEGIN")
        std::cout << "Successful receiving" << std::endl;
    is >> trash;
    getline(is, tr_string, ':');
    if (tr_string == "TYPE=PLAYER")
        std::cout << "Sucessful player" << std::endl;
    getline(is, tr_string, '&');
    player2 = From_String_To_Player(tr_string);
    double speed_x, speed_y;
    is >> trash >> trash;
    is >> speed_x >> trash >> speed_y;
    getline(is, tr_string, '#');
    if(speed_x*speed_x + speed_y*speed_y >= 425 )
        (entities).push_back(std::make_shared<Fireball>(player2.abs_pos_x,
                                               player2.abs_pos_y, speed_x, speed_y));
    return;
}


std::string From_World_To_String(Game_World& game_world){
    std::string result;
    Player& player = game_world.Get_Player();
    std::vector<std::shared_ptr<Entity>> &entities = game_world.Get_Entities();

    result += "$BEGIN&&";
    result += player.From_Entity_To_String();
    result+= '{';
    result += std::to_string(entities.back()->vector_speed.x);
    result += ',';
    result += std::to_string(entities.back()->vector_speed.y);
    result += "}&&";
    result += '#';
    return result;
}


Player From_String_To_Player(const std::string& str){
    std::istringstream is(str);
    int abs_x = 0, abs_y = 0;
    double sx, sy;
    int health = 0;
    char trash;
    for(int i = 0; i < 7; i++)
        is >> trash;
    is >> sx >> trash >> sy >> trash >> trash;
    for(int i = 0; i < 5; i++)
        is >> trash;
    is >> abs_x;
    is >> trash;
    for(int i = 0; i < 5; i++)
        is >> trash;
    is >> abs_y;
    is>> trash;
    is >> health;
    return Player(abs_x, abs_y, health);

}


Wall From_String_To_Wall(const std::string& str){
    std::istringstream is(str);
    double sx, sy;
    int abs_x = 0, abs_y = 0;
    char trash;
    for(int i = 0; i < 7; i++)
        is >> trash;
    is >> sx >> trash >> sy >> trash >> trash;
    for(int i = 0; i < 5; i++)
        is >> trash;
    is >> abs_x;
    is >> trash;
    for(int i = 0; i < 5; i++)
        is >> trash;
    is >> abs_y;
    return Wall(abs_x, abs_y);

}


Fire_Shooter From_String_To_Fire_Shooter(const std::string& str){
    std::istringstream is(str);
    int abs_x = 0, abs_y = 0;
    double sx, sy;
    char trash;
    for(int i = 0; i < 7; i++)
        is >> trash;
    is >> sx >> trash >> sy >> trash >> trash;
    for(int i = 0; i < 5; i++)
        is >> trash;
    is >> abs_x;
    is >> trash;
    for(int i = 0; i < 5; i++)
        is >> trash;
    is >> abs_y;
    return Fire_Shooter(abs_x, abs_y);

}


Fireball From_String_To_Fireball(const std::string& str){
    std::istringstream is(str);
    int abs_x = 0, abs_y = 0;
    double sx = 0, sy = 0;
    char trash;
    for(int i = 0; i < 7; i++)
        is >> trash;
    is >> sx >> trash >> sy >> trash >> trash;
    for(int i = 0; i < 5; i++)
        is >> trash;
    is >> abs_x;
    is >> trash;
    for(int i = 0; i < 5; i++)
        is >> trash;
    is >> abs_y;
    return Fireball(abs_x, abs_y, sx, sy);

}
