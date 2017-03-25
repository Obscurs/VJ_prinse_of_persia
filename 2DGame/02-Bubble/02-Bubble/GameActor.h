#ifndef _GAME_ACTOR_INCLUDE
#define _GAME_ACTOR_INCLUDE
#include "Sprite.h"
class GameActor
{
public:
	Sprite* getSprite();
	int health;
	int max_health;
	bool down_key;
	glm::ivec2 size;
	glm::ivec2 position_col;
	glm::ivec2 old_position_col;
	float magic = 16.0f;
	float speed = 2.0f;
	bool alive;
protected:
	
	Sprite *sprite;
};

#endif // _GAME_ACTOR_INCLUDE