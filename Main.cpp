#include <stdio.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <iostream>
#include <cassert>
#include <fstream>
#include "Game.h"
#include "Settings.h"


sf::Clock deltaClock;
sf::Time dt;
int Settings::SCREEN_WIDTH = 0;
int Settings::SCREEN_HEIGHT = 0;
int Settings::GAME_WIDTH = 0;
int Settings::GAME_HEIGHT = 0;
int main(int argc, char** argv)
{
    //bool true_exit = false;
    //while(!true_exit) {
        std::ifstream myfile("config/config");
        myfile >> Settings::SCREEN_WIDTH >> Settings::SCREEN_HEIGHT;
        myfile.close();
        Settings::GAME_WIDTH = Settings::GAME_WIDTH_MED;
        Settings::GAME_HEIGHT = Settings::GAME_HEIGHT_MED;
        Game *g = new Game();
        g->Start();
        //true_exit = g->true_exit;
    //}
    return 0;
}