#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Entity.h"
#include "Game.h"
#include <MMSystem.h>


enum Animations
{
	ANIM1, ANIM2
};

Entity::Entity()
{
	type = 0;
}


Entity::~Entity()
{
}
void Entity::init(const glm::ivec2 &tileMapPos, glm::ivec2 &pos, ShaderProgram &shaderProgram, Texture &spritesheet, int tp )
{
	//tileMapDispl = tileMapPos;
	tileMapDispl = glm::vec2(0,0);
	position = pos;
	position = glm::vec2(float(position.x), float(position.y));
	type = tp;
	actived = true;
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);		//el 46 es superhardcoded
	sprite->setPosition(position);
	sound_playing = false;
	
	
	
	if (type == 1){
		sprite->setNumberAnimations(2);
		sprite->setAnimationSpeed(ANIM1, 8);
		sprite->addKeyframe(ANIM2, glm::vec2(0.75f, 0.f));

		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.25f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.25f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.f));

		position = glm::vec2(position.x-3, position.y+8);
		sprite->setPosition(position);
		col_position = glm::vec2(position.x+8, position.y+16);
		col_size = glm::vec2(24, 32);
		actived = false;

	}
	else if (type == 2){
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(ANIM1, 8);
		sprite->setAnimationSpeed(ANIM1, 8);
		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.25f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.25f));
		position = glm::vec2(position.x, position.y - 16);
		sprite->setPosition(position);
		col_position = glm::vec2(position.x + 16, position.y + 20);
		col_size = glm::vec2(32, 26);
	}
	else if (type == 3){
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(ANIM1, 8);
		position = glm::vec2(position.x - 4, position.y - 12);
		sprite->setPosition(position);
		sprite->addKeyframe(ANIM1, glm::vec2(0.f, 0.5f));
		col_position = glm::vec2(position.x + 20, position.y + 22);
		col_size = glm::vec2(8, 8);
	}
	else if (type == 4){
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(ANIM1, 8);
		position = glm::vec2(position.x - 4, position.y - 12);
		sprite->setPosition(position);
		sprite->addKeyframe(ANIM1, glm::vec2(0.25f, 0.5f));
		col_position = glm::vec2(position.x + 20, position.y + 22);
		col_size = glm::vec2(8, 8);
	}
	else if (type == 5){
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(ANIM1, 8);
		position = glm::vec2(position.x-4, position.y-12);
		sprite->setPosition(position);
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.5f));
		col_position = glm::vec2(position.x + 20, position.y + 22);
		col_size = glm::vec2(8, 8);
		

	}
	else if (type == 6){
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(ANIM1, 8);
		position = glm::vec2(position.x + 3, position.y-32);
		sprite->setPosition(position);
		sprite->addKeyframe(ANIM1, glm::vec2(0.0f, 0.75f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.25f, 0.75f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.5f, 0.75f));
		sprite->addKeyframe(ANIM1, glm::vec2(0.75f, 0.75f));
		col_position = glm::vec2(position.x + 16, position.y);
		col_size = glm::vec2(32, 14);
	}
	sprite->changeAnimation(ANIM1);
}

void Entity::update(int deltaTime)
{
	if(actived) sprite->update(deltaTime);
	if (type == 1 && actived){
		if (sprite->getCurrentKeyframe() >= 9){
			actived = false;
			sprite->changeAnimation(ANIM1);
			//mciSendString(TEXT("stop spike"), NULL, 0, 0);
			sound_playing = false;
		}
	}
	
}

void Entity::render()
{
	
	sprite->render();
}
bool Entity::action(GameActor &actor){
	if (actor.alive){
		//spikes
		if (type == 1){
			actived = true;
			if (!sound_playing && sprite->getCurrentKeyframe() >= 2){
				PlaySound(TEXT("sounds/spike"), NULL, SND_ASYNC);
				sound_playing = true;
			}
			if (sprite->getCurrentKeyframe() >= 4 && actor.state == RUNING_RIGHT || actor.state == RUNING_LEFT){
				actor.health = 0;
				actor.alive = false;
				sprite->changeAnimation(ANIM2);
				actived = false;	
			}
			

		}//saw
		else if (type == 2){
			if (actor.health > 0 && sprite->getCurrentKeyframe() < 2){
				actor.health = 0;
				actor.alive = false;
			}
		}//potion1
		else if (type == 3){
			if (actor.state == DOWNING_LEFT || actor.state == DOWNING_RIGHT){
				actor.drink();
				if (actor.health < actor.max_health) actor.health++;
				return true;
			}
		}//potion2
		else if (type == 4){
			if (actor.state == DOWNING_LEFT || actor.state == DOWNING_RIGHT){
				actor.drink();
				actor.max_health++;
				return true;
			}
		}//potion3
		else if (type == 5){
			if (actor.state == DOWNING_LEFT || actor.state == DOWNING_RIGHT){
				actor.drink();
				if (actor.health > 0) actor.health--;
				return true;
			}
		}
	}
	return false;
}
bool Entity::overlapping1D(glm::vec2 box1, glm::vec2 box2){
	return (box1.y >= box2.x && box2.y >= box1.x);
}
bool Entity::collides(glm::vec2 pos, glm::vec2 size){

	return (overlapping1D(glm::vec2(pos.x, pos.x + size.x), glm::vec2(col_position.x, col_position.x + col_size.x)) 
		&& overlapping1D(glm::vec2(pos.y, pos.y + size.y), glm::vec2(col_position.y, col_position.y + col_size.y)));
}





