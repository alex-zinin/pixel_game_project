#include"Drawer.h"



Screen::Screen(int x, int y): size_x(SCREEN_X_SIZE - 100), size_y(SCREEN_Y_SIZE - 100)
{
    pos_x = x;
    pos_y = y;
}

void Screen::move(int x, int y){
    pos_x += x;
    pos_y += y;
}

void Screen::Set_Pos(int x, int y)
{
    pos_x = x;
    pos_y = y;
}



Info_Table::Info_Table(int size_x, int size_y, sf::RenderWindow &wind, Game_World &gm): x_size(size_x), y_size(size_y), window(wind), game_world(gm) {
    table.setSize(sf::Vector2f(x_size, y_size));
    table.setPosition(SCREEN_X_SIZE - 2*x_size, SCREEN_Y_SIZE- y_size + 140);

    info_table_texture.setRepeated(true);
    info_table_texture.loadFromFile("textures/table_info_textures/table_texture.png");
    table.setTexture(&info_table_texture);


    heart_texture.setRepeated(true);
    heart_texture.loadFromFile("textures/table_info_textures/heart.jpg");
    int heart_size = 50;
    for(int i = 0; i < MAX_NUM_OF_HEARTS; i++)
    {
        sf::RectangleShape heart;
        heart.setSize(sf::Vector2f(heart_size, heart_size));
        heart.setPosition(SCREEN_X_SIZE - 2*x_size + 30 + i* heart_size, SCREEN_Y_SIZE- y_size + 180 );
        heart.setTexture(&heart_texture);
        hearts.push_back(heart);
    }

    text.setPosition(SCREEN_X_SIZE - 2*x_size + 30, SCREEN_Y_SIZE- y_size + 170);
    font.loadFromFile("textures/table_info_textures/CyrilicOld.TTF");
    text.setFont(font); // font is a sf::Font
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);






}



void Info_Table::Show_Table(){
    window.draw(table);
    Player& player = game_world.Get_Player();

    int health = MAX_NUM_OF_HEARTS*player.health/PLAYER_HEALTH;
    for(int i = 0; i <  health; i++)
        window.draw(hearts[i]);

    text.setString("Health = "+ std::to_string(player.health) + "/" + std::to_string(PLAYER_HEALTH));
    window.draw(text);


}







Drawer::Drawer(sf::RenderWindow& wind, Game_World& gm): window(wind), game_world(gm),
                                                        screen(0, 0),
                                                        info_table(TABLE_X_SIZE, TABLE_Y_SIZE, wind, gm),
                                                        mini_map(250, gm, -250, -140, *this),
                                                        hearts(MAX_NUM_OF_HEARTS) {

    sf::Texture gm_world_texture;
    gm_world_texture.setRepeated(true);
    gm_world_texture.loadFromFile("textures/s3.png");
    game_world_texture = gm_world_texture;
    game_world.world.setTexture(&game_world_texture);

    int max_num_of_texture_zombie = Zombie::MAX_NUM_OF_TEXTURE;
    std::vector<sf::Texture> texture_zombie(max_num_of_texture_zombie + 1);
    for(int i = 0; i < max_num_of_texture_zombie + 1; i++)
    {int index = i/3;
        if(i == max_num_of_texture_zombie)
        texture_zombie[i].loadFromFile("textures/zombie/pos" +std::to_string(17)+".png");
        else
            texture_zombie[i].loadFromFile("textures/zombie/pos" +std::to_string(index%17)+".png");

    }
    animation_texture[Entity_Type::ZOMBIE] = texture_zombie;


    sf::Texture texture_wall;
    texture_wall.setRepeated(true);
    texture_wall.loadFromFile("textures/wall_texture.jpg");
    static_textures[Entity_Type::WALL] = texture_wall;


    sf::Texture texture_hospital;
    texture_hospital.setRepeated(true);
    texture_hospital.loadFromFile("textures/house/house.png");
    static_textures[Entity_Type::HOSPITAL_HOUSE] = texture_hospital;

    int max_num_of_texture_bon_fire = Bon_Fire::MAX_NUM_OF_TEXTURE;
    std::vector<sf::Texture> texture_bon_fire(max_num_of_texture_bon_fire + 1);
    for(int i = 0; i < max_num_of_texture_bon_fire + 1; i++)
    {
        texture_bon_fire[i].loadFromFile("textures/bon_fire_textures/pos" +std::to_string(i)+".png");
    }
    animation_texture[Entity_Type::BON_FIRE] = texture_bon_fire;

    int max_num_of_texture_player = Player::MAX_NUM_OF_TEXTURE;
    std::vector<sf::Texture> player_texture(max_num_of_texture_player + 1);
    for(int i = 0; i < max_num_of_texture_player + 1; i++)
    {
        player_texture[i].loadFromFile("textures/player_textures/pos" +std::to_string(i)+".png");
    }
    animation_texture[Entity_Type::PLAYER] = player_texture;



    std::vector<sf::Texture> reversed_player_texture(max_num_of_texture_player + 1);
    for(int i = 0; i < max_num_of_texture_player + 1; i++)
    {
        reversed_player_texture[i].loadFromFile("textures/player_textures/rpos" +std::to_string(i)+".png");
    }
    reversed_animation_texture[Entity_Type::PLAYER] = reversed_player_texture;

    int max_num_of_texture_fire_shooter = Fire_Shooter::MAX_NUM_OF_TEXTURE;
    std::vector<sf::Texture> fire_shooter_texture(max_num_of_texture_fire_shooter + 1);
    for(int i = 0; i < max_num_of_texture_fire_shooter + 1; i++){
        int index = i/3;
        if(i == max_num_of_texture_fire_shooter)
            fire_shooter_texture[i].loadFromFile("textures/fire_baller/pos"+ std::to_string(8)+ ".png");
        else
            fire_shooter_texture[i].loadFromFile("textures/fire_baller/pos"+ std::to_string(index%8)+ ".png");
    }
    animation_texture[Entity_Type::FIRE_SHOOTER] = fire_shooter_texture;

    int max_num_of_texture_witch = Witch::MAX_NUM_OF_TEXTURE;
    std::vector<sf::Texture> witch_texture(max_num_of_texture_witch + 1);
    for(int i = 0; i < max_num_of_texture_witch + 1; i++){
        int index = i/3;
        if(i == max_num_of_texture_witch)
            witch_texture[i].loadFromFile("textures/witch/pos"+ std::to_string(20)+ ".png");
        else
            witch_texture[i].loadFromFile("textures/witch/pos"+ std::to_string(index%20)+ ".png");

        //   else
          //  witch_texture[i].loadFromFile("textures/witch/pos"+ std::to_string(index%8)+ ".png");
    }
    animation_texture[Entity_Type::WITCH] = witch_texture;

    int max_num_of_texture_fireball = Fireball::MAX_NUM_OF_TEXTURE;
    std::vector<sf::Texture> fireball_texture(max_num_of_texture_fireball + 1);
    for(int i = 0; i < max_num_of_texture_fireball; i++){
        fireball_texture[i].loadFromFile("textures/fireball/pos"+ std::to_string(i)+ ".png");
    }
    animation_texture[Entity_Type::FIREBALL] = fireball_texture;

    int max_num_of_texture_magic = Magic::MAX_NUM_OF_TEXTURE;
    std::vector<sf::Texture> magic_texture(max_num_of_texture_magic + 1);
    for(int i = 0; i < max_num_of_texture_magic; i++){
        magic_texture[i].loadFromFile("textures/witch/magic/pos"+ std::to_string(i)+ ".png");
    }
    animation_texture[Entity_Type::MAGIC] = magic_texture;

    heart_texture.setRepeated(true);
    heart_texture.loadFromFile("textures/table_info_textures/heart.jpg");




}



void Drawer::Draw_Health(sf::RenderWindow& window, const Entity& entity){

    for(int i = 0; i < MAX_NUM_OF_HEARTS; i++)
    {
        hearts[i].setSize(sf::Vector2f(heart_size, heart_size));
        hearts[i].setPosition(entity.pos_x + i* heart_size, entity.pos_y - 50);
        hearts[i].setTexture(&heart_texture);
    }

    int health = MAX_NUM_OF_HEARTS*entity.health/entity.max_health;
    for(int i = 0; i <  health; i++)
        window.draw(hearts[i]);


}



void Drawer::Show_Player_Table(){
    window.draw(info_table.table);
}


void Drawer::Move_Screen_To_Player(){
    Player& player = game_world.Get_Player();

    if(player.pos_y >= screen.size_y)
    {
        screen.pos_y += screen.size_y/2;
        player.pos_y = screen.size_y/2;
    }

    if(player.pos_x >= screen.size_x)
    {
        screen.pos_x += screen.size_x/2;
        player.pos_x = screen.size_x/2;
    }

    if(player.pos_y <= 0)
    {
        screen.pos_y -= screen.size_y/2;
        player.pos_y = screen.size_y/2;
    }

    if(player.pos_x <= 0)
    {
        screen.pos_x -= screen.size_x/2;
        player.pos_x = screen.size_x/2;
    }
}



void Drawer::Draw_World(){
    Player& player = game_world.Get_Player();
    Player& player2 = game_world.Get_Second_Player();

    window.draw(game_world.world);
    Move_Screen_To_Player();

    player2.Set_Pos(player2.abs_pos_x-screen.pos_x,
                               player2.abs_pos_y-screen.pos_y);

    for(auto& x: game_world.Get_Entities()) {
        x->Set_Pos(x->abs_pos_x-screen.pos_x, x->abs_pos_y-screen.pos_y);
    }

    int index = player.num_of_texture/4;
    if(player.vector_speed.x > 0)
        player.sprite.setTexture(&(animation_texture[player.entity_type])[index]);
    else
        player.sprite.setTexture(&(reversed_animation_texture[player.entity_type])[index]);


    if(player2.vector_speed.x > 0)
        player2.sprite.setTexture(&(animation_texture[player2.entity_type])[index]);
    else
        player2.sprite.setTexture(&(reversed_animation_texture[player2.entity_type])[index]);

    window.draw(player.sprite);
    Draw_Health(window, player);

    window.draw(player2.sprite);
    Draw_Health(window, player2);



    if(player2.num_of_texture == 4*player2.max_num_of_texture)
        player2.num_of_texture = 0;
    else
        player2.num_of_texture++;

    if(player.num_of_texture == 4*player.max_num_of_texture)
        player.num_of_texture = 0;
    else
        player.num_of_texture++;

    for(auto& x: game_world.Get_Entities()){
        if(x->type_of_animation == Type_Of_Animation::NONSTATIC){
            Draw_Health(window, *x);
            x->sprite.setTexture(&(animation_texture[x->entity_type])[x->num_of_texture]);
            window.draw(x->sprite);
            if(x->num_of_texture == x->max_num_of_texture)
                x->num_of_texture = 0;
            else
            {
                if(game_world.Get_Time() % 4 == 0)
                    x->num_of_texture++;
            }
        } else{
            x->sprite.setTexture(&static_textures[x->entity_type]);
            window.draw(x->sprite);
        }
    }


    info_table.Show_Table();
    mini_map.Draw_Map();

}




Drawer::Mini_Map::Mini_Map(int size, Game_World& gm, int x_pos, int y_pos, Drawer& dr): size_x(size), size_y(size), game_world(gm), drawer(dr), pos_x(x_pos), pos_y(y_pos){
    relative_map_to_world = (int) (game_world.world_x_size/size_x);
    map.setSize(sf::Vector2f(size_x, size_y));
    map_texture.loadFromFile("textures/map_texture.jpg");
    map.setTexture(&map_texture);
    map.setPosition(SCREEN_X_SIZE/2 + x_pos, SCREEN_Y_SIZE + y_pos);
    pos_x = SCREEN_X_SIZE/2 + x_pos;
    pos_y = SCREEN_Y_SIZE+ y_pos;

}



void Drawer::Mini_Map::Draw_Map(){
    Player& player = game_world.Get_Player();


    drawer.window.draw(map);
    for(auto& x: game_world.Get_Entities()){
        sf::RectangleShape shape;

        double entity_size_on_map_x = x->size_x/relative_map_to_world;
        double entity_size_on_map_y = x->size_y/relative_map_to_world;
        double entity_pos_on_map_x = x->abs_pos_x/relative_map_to_world;
        double entity_pos_on_map_y = x->abs_pos_y/relative_map_to_world;

        shape.setSize(sf::Vector2f(entity_size_on_map_x, entity_size_on_map_y));
        if(x->type_of_moving == Type_Of_Moving::STATIC){
            shape.setTexture(&drawer.static_textures[x->entity_type]);
        } else
            shape.setTexture(&(drawer.animation_texture[x->entity_type])[0]);
        shape.setPosition(entity_pos_on_map_x + pos_x, entity_pos_on_map_y + pos_y);
        drawer.window.draw(shape);
    }


    sf::RectangleShape map_player;
    double player_pos_on_map_x = player.abs_pos_x/relative_map_to_world;
    double player_pos_on_map_y = player.abs_pos_y/relative_map_to_world;
    map_player.setSize(sf::Vector2f(10, 10));
    map_player.setTexture(&(drawer.animation_texture[player.entity_type])[0]);
    map_player.setPosition(player_pos_on_map_x + pos_x, player_pos_on_map_y+pos_y);
    drawer.window.draw(map_player);

}

