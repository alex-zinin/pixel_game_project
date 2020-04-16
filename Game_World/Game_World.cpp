#include"Game_World.h"



Game_World::Game_World(int x_size, int y_size): player(350, 700), player2(-200, -200), world_x_size(x_size), world_y_size(y_size){

    for(int i = 0; i < GAME_WORLD_SIZE/100; i++)
    {
        entities.push_back(std::make_shared<Wall>(i*100 + 200, 200));
        entities.push_back(std::make_shared<Wall>(200, i*100));
        entities.push_back(std::make_shared<Wall>(GAME_WORLD_SIZE-1 - 200, i*100));
        entities.push_back(std::make_shared<Wall>(i*100, GAME_WORLD_SIZE-1 - 200));
        entities.push_back(std::make_shared<Tree1>(i*100, 0));
        entities.push_back(std::make_shared<Tree2>(0, i*100));
        entities.push_back(std::make_shared<Tree2>(GAME_WORLD_SIZE-1, i*100));
        entities.push_back(std::make_shared<Tree1>(i*100, GAME_WORLD_SIZE-1 - 100));
    }

    entities.push_back(std::make_shared<House>(1600, 800));
    entities.push_back(std::make_shared<Bon_Fire>(1800, 900));
     entities.push_back(std::make_shared<Pit>(1500, 900));

     entities.push_back(std::make_shared<Torch>(900, 900));
    entities.push_back(std::make_shared<Fire_Shooter>(1200, 700));
    entities.push_back(std::make_shared<Hospital_House>(900, 700));
    entities.push_back(std::make_shared<Witch>(1000, 500, 2, 2));



    entities.push_back(std::make_shared<Hospital_House>(2200, 1700));
    entities.push_back(std::make_shared<Bon_Fire>(2000, 1800));
    entities.push_back(std::make_shared<Bench>(2400, 1800));


    entities.push_back(std::make_shared<Bon_Fire>(1000, 1400));
    entities.push_back(std::make_shared<Basin>(700, 1400));


    entities.push_back(std::make_shared<Bon_Fire>(1000, 1000));
    entities.push_back(std::make_shared<Cart>(700, 1000));


    std::vector<std::pair<int, int>> tree1_positions = {{1200, 2200}, {1201, 1300}, {1701, 1234}, {2701, 1735}, {1003, 2225}, {1325, 2462}, {1322, 1435}, {1345, 2127}};
    for(auto &x: tree1_positions)
        entities.push_back(std::make_shared<Tree1>(x.first, x.second));


    std::vector<std::pair<int, int>> tree2_positions = {{1900, 2109}, {2201, 2100}, {2501, 2234}, {2601, 2535}, {1403, 2125}, {2325, 2362}, {2322, 2435}, {2345, 2127}};
    for(auto &x: tree2_positions)
        entities.push_back(std::make_shared<Tree2>(x.first, x.second));

    std::vector<std::pair<int, int>> tree3_positions = {{900, 1109}, {201, 2140}, {701, 234}, {2601, 635}, {2403, 512}, {2325, 762}, {2322, 435}, {2345, 727}};
    for(auto &x: tree3_positions)
        entities.push_back(std::make_shared<Tree3>(x.first, x.second));

    std::vector<std::pair<int, int>> zombie_positions = {{1200, 2100}, {1001, 2300}, {1001, 2234}, {1701, 2235}, {1003, 2325}, {1325, 1462}, {1322, 1435}, {1345, 1127}};
    for(auto &x: zombie_positions)
        entities.push_back(std::make_shared<Zombie>(x.first, x.second, 2, 2));



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
