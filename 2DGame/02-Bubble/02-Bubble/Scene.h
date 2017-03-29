#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "EntityMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Gui.h"
#include<iostream>
#include<fstream>
#include<sstream>

// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	ShaderProgram& getProgram();
private:
	void initShaders();

private:
	bool first_update;
	int totalPlayTime;
	EntityMap *entities;
	TileMap *map;
	TileMap *background;
	TileMap *foreground;
	Gui *gui;
	Player *player;
	Enemy *enemy;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

};


#endif // _SCENE_INCLUDE

