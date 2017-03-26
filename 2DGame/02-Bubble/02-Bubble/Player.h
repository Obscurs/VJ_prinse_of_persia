#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "GameActor.h"

// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.

enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, RUN_LEFT, RUN_RIGHT, WALK_LEFT, WALK_RIGHT, JUMP_RUN_RIGHT, JUMP_RUN_LEFT, TURN_RIGHT, TURN_LEFT, STOP_RIGHT, STOP_LEFT,
	DOWN_RIGHT, DOWN_LEFT, JUMP_STAND_RIGHT, JUMP_STAND_LEFT, FALL_RIGHT, FALL_LEFT, TURN_RUN_RIGHT, TURN_RUN_LEFT, PRE_JUMP_RIGHT, PRE_JUMP_LEFT,
	PRE_RUN_RIGHT, PRE_RUN_LEFT, GRAB_RIGHT, GRAB_LEFT, GRAB_LEFT_STATIC, GRAB_RIGHT_STATIC, CLIMB_LEFT, CLIMB_RIGHT, CLIMB_LEFT_DOWN, CLIMB_RIGHT_DOWN,
	SWORD_OUT_RIGHT, SWORD_OUT_LEFT, SWORD_IN_RIGHT, SWORD_IN_LEFT, SWORD_STAND_RIGHT, SWORD_STAND_LEFT, SWORD_ATTACK_RIGHT, SWORD_ATTACK_LEFT,
	PARRY_RIGHT, PARRY_LEFT, SWORD_STEP_RIGHT, SWORD_STEP_LEFT, DRINK_RIGHT, DRINK_LEFT, 

	ANIMATION_COUNT
};

class Player: public GameActor
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
	void DIE();
	glm::vec2 getPosition();
	virtual void drink();
	
private:
	bool bJumping;
	bool right, left, up, down, jump, shift;
	bool facingRight;
	bool is_up;
	glm::ivec2 tileMapDispl, posPlayer, posStartAnim;
	int jumpAngle, startY, frame;
	Texture spritesheet;
	TileMap *map;
};


#endif // _PLAYER_INCLUDE


