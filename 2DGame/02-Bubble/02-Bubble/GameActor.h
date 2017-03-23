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
	glm::vec2 size;
	glm::vec2 position_col;
	float magic = 16.0f;
	float speed = 2.0f;
protected:
	
	Sprite *sprite;
};

#endif // _GAME_ACTOR_INCLUDE