#include<SFML/Graphics.hpp>


class Main_Menu{
public:
    sf::RectangleShape menu;
    sf::Texture menu_textures;

public:
    Main_Menu(){
        menu.setSize(sf::Vector2f(1850, 1050));
        menu.setPosition(0,0);
        menu_textures.loadFromFile("textures/font/f.png");
        menu.setTexture(&menu_textures);
    }

    int Main_Menu_Draw(sf::RenderWindow &window){
        window.draw(menu);
        return 0;
    }

};
