#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

enum PlayerState {
	STANDING_LEFT, STANDING_RIGHT, RUNING_LEFT, RUNING_RIGHT, WALKING_LEFT, WALKING_RIGHT, JUMPING_LEFT, JUMPING_RIGHT,
	JUMP_STANDING_LEFT, JUMP_STANDING_RIGHT, TURNING_LEFT, TURNING_RIGHT, TURN_RUNING_RIGHT, TURN_RUNNING_LEFT, STOPING_RIGHT, STOPING_LEFT
};

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, RUN_LEFT, RUN_RIGHT, WALK_LEFT, WALK_RIGHT, JUMP_RUN_RIGHT, JUMP_RUN_LEFT, TURN_RIGHT, TURN_LEFT, STOP_RIGHT, STOP_LEFT
};

class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void input();
	void setState(PlayerState newState);
	void setAnimation(PlayerAnims newState);
	glm::vec2 getPosition();
	int health;
	int max_health;
	
private:
	bool bJumping;
	bool right, left, up, down, jump, shift;
	bool facingRight;
	glm::ivec2 tileMapDispl, posPlayer, posStartAnim;
	int jumpAngle, startY, frame;
	PlayerState state;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};


#endif // _PLAYER_INCLUDE


