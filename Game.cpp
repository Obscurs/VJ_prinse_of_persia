//
// Created by arnito on 26/02/17.
//

#include <stdio.h>
#include <math.h>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include <dirent.h>
#include <fstream>
#include <sys/stat.h>
#include <string.h>

#include <limits.h>
#include <unistd.h>
#include <unistd.h>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "Game.h"
#include "Settings.h"

Game::Game():
        inputs(),
        window(),
        game(window)
{
    _gameState = Uninitialized;

}
Game::~Game() {

}




void Game::Start(void)
{

    if(_gameState != Uninitialized)
        return;
    window.create(sf::VideoMode(Settings::SCREEN_WIDTH,Settings::SCREEN_HEIGHT,32),"Genland!");

    // sf::View viewPlayer(sf::FloatRect(200, 200, Settings::SCREEN_WIDTH, Settings::SCREEN_HEIGHT));

    _gameState= Game::ShowingMenu;
    sf::Clock clock1;
    sf::Clock clock2;
    float lastTime = 0;

    char c[10];
    sf::Text text;
    sf::Font font;
    text.setCharacterSize(24);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::String str("no data");
    text.setString(str);

    if (!font.loadFromFile("resources/font1.ttf"))
    {
        std::cout << "font error" << std::endl;
    }
    text.setFont(font); // font is a sf::Font
    float fps_timer=0;
    int fps_count=0;
    int fps_count2=0;

    MenuMain::view = MagicView(&window,MagicView::expanded,sf::Vector2i(2000,2000));
    //NewGameMenu::view = MagicView(&window,MagicView::expanded,sf::Vector2i(2000,2000));
    //MenuLoadGame::view = MagicView(&window,MagicView::expanded,sf::Vector2i(2000,2000));
    //MenuConfigGame::view = MagicView(&window,MagicView::expanded,sf::Vector2i(2000,2000));

    while(!IsExiting())
    {


        double delta =  clock1.restart().asSeconds();


        float currentTime = clock2.restart().asSeconds();
        float fps = 1.f / currentTime;
        fps_count += 1;
        fps_count2 += fps;
        //fps = roundf(fps/10)*10;
        lastTime = currentTime;
        //std::cout << fps << std::endl;

        window.clear(sf::Color(0,255,0));
        GameLoop(delta);
        fps_timer += lastTime;
        sf::View currentView = window.getView();
        sf::Vector2f centerView = currentView.getCenter();
        sf::Vector2f sizeView = currentView.getSize();
        text.setPosition(centerView.x-sizeView.x/2, centerView.y-sizeView.y/2);
        if(fps_timer > 1){
            sprintf(c, "%i", fps_count2/fps_count);
            std::string string(c);
            sf::String str(string);
            text.setString(str);

            fps_count = 0;
            fps_count2 = 0;
            fps_timer = 0;
        }

        window.draw(text);
        window.display();
        //sf::sleep(sf::milliseconds(30));
    }

    window.close();
}

bool Game::IsExiting()
{
    if(_gameState == Game::Exiting)
        return true;
    else
        return false;
}




void Game::GameLoop(double delta)
{

    sf::Event currentEvent;
    sf::Font font;
    if (!font.loadFromFile("resources/font1.ttf"))
    {
        std::cout << "font error" << std::endl;
    }
    Game::inputs.Update();
    switch(_gameState)
    {
        case Game::ShowingMenu:
        {
            if(MenuMain::newGameClicked(Game::inputs)) _gameState = NewGame;
            else if(MenuMain::exitClicked(Game::inputs)) {
                ExitGame();
            }
            else if(MenuMain::loadClicked(Game::inputs)) _gameState = LoadGame;
            else if(MenuMain::configClicked(Game::inputs)) _gameState = Config;
            while(window.pollEvent(currentEvent))
            {
                if(currentEvent.type == sf::Event::MouseWheelMoved)
                {
                    Game::inputs.UpdateWheel(currentEvent.mouseWheel.delta);
                }

                else if (
                        (currentEvent.type == sf::Event::KeyPressed) &&
                        (currentEvent.key.code == sf::Keyboard::Tab))
                {
                    std::cout << "bye" << std::endl;
                    _gameState = Playing;
                }
                else if (currentEvent.type == sf::Event::Resized){
                    MenuMain::view.update();
                    std::cout << "res" << std::endl;
                }
                else if (currentEvent.type == sf::Event::Closed)
                {
                    Game::ExitGame();
                }
            }
            MenuMain::Update();
            MenuMain::Draw(window, font);
            break;
        }
        case Game::NewGame:
        {

        }
        case Game::LoadGame:
        {

        }
        case Game::Playing:
        {
            while(window.pollEvent(currentEvent))
            {
                if(currentEvent.type == sf::Event::MouseWheelMoved)
                {
                    Game::inputs.UpdateWheel(currentEvent.mouseWheel.delta);
                }
                else if (currentEvent.type == sf::Event::Resized){
                    std::cout << "res" << std::endl;
                    //Game::game.view_game.update();
                }
                else if (
                        (currentEvent.type == sf::Event::KeyPressed) &&
                        (currentEvent.key.code == sf::Keyboard::Tab))
                {
                    std::cout << "bye" << std::endl;
                    _gameState = ShowingMenu;
                    //window.close();
                }
                else if (currentEvent.type == sf::Event::Closed)
                {
                    Game::ExitGame();
                }
            }
            //Game::game.update(window,delta,inputs);
            //Game::game.draw(window);
            break;
        }
        case Game::Config:
        {

        }
    }
}



void Game::ExitGame()
{
    _gameState = Exiting;
}




