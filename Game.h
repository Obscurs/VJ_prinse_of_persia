//
// Created by arnito on 26/02/17.
//

#ifndef VJ_PRINSE_OF_PERSIA_GAME_H
#define VJ_PRINSE_OF_PERSIA_GAME_H


#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


#include "MenuMain.h"
#include "RunningGame.h"
#include "MagicView.h"
#include "Inputs.h"
#include <algorithm>
class Game
{
public:
    Game();
    ~Game();
    void Start();



private:
    bool IsExiting();
    void GameLoop(double delta);
    void ExitGame();


    enum GameState { Uninitialized, NewGame, LoadGame, Paused,
        ShowingMenu, Playing, Exiting, Config };

    GameState _gameState;
    sf::RenderWindow window;
    Inputs inputs;
    RunningGame game;


};


#endif //VJ_PRINSE_OF_PERSIA_GAME_H
