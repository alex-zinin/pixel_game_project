#include"unit_tests.h"


void Test_Vector2(){
    Vector2 vector1(10, 34);
    ASSERT_EQUAL(vector1.x, 10);
    ASSERT_EQUAL(vector1.y, 34);


    Vector2 vector2;
    ASSERT_EQUAL(vector2.x, 0);
    ASSERT_EQUAL(vector2.y, 0);

    {
        Vector2 vect1(10, 23);
        Vector2 vect2(11, 33);
        vect1 = vect1 + vect2;
        AssertEqual(vect1.x, 21, "Operator+");
        AssertEqual(vect1.y, 56, "Operator+");

    }

    {
        Vector2 vect1(10, 23);
        Vector2 vect2(11, 33);
        vect1 = vect1 - vect2;
        AssertEqual(vect1.x, -1, "Operator-");
        AssertEqual(vect1.y, -10, "Operator-");
    }

    {
        Vector2 vect1(10, 2);
        vect1 = (vect1)*7;
        AssertEqual(vect1.x, 70, "Operator*");
        AssertEqual(vect1.y, 14, "Operator*");
    }


}

void Test_Sender(){
    Game_World game_world(GAME_WORLD_SIZE, GAME_WORLD_SIZE);
    game_world.Add_Entity(Fireball(10, 10, 20, 20));
    Player& player = game_world.Get_Player();
    player.health = 10;
    player.abs_pos_x = 12;
    player.abs_pos_y = 17;
    AssertEqual(From_World_To_String(game_world), "$BEGIN&&TYPE=PLAYER:speed={0.000000,0.000000};absx=12,absy=17,10&&{20.000000,20.000000}&&#");

}

void Test_Changer_From_Message(){
    Game_World game_world(GAME_WORLD_SIZE, GAME_WORLD_SIZE);
    game_world.Add_Entity(Fireball(10, 10, 20, 20));
    Player& player = game_world.Get_Player();
    player.health = 10;
    player.abs_pos_x = 12;
    player.abs_pos_y = 17;
    Change_Game_World_From_String("$BEGIN&&TYPE=PLAYER:speed={0.000000,0.000000};absx=12,absy=17,10&&{20.000000,20.000000}&&#",
            game_world);
    Player &player2 = game_world.Get_Second_Player();
    Entity fireball = (*((game_world.Get_Entities()).back()));
    AssertEqual(player2.abs_pos_x, 12);
    AssertEqual(player2.abs_pos_y, 17);
    AssertEqual(player2.health, 10);
    AssertEqual(fireball.vector_speed.x, 20.000000);
    AssertEqual(fireball.vector_speed.y, 20.000000);

}
