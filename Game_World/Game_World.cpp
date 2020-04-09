#include"Game_World.h"



Game_World::Game_World(int x_size, int y_size): player(400, 200), player2(-10, -10), world_x_size(x_size), world_y_size(y_size){

    for(int i = 0; i < GAME_WORLD_SIZE/100; i++)
    {
        entities.push_back(std::make_shared<Wall>(i*100, 0));
        entities.push_back(std::make_shared<Wall>(0, i*100));
        entities.push_back(std::make_shared<Wall>(GAME_WORLD_SIZE-1, i*100));
        entities.push_back(std::make_shared<Wall>(i*100, GAME_WORLD_SIZE-1));
    }
    entities.push_back(std::make_shared<Fire_Shooter>(737, 945));
    //std::cout << entities.back()->health << std::endl;
    entities.push_back(std::make_shared<Hospital_House>(700, 700));
    //std::cout << entities.back()->health << std::endl;
    entities.push_back(std::make_shared<Witch>(1000, 500, 2, 2));

    entities.push_back(std::make_shared<Hospital_House>(1500, 700));

    entities.push_back(std::make_shared<Wall>(500, 500));
    //std::cout << entities.back()->health << std::endl;
    std::vector<std::pair<int, int>> zombie_positions = {{1200, 200}, {1001, 300}, {1001, 234}, {701, 235}, {1003, 725}, {1325, 462}, {1322, 435}, {1345, 127}};
    for(auto &x: zombie_positions)
        entities.push_back(std::make_shared<Zombie>(x.first, x.second, 2, 2));


    entities.push_back(std::make_shared<Wall>(999, 1010));
    entities.push_back(std::make_shared<Bon_Fire>(700, 500));

    world.setPosition(0, 0);
    world.setScale(1.0f, 1.0f);
    world.setSize(sf::Vector2f(2000, 1000));
}


std::vector<std::shared_ptr<Entity>>& Game_World::Get_Entities(){
    return entities;
}

Player& Game_World::Get_Player(){
    return player;
}

Player& Game_World::Get_Second_Player(){
    return player2;
}

int Game_World::Add_Entity(Entity entity){
    entities.push_back(std::make_shared<Entity>(entity));
    return 0;
}

int Game_World::Get_Time() {
    return time;
}

int Game_World::Increment_Time() {
    time++;
    if(time == MAX_TIME)
        time = 0;
    return time;
}
