#include"Entity_Handler.h"





void Entity_Shoot(Game_World& game_world, Entity& entity, const Vector2& speed){
    if(game_world.Get_Time() % 4 != 0)
        return;
    double x_pos = entity.abs_pos_x;
    double y_pos = entity.abs_pos_y;
    Vector2 vect_speed;
    if(entity.num_of_texture%5 == 0){
      Fireball fireball(x_pos + 3*speed.x, y_pos+3*speed.y, speed.x, speed.y);
        vect_speed = speed;
        vect_speed.x = vect_speed.x/2;
        vect_speed.y = vect_speed.y/2;
        fireball.Set_Speed(vect_speed);
        (game_world.Get_Entities()).push_back(std::make_shared<Fireball>(fireball));
    }

}


void Fire_Shooter_Entity_Shoot(Game_World& game_world, Entity& fire_shooter, const Vector2& speed){
    double x_pos = fire_shooter.abs_pos_x;
    double y_pos = fire_shooter.abs_pos_y;
    Vector2 vect_speed;
    if(fire_shooter.num_of_texture == fire_shooter.max_num_of_texture){
    Fireball fireball(x_pos + 3*speed.x, y_pos+3*speed.y, speed.x, speed.y);
    vect_speed = speed;
    vect_speed.x = vect_speed.x/2;
    vect_speed.y = vect_speed.y/2;
    fireball.Set_Speed(vect_speed);
        (game_world.Get_Entities()).push_back(std::make_shared<Fireball>(fireball));


    }

}


void Witch_Shoot(Game_World& game_world, Entity& witch){
    double x_pos = witch.abs_pos_x;
    double y_pos = witch.abs_pos_y;
    Player& player = game_world.Get_Player();
    Vector2 vect_speed(player.abs_pos_x/10 - witch.abs_pos_x/10,
                        player.abs_pos_y/10 - witch.abs_pos_y/10);
    if(witch.num_of_texture == witch.max_num_of_texture){
        Magic magic(x_pos + vect_speed.x*2, y_pos+vect_speed.y*2, vect_speed.x/2, vect_speed.y/2);

        (game_world.Get_Entities()).push_back(std::make_shared<Magic>(magic));
    }
}

int Make_Entity_Action(Game_World& game_world, Entity& entity){
    Player& player = game_world.Get_Player();

    if(entity.entity_type == Entity_Type::FIRE_SHOOTER){
        Fire_Shooter_Entity_Shoot(game_world, entity, Vector2(40,0));
    }
    if(entity.entity_type == Entity_Type::ZOMBIE){
        entity.Set_Entity_Direction(player);
    }
    if(entity.entity_type == Entity_Type::WITCH){
        Witch_Shoot(game_world, entity);
        entity.Set_Entity_Direction(player);
    }
}


int Entity_Handler::Get_Mouse_Action(){
    Player& player = game_world.Get_Player();
    std::vector<std::shared_ptr<Entity>>& entities = game_world.Get_Entities();

    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        entities.push_back(std::make_shared<Fire_Shooter>(mousePosition.x + drawer.screen.pos_x, mousePosition.y + drawer.screen.pos_y));
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        Vector2 speed((mousePosition.x-player.pos_x), (mousePosition.y-player.pos_y));
        Entity_Shoot(game_world, player, speed/5);
    }



}

Direction Entity_Handler::GetReverseDirection(Direction dir)
{
    switch(dir)
    {
        case Direction::RIGHT: return Direction::LEFT;
        case Direction::LEFT: return Direction::RIGHT;
        case Direction::UP: return Direction::DOWN;
        case Direction::DOWN: return Direction::UP;
        case Direction ::NODIRECTION: return Direction::NODIRECTION;
        default: return Direction::NODIRECTION;
    }

}




Direction Entity_Handler::Take_Controll_Button_Direction(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return Direction::LEFT;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        return Direction::RIGHT;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return Direction::UP;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return Direction::DOWN;
    return Direction::NODIRECTION;
}


void Entity_Handler::World_Process() {
    game_world.Increment_Time();

    std::vector<std::shared_ptr<Entity>> &entities = game_world.Get_Entities();
    Player& player = game_world.Get_Player();

    Direction controll_buton_direction;
    controll_buton_direction = Take_Controll_Button_Direction();
    player.move_entity(controll_buton_direction);
    Get_Mouse_Action();


    for (auto it = entities.begin(); it < entities.end(); it++) {
        (*it)->move_entity();
        for(auto itr = entities.begin(); itr < entities.end(); itr++){
            if(it != itr && (*it)->Has_Collised(**itr))
            {
                if((*it)->type_of_moving == Type_Of_Moving::NONSTATIC)
                    (*it)->Process_Collision(*(*itr));

                if((*it)->entity_type != (*itr)->entity_type){
                    (*itr)->Get_Damage_From_Entity(*(*it));
                    (*it)->Get_Damage_From_Entity(*(*itr));
                }
            }
        }

        Make_Entity_Action(game_world, *(*it));

        if((*it)->abs_pos_x >= GAME_WORLD_SIZE || (*it)->abs_pos_y >= GAME_WORLD_SIZE ||
                    (*it)->abs_pos_x < 0 || (*it)->abs_pos_y < 0 || (*it)->health < 0)
        {
            it = entities.erase(it) - 1;
            continue;
        }
        if ((*it)->Has_Collised(player)) {
            if((*it)->entity_type == Entity_Type::HOSPITAL_HOUSE)
                player.Get_Medication();
            player.move_entity(GetReverseDirection(controll_buton_direction),
                                         player.entity_speed);
            player.health -= (*it)->damage;

            break;
        }

    }

    if (player.health < 0) {
        cout << "GAME OVER\n";
        // return;

    }


}
