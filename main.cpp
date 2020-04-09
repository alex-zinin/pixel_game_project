#include <iostream>
#include <SFML/Graphics.hpp>
#include<cstdlib>
#include <vector>
#include<cmath>
#include<ctime>
#include<algorithm>
#include<SFML/Window.hpp>
#include<future>
#include<utility>
#include<thread>
#include<sstream>
#include"including_headers.h"

using  namespace std;

int main() {

    TestRunner tr;
    RUN_TEST(tr, Test_Vector2);
    RUN_TEST(tr, Test_Sender);
    RUN_TEST(tr, Test_Changer_From_Message);

    sf::RenderWindow window(sf::VideoMode(2000, 900), "SFML window");
    Game_World game_world(GAME_WORLD_SIZE, GAME_WORLD_SIZE);
    Drawer drawer(window, game_world);
    Entity_Handler entity_handler(game_world, drawer, window);
    Server server;
    Client client;
    Main_Menu main_menu;


    int stat = 1;
    int index = 0;

   auto serv = async([&server] {
                    while (1)
                        server.Process();
                });

    main_menu.Main_Menu_Draw(window);
    window.display();
    while(1){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            break;
    }

//    auto message = async([&]{
//
//            while(1)
//            {
//                Change_Game_World_From_String(client.Get_Message(), game_world);
//            }
//
//
//
//        return 0;});

    auto game_process = async([&]{
        while (window.isOpen()) {
            index++;
            window.clear();
            entity_handler.World_Process();
            drawer.Draw_World();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.display();
          client.Send_Message(From_World_To_String(game_world));
        }
        return 0;
    });


    return 0;
}


