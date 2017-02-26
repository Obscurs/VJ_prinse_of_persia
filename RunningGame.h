//
// Created by arnito on 26/02/17.
//

#ifndef VJ_PRINSE_OF_PERSIA_RUNNINGGAME_H
#define VJ_PRINSE_OF_PERSIA_RUNNINGGAME_H
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "MenuMain.h"
#include "MagicView.h"
#include "TextureManager.h"
class RunningGame {
public:
    void restart();
    RunningGame(sf::RenderWindow &window);
    ~RunningGame();
    Inputs inputs;
    sf::RenderTexture texture_plain_sprite;
    MagicView view_game;
    TextureManager* texMan;
    void update(sf::RenderWindow &window,float delta,Inputs &inputs);
    void draw(sf::RenderWindow &window);
    sf::Sprite get_plain_sprite(sf::RenderWindow& renderWindow,sf::VertexArray &render_array);

};


#endif //VJ_PRINSE_OF_PERSIA_RUNNINGGAME_H
