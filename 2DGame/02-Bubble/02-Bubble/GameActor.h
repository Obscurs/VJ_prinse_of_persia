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
protected:
	
	Sprite *sprite;
};

#endif // _GAME_ACTOR_INCLUDE