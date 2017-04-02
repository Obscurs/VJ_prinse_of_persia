#pragma once
#include "GameActor.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
enum EnemyAnims {
	eSTAND_LEFT, eSTAND_RIGHT, ePARRY_LEFT, ePARRY_RIGHT, eATACK_RIGHT, eATACK_LEFT, eWALK_RIGHT, eWALK_LEFT, eDIE_RIGHT, eDIE_LEFT, eDAMAGE_RIGHT, eDAMAGE_LEFT,
	eANIMATION_COUNT
};

class Enemy :public GameActor
{
public:
	Enemy();
	~Enemy();

	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int tp, Player *pl);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setState(PlayerState newState);
	void setAnimation(EnemyAnims newAnim);
	void DIE();
	glm::vec2 getPosition();
	
	int timer;
	void damage(bool direction, int dmg);
private:
	bool wait;
	int eye_distance;
	int close_distance;
	bool canSeePlayer();
	bool playerClose();
	bool playerDirection();
	bool direction;
	void newDecision();
	int old_frame;
	glm::ivec2 tileMapDispl, posPlayer, posStartAnim;
	Texture spritesheet;
	TileMap *map;
	Player *player;

};

