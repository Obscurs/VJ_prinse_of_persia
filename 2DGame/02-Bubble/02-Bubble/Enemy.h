#pragma once
#include "GameActor.h"
#include "Sprite.h"
#include "TileMap.h"

enum EnemyAnims {
	STAND_LEFT, STAND_RIGHT,
	ANIMATION_COUNT
};

class Enemy :public GameActor
{
public:
	Enemy();
	~Enemy();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setState(PlayerState newState);
	void setAnimation(EnemyAnims newAnim);
	void DIE();
	glm::vec2 getPosition();
private:
	glm::ivec2 tileMapDispl, posPlayer, posStartAnim;
	Texture spritesheet;
	TileMap *map;

};

