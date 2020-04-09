#include<iostream>
#include"../Entities/Entities.h"
#include<sstream>
#include"../Game_World/Game_World.h"


std::string mass_to_string(char *mass);
Player From_String_To_Player(const std::string& str);
Wall From_String_To_Wall(const std::string& str);
Fire_Shooter From_String_To_Fire_Shooter(const std::string& str);
Fireball From_String_To_Fireball(const std::string& str);
Entity From_String_Entity(const std::string& str);
void Change_Game_World_From_String(const std::string& str, Game_World& game_world);
std::string From_World_To_String(Game_World& game_world);
