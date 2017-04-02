#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y -13

#define CHUNK_X_SIZE 256
#define CHUNK_Y_SIZE 256
#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 4
#define INIT_ENEMY_X_TILES 25
#define INIT_ENEMY_Y_TILES 5

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

Scene::Scene()
{
	entities = NULL;
	map = NULL;
	background = NULL;
	foreground = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (entities != NULL)
		delete entities;
	if (background != NULL)
		delete background;
	if (foreground != NULL)
		delete foreground;
	if (gui != NULL)
		delete gui;
	if(player != NULL)
		delete player;
	//if (enemy != NULL)
		//delete enemy;
}


void Scene::init(bool is_reset)
{
	first_update = true;
	if(!is_reset)initShaders();
	player = new Player();
	map = TileMap::createTileMap("levels/level02test.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	entities = EntityMap::createTileMap("levels/level02teste.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram, map,player);
	background = TileMap::createTileMap("levels/level02testb.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	foreground = TileMap::createTileMap("levels/level02testf.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	
	//enemy = new Enemy();
	gui = new Gui();
	player->init(glm::ivec2(SCREEN_X+16, SCREEN_Y+8), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	//enemy->init(glm::ivec2(SCREEN_X + 16, SCREEN_Y + 8), texProgram, 0);
	//enemy->setPosition(glm::vec2(INIT_ENEMY_X_TILES * map->getTileSize(), INIT_ENEMY_Y_TILES * map->getTileSize()));
	//enemy->setTileMap(map);
	
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	gui->init(player, texProgram);
}

void Scene::update(int deltaTime)
{
	
	//PlaySound(TEXT("sounds/test.wav"), NULL, SND_APPLICATION);
	//mciSendString("open C:\\M0.wav alias MY_SND");
	if (first_update || (int)currentTime % 300000 < 290000){
		mciSendString(TEXT("close menu_song"), NULL, 0, 0);
		mciSendString(TEXT("open sounds/Crypto.wav alias scene_song"), NULL, 0, 0);
		mciSendString(TEXT("play scene_song"), NULL, 0,0);
		first_update = false;
	}
	else mciSendString(TEXT("close scene_song"), NULL, 0, 0);
	//if (totalPlayTime % ) mciSendString(TEXT("stop scene_song"), NULL, 0, 0);
	//if (totalPlayTime > 5000 ) mciSendString(TEXT("play scene_song"), NULL, 0, 0);
	currentTime += deltaTime;
	player->update(deltaTime);
	//enemy->update(deltaTime);
	player->down_key = true;
	entities->update(deltaTime);
	entities->interactEntitiesWithActor(*player);
	int x = player->getPosition().x + 16;
	int y = player->getPosition().y + 16;
	int chunk_x = x / (CHUNK_X_SIZE);
	int chunk_y = y / (CHUNK_Y_SIZE);
	x = chunk_x*(CHUNK_X_SIZE);
	y = chunk_y*(CHUNK_Y_SIZE);
	//DBOUT("positionX: " << x << " " << y << "\n");
	gui->update(deltaTime, glm::vec2(x,y));
	projection = glm::ortho((float)x, x + float(CHUNK_X_SIZE), y + float(CHUNK_Y_SIZE), (float)y);
}

void Scene::render()
{
	glm::mat4 modelview;
	
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	background->render();
	map->render();
	texProgram.free();
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	entities->render();

	player->render();

	texProgram.free();
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	foreground->render();
	gui->render();
	
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}
ShaderProgram& Scene::getProgram(){
	return texProgram;
}


