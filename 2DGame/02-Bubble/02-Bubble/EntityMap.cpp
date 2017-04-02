#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "EntityMap.h"


using namespace std;


EntityMap *EntityMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program, TileMap *tileMap, Player *pl)
{
	
	EntityMap *map = new EntityMap(levelFile, minCoords, program, tileMap,pl);

	return map;
}


EntityMap::EntityMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program, TileMap *tileMap, Player *pl)
{
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);	//per a fer servir coordenades negatives i fer mirror
	spritesheet.loadFromFile("images/entities.png", TEXTURE_PIXEL_FORMAT_RGBA);
	loadLevel(levelFile, minCoords, program, tileMap,pl);
	//prepareArrays(minCoords, program);
}

EntityMap::~EntityMap()
{
	//if (entities != NULL)
		//delete entities;
}

void EntityMap::update(int deltaTime)
{
	for (int i = 0; i < entities.size(); i++){
		entities[i]->update(deltaTime);
		
	}
	for (int i = 0; i < enemies.size(); i++){
		interactEntitiesWithActor(*enemies[i]);
		enemies[i]->update(deltaTime);

	}
}
void EntityMap::render() const
{
	for (int i = 0; i < entities.size(); i++){
		entities[i]->render();
	}
	for (int i = 0; i < enemies.size(); i++){
		std::cout << enemies[i]->type << " " << std::endl;
		enemies[i]->render();
	}

	
}

void EntityMap::free()
{

}
void EntityMap::interactEntitiesWithActor(GameActor &actor){
	if (actor.alive){
		glm::vec2 actorPos = actor.position_col;
		glm::vec2 actorSize = actor.size;
		for (int i = 0; i < entities.size(); i++){
			if (entities[i]->collides(actorPos, actorSize)) {
				bool destroy = entities[i]->action(actor);
				if (destroy) {
					delete entities[i];
					entities.erase(entities.begin() + i);
				}
			}
		}
	}
}
bool EntityMap::loadLevel(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program, TileMap *tileMap, Player *pl)
{

	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
	//map = new Entity[mapSize.x * mapSize.y];
	
	for (int j = 0; j<mapSize.y; j++)
	{
		for (int i = 0; i<mapSize.x; i++)
		{
			fin.get(tile);
			//if (tile != ' ') map[j*mapSize.x + i].init(minCoords, program, tile - int('0'));
			if (tile != ' ' && tile != '0' && tile != '1' && tile != '2' && tile != '3') {
				Entity *ent = new Entity();
				ent->init(minCoords, glm::ivec2(i *tileSize, j * tileSize), program, spritesheet, tile - int('a') + 1);
				entities.push_back(ent);
			}
			else if (tile != ' ' && tile != '0'){
				Enemy *en = new Enemy();
				en->init(glm::ivec2(minCoords.x+16, minCoords.y+8), program, tile - int('0'),pl);
				en->setPosition(glm::ivec2(i *tileSize, j * tileSize));
				en->setTileMap(tileMap);
				enemies.push_back(en);
			}
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();
	
	return true;
}
































