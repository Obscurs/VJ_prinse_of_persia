//
// Created by arnito on 26/02/17.
//

#include "RunningGame.h"
#include "Settings.h"

RunningGame::RunningGame(sf::RenderWindow &window)
        :
          view_game(&window,MagicView::crop,sf::Vector2i(Settings::GAME_WIDTH,Settings::GAME_HEIGHT))
{
    texture_plain_sprite.create(Settings::GAME_WIDTH, Settings::GAME_HEIGHT);
    texMan = new TextureManager("resources/map_tiles.png", 16, 16);
}

sf::Sprite RunningGame::get_plain_sprite(sf::VertexArray &render_array){
    texture_plain_sprite.clear(sf::Color(0,0,0,0));
    sf::RenderStates states;
    states.texture = texMan->getTexture();
    texture_plain_sprite.draw(render_array, states);
    texture_plain_sprite.display();
    sf::Sprite sprite_result(texture_plain_sprite.getTexture());
    return sprite_result;
}
void RunningGame::update(sf::RenderWindow &window,float delta,Inputs &inputs){

    //view_game.setCenter(player.GetPosition().x+(player.GetWidth()/2), player.GetPosition().y+(player.GetHeight()/2));
}
void RunningGame::draw(sf::RenderWindow &window){
    const sf::View &aux = window.getView();
    window.setView(view_game);
    sf::VertexArray render_array(sf::Quads , (uint)(4));
    sf::Sprite sprite = get_plain_sprite(render_array);
    window.draw(sprite);
    window.setView(aux);
}
void RunningGame::restart(){

}



RunningGame::~RunningGame() {
}
