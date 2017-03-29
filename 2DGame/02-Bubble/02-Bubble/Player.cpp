#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include <math.h>  

#define JUMP_ANGLE_STEP 5
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define JUMP 40


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	shift_released = false;
	shift_rel_soon = false;
	is_up = false;
	alive = true;
	float stepX = 1.0f / 15.0f;
	float stepY = 1.0f / 20.0f;
	tileMapDispl = tileMapPos;
	health = 3;
	max_health = 4;
	bJumping = false;
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);	//per a fer servir coordenades negatives i fer mirror
	spritesheet.loadFromFile("images/Prince2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(stepX, stepY), &spritesheet, &shaderProgram);
	
	sprite->setNumberAnimations(ANIMATION_COUNT);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(-1*stepX, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(RUN_LEFT, 15);
		//sprite->addKeyframe(RUN_LEFT, glm::vec2(-1 *stepX, 0.f));
		//sprite->addKeyframe(RUN_LEFT, glm::vec2(-1* stepX, stepY));
		//sprite->addKeyframe(RUN_LEFT, glm::vec2(-2* stepX, stepY));
		//sprite->addKeyframe(RUN_LEFT, glm::vec2(-3* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-4* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-5* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-6* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-7* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-8* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-9* stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-10*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-11*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-12*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-13*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-14*stepX, stepY));

		sprite->setAnimationSpeed(RUN_RIGHT, 15);
		//sprite->addKeyframe(RUN_RIGHT, glm::vec2(0*stepX, stepY));
		//sprite->addKeyframe(RUN_RIGHT, glm::vec2(1*stepX, stepY));
		//sprite->addKeyframe(RUN_RIGHT, glm::vec2(2*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(3*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(4*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(5*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(6*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(7*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(8*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(9*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(10*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(11*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(12*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(13*stepX, stepY));

		sprite->setAnimationSpeed(WALK_RIGHT, 12);
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(0 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(1 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(2 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(3 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(4 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(5 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(6 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(7 * stepX, 3 * stepY));

		sprite->setAnimationSpeed(WALK_LEFT, 12);
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-1 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-2 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-3 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-4 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-5 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-6 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-7 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-8 * stepX, 3 * stepY));

		sprite->setAnimationSpeed(JUMP_RUN_RIGHT, 13);
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(0*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(1*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(2*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(3*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(4*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(5*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(6*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(7*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(8*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(9*stepX, 2*stepY));
		sprite->addKeyframe(JUMP_RUN_RIGHT, glm::vec2(9*stepX, 2*stepY)); //copy

		sprite->setAnimationSpeed(JUMP_RUN_LEFT, 13);
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-1 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-2 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-3 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-4 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-5 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-6 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-7 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-8 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-9 * stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-10 *stepX, 2 * stepY));
		sprite->addKeyframe(JUMP_RUN_LEFT, glm::vec2(-10 *stepX, 2 * stepY)); //copy

		sprite->setAnimationSpeed(TURN_RIGHT, 10);
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(0 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(1 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(2 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(3 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(4 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(4 * stepX, 4 * stepY)); //copy

		sprite->setAnimationSpeed(TURN_LEFT, 10);
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-1 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-2 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-3 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-4 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-5 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-5 * stepX, 4 * stepY)); //copy

		sprite->setAnimationSpeed(STOP_RIGHT, 10);
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(0 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(1 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(2 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(3 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(4 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(5 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_RIGHT, glm::vec2(5 * stepX, 5 * stepY)); //copy

		sprite->setAnimationSpeed(STOP_LEFT, 10);
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-1 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-2 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-3 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-4 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-5 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-6 * stepX, 5 * stepY));
		sprite->addKeyframe(STOP_LEFT, glm::vec2(-6 * stepX, 5 * stepY)); //copy

		sprite->setAnimationSpeed(DOWN_RIGHT, 10);
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(1 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(2 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(3 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(4 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(5 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(6 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(7 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(8 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(9 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(10* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(11* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_RIGHT, glm::vec2(11 * stepX, 0 * stepY)); //copy

		sprite->setAnimationSpeed(DOWN_LEFT, 10);
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-2 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-3 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-4 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-5 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-6 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-7 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-8 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-9 * stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-10* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-11* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-12* stepX, 0 * stepY));
		sprite->addKeyframe(DOWN_LEFT, glm::vec2(-13* stepX, 0 * stepY)); //copy

		sprite->setAnimationSpeed(JUMP_STAND_RIGHT, 5);
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(8 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_RIGHT, glm::vec2(9 * stepX, 8 * stepY));

		sprite->setAnimationSpeed(JUMP_STAND_LEFT, 5);
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-9 * stepX, 8 * stepY));
		sprite->addKeyframe(JUMP_STAND_LEFT, glm::vec2(-10* stepX, 8 * stepY));

		//TODO
		sprite->setAnimationSpeed(FALL_RIGHT, 10);
		sprite->addKeyframe(FALL_RIGHT, glm::vec2(8 * stepX, 8 * stepY));

		sprite->setAnimationSpeed(FALL_LEFT, 10);
		sprite->addKeyframe(FALL_LEFT, glm::vec2(-9 * stepX, 8 * stepY));

		sprite->setAnimationSpeed(TURN_RUN_RIGHT, 12);
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(0 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(1 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(2 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(3 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(4 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(5 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(6 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(7 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(8 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(9 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(10* stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_RIGHT, glm::vec2(10* stepX, 7 * stepY)); //copy

		sprite->setAnimationSpeed(TURN_RUN_LEFT, 12);
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-1 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-2 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-3 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-4 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-5 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-6 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-7 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-8 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-9 * stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-10* stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-11* stepX, 7 * stepY));
		sprite->addKeyframe(TURN_RUN_LEFT, glm::vec2(-12* stepX, 7 * stepY)); //copy

		sprite->setAnimationSpeed(PRE_JUMP_RIGHT, 10);
		sprite->addKeyframe(PRE_JUMP_RIGHT, glm::vec2(0 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT, glm::vec2(1 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT, glm::vec2(2 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT, glm::vec2(3 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT, glm::vec2(4 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT, glm::vec2(5 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT, glm::vec2(6 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT, glm::vec2(7 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT, glm::vec2(7 * stepX, 8 * stepY)); //copy

		sprite->setAnimationSpeed(PRE_JUMP_LEFT, 10);
		sprite->addKeyframe(PRE_JUMP_LEFT, glm::vec2(-1 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT, glm::vec2(-2 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT, glm::vec2(-3 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT, glm::vec2(-4 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT, glm::vec2(-5 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT, glm::vec2(-6 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT, glm::vec2(-7 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT, glm::vec2(-8 * stepX, 8 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT, glm::vec2(-9 * stepX, 8 * stepY)); //copy

		sprite->setAnimationSpeed(PRE_RUN_RIGHT, 12);
		sprite->addKeyframe(PRE_RUN_RIGHT, glm::vec2(0 * stepX, 1 * stepY));
		sprite->addKeyframe(PRE_RUN_RIGHT, glm::vec2(1 * stepX, 1 * stepY));
		sprite->addKeyframe(PRE_RUN_RIGHT, glm::vec2(2 * stepX, 1 * stepY));
		sprite->addKeyframe(PRE_RUN_RIGHT, glm::vec2(2 * stepX, 1 * stepY)); //copy

		sprite->setAnimationSpeed(PRE_RUN_LEFT, 12);
		sprite->addKeyframe(PRE_RUN_LEFT, glm::vec2(-1 * stepX, 1 * stepY));
		sprite->addKeyframe(PRE_RUN_LEFT, glm::vec2(-2 * stepX, 1 * stepY));
		sprite->addKeyframe(PRE_RUN_LEFT, glm::vec2(-3 * stepX, 1 * stepY));
		sprite->addKeyframe(PRE_RUN_LEFT, glm::vec2(-3 * stepX, 1 * stepY)); //copy

		sprite->setAnimationSpeed(GRAB_RIGHT, 6);
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(0 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(1 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(2 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(3 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(4 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(5 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(6 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(7 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(8 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(9 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(10* stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(11* stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(0 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(1 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(0 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_RIGHT, glm::vec2(0 * stepX, 9 * stepY));

		sprite->setAnimationSpeed(GRAB_LEFT, 6);
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-1 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-2 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-3 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-4 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-5 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-6 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-7 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-8 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-9 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-10* stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-11 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-12 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-1 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-2 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-1 * stepX, 9 * stepY));
		sprite->addKeyframe(GRAB_LEFT, glm::vec2(-1 * stepX, 9 * stepY));

		sprite->setAnimationSpeed(GRAB_LEFT_STATIC, 6);
		sprite->addKeyframe(GRAB_LEFT_STATIC, glm::vec2(-1 * stepX, 9 * stepY));

		sprite->setAnimationSpeed(GRAB_RIGHT_STATIC, 6);
		sprite->addKeyframe(GRAB_RIGHT_STATIC, glm::vec2(0 * stepX, 9 * stepY));

		sprite->setAnimationSpeed(CLIMB_RIGHT, 8);
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(0 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(1 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(2 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(3 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(4 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(5 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(6 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(7 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(8 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(9 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(10 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(11 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT, glm::vec2(11 * stepX, 10 * stepY));
		

		sprite->setAnimationSpeed(CLIMB_LEFT, 8);
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-1 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-2 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-3 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-4 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-5 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-6 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-7 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-8 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-9 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-10 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-11 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-12 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT, glm::vec2(-12 * stepX, 10 * stepY));

		sprite->setAnimationSpeed(CLIMB_LEFT_DOWN, 8);
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-12 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-11 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-10 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-8 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-7 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-6 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-5 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-4 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-3 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-2 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-1 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_LEFT_DOWN, glm::vec2(-1 * stepX, 10 * stepY));

		sprite->setAnimationSpeed(CLIMB_RIGHT_DOWN, 8);
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(11 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(10 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(8 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(7 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(6 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(5 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(4 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(3 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(2 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(1 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(0 * stepX, 10 * stepY));
		sprite->addKeyframe(CLIMB_RIGHT_DOWN, glm::vec2(0 * stepX, 10 * stepY));
		
		sprite->setAnimationSpeed(SWORD_OUT_RIGHT, 8);
		sprite->addKeyframe(SWORD_OUT_RIGHT, glm::vec2(0 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_RIGHT, glm::vec2(1 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_RIGHT, glm::vec2(2 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_RIGHT, glm::vec2(3 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_RIGHT, glm::vec2(4 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_RIGHT, glm::vec2(4 * stepX, 11 * stepY)); //copy

		sprite->setAnimationSpeed(SWORD_STAND_RIGHT, 1);
		sprite->addKeyframe(SWORD_STAND_RIGHT, glm::vec2(4 * stepX, 11 * stepY));

		sprite->setAnimationSpeed(SWORD_IN_RIGHT, 8);
		sprite->addKeyframe(SWORD_IN_RIGHT, glm::vec2(0 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_RIGHT, glm::vec2(1 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_RIGHT, glm::vec2(2 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_RIGHT, glm::vec2(3 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_RIGHT, glm::vec2(4 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_RIGHT, glm::vec2(4 * stepX, 14 * stepY)); //copy

		sprite->setAnimationSpeed(SWORD_ATTACK_RIGHT, 9);
		sprite->addKeyframe(SWORD_ATTACK_RIGHT, glm::vec2(0 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_RIGHT, glm::vec2(1 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_RIGHT, glm::vec2(2 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_RIGHT, glm::vec2(3 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_RIGHT, glm::vec2(4 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_RIGHT, glm::vec2(5 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_RIGHT, glm::vec2(6 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_RIGHT, glm::vec2(7 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_RIGHT, glm::vec2(7 * stepX, 12 * stepY)); //copy

		sprite->setAnimationSpeed(PARRY_RIGHT, 9);
		sprite->addKeyframe(PARRY_RIGHT, glm::vec2(0 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_RIGHT, glm::vec2(1 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_RIGHT, glm::vec2(2 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_RIGHT, glm::vec2(3 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_RIGHT, glm::vec2(2 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_RIGHT, glm::vec2(1 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_RIGHT, glm::vec2(0 * stepX, 13 * stepY)); //copy

		sprite->setAnimationSpeed(SWORD_STEP_RIGHT, 8);
		sprite->addKeyframe(SWORD_STEP_RIGHT, glm::vec2(0 * stepX, 13 * stepY));
		sprite->addKeyframe(SWORD_STEP_RIGHT, glm::vec2(4 * stepX, 11 * stepY));
		//
		sprite->setAnimationSpeed(SWORD_OUT_LEFT, 8);
		sprite->addKeyframe(SWORD_OUT_LEFT, glm::vec2(-1 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_LEFT, glm::vec2(-2 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_LEFT, glm::vec2(-3 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_LEFT, glm::vec2(-4 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_LEFT, glm::vec2(-5 * stepX, 11 * stepY));
		sprite->addKeyframe(SWORD_OUT_LEFT, glm::vec2(-5 * stepX, 11 * stepY)); //copy

		sprite->setAnimationSpeed(SWORD_STAND_LEFT, 1);
		sprite->addKeyframe(SWORD_STAND_LEFT, glm::vec2(-5 * stepX, 11 * stepY));

		sprite->setAnimationSpeed(SWORD_IN_LEFT, 8);
		sprite->addKeyframe(SWORD_IN_LEFT, glm::vec2(-1 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_LEFT, glm::vec2(-2 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_LEFT, glm::vec2(-3 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_LEFT, glm::vec2(-4 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_LEFT, glm::vec2(-5 * stepX, 14 * stepY));
		sprite->addKeyframe(SWORD_IN_LEFT, glm::vec2(-5 * stepX, 14 * stepY)); //copy

		sprite->setAnimationSpeed(SWORD_ATTACK_LEFT, 9);
		sprite->addKeyframe(SWORD_ATTACK_LEFT, glm::vec2(-1 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_LEFT, glm::vec2(-2 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_LEFT, glm::vec2(-3 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_LEFT, glm::vec2(-4 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_LEFT, glm::vec2(-5 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_LEFT, glm::vec2(-6 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_LEFT, glm::vec2(-7 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_LEFT, glm::vec2(-8 * stepX, 12 * stepY));
		sprite->addKeyframe(SWORD_ATTACK_LEFT, glm::vec2(-8 * stepX, 12 * stepY)); //copy

		sprite->setAnimationSpeed(PARRY_LEFT, 9);
		sprite->addKeyframe(PARRY_LEFT, glm::vec2(-1 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_LEFT, glm::vec2(-2 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_LEFT, glm::vec2(-3 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_LEFT, glm::vec2(-4 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_LEFT, glm::vec2(-3 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_LEFT, glm::vec2(-2 * stepX, 13 * stepY));
		sprite->addKeyframe(PARRY_LEFT, glm::vec2(-1 * stepX, 13 * stepY)); //copy

		sprite->setAnimationSpeed(SWORD_STEP_LEFT, 8);
		sprite->addKeyframe(SWORD_STEP_LEFT, glm::vec2(-1 * stepX, 13 * stepY));
		sprite->addKeyframe(SWORD_STEP_LEFT, glm::vec2(-5 * stepX, 11 * stepY));

		sprite->setAnimationSpeed(DRINK_RIGHT, 8);
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(0 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(1 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(2 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(3 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(4 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(5 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(6 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(7 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(8 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(9 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(10* stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_RIGHT, glm::vec2(10* stepX, 15 * stepY)); //copy

		sprite->setAnimationSpeed(DRINK_LEFT, 8);
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-1 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-2 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-3 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-4 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-5 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-6 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-7 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-8 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-9 * stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-10* stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-11* stepX, 15 * stepY));
		sprite->addKeyframe(DRINK_LEFT, glm::vec2(-11* stepX, 15 * stepY)); //copy

		sprite->setAnimationSpeed(PRE_JUMP_RIGHT2, 8);
		sprite->addKeyframe(PRE_JUMP_RIGHT2, glm::vec2(0 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT2, glm::vec2(1 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT2, glm::vec2(2 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT2, glm::vec2(3 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT2, glm::vec2(4 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_RIGHT2, glm::vec2(4 * stepX, 6 * stepY)); //copy

		sprite->setAnimationSpeed(PRE_JUMP_LEFT2, 8);
		sprite->addKeyframe(PRE_JUMP_LEFT2, glm::vec2(-1 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT2, glm::vec2(-2 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT2, glm::vec2(-3 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT2, glm::vec2(-4 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT2, glm::vec2(-5 * stepX, 6 * stepY));
		sprite->addKeyframe(PRE_JUMP_LEFT2, glm::vec2(-5 * stepX, 6 * stepY)); //copy

		sprite->setAnimationSpeed(JUMP_RIGHT2, 8);
		sprite->addKeyframe(JUMP_RIGHT2, glm::vec2(5 * stepX, 6 * stepY));
		sprite->addKeyframe(JUMP_RIGHT2, glm::vec2(6 * stepX, 6 * stepY));
		sprite->addKeyframe(JUMP_RIGHT2, glm::vec2(7 * stepX, 6 * stepY));
		sprite->addKeyframe(JUMP_RIGHT2, glm::vec2(8 * stepX, 6 * stepY));
		sprite->addKeyframe(JUMP_RIGHT2, glm::vec2(8 * stepX, 6 * stepY)); //copy

		sprite->setAnimationSpeed(JUMP_LEFT2, 8);
		sprite->addKeyframe(JUMP_LEFT2, glm::vec2(-6 * stepX, 6 * stepY));
		sprite->addKeyframe(JUMP_LEFT2, glm::vec2(-7 * stepX, 6 * stepY));
		sprite->addKeyframe(JUMP_LEFT2, glm::vec2(-8 * stepX, 6 * stepY));
		sprite->addKeyframe(JUMP_LEFT2, glm::vec2(-9 * stepX, 6 * stepY));
		sprite->addKeyframe(JUMP_LEFT2, glm::vec2(-9 * stepX, 6 * stepY)); //copy

		sprite->setAnimationSpeed(POST_JUMP_RIGHT2, 8);
		sprite->addKeyframe(POST_JUMP_RIGHT2, glm::vec2(9  * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_RIGHT2, glm::vec2(10 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_RIGHT2, glm::vec2(11 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_RIGHT2, glm::vec2(12 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_RIGHT2, glm::vec2(13 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_RIGHT2, glm::vec2(14 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_RIGHT2, glm::vec2(14 * stepX, 6 * stepY)); //copy

		sprite->setAnimationSpeed(POST_JUMP_LEFT2, 8);
		sprite->addKeyframe(POST_JUMP_LEFT2, glm::vec2(-10 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_LEFT2, glm::vec2(-11 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_LEFT2, glm::vec2(-12 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_LEFT2, glm::vec2(-13 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_LEFT2, glm::vec2(-14 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_LEFT2, glm::vec2(-15 * stepX, 6 * stepY));
		sprite->addKeyframe(POST_JUMP_LEFT2, glm::vec2(-15 * stepX, 6 * stepY)); //copy
		//END ANIMATIONS

		setAnimation(FALL_RIGHT);
		setState(FALLING_RIGHT);

	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	size = glm::vec2(float(19), float(42));
	position_col = glm::vec2(float(posPlayer.x + 16), float(posPlayer.y  + 16));
	old_position_col = position_col;
}

void Player::update(int deltaTime)
{
	//deltaTime = 50;
	if (alive){
		old_position_col = position_col;
		sprite->update(deltaTime);
		input();
		position_col = glm::vec2(float(posPlayer.x + 24), float(posPlayer.y + 22));
		//std::cout << position_col.x << " " << position_col.y << std::endl;
		switch (state) {
		case STANDING_RIGHT:
			is_up = false;
			if (map->collisionPoint(glm::ivec2(position_col.x+size.x, position_col.y))) {
				position_col.x -= 1;
			}
			else if (!map->collisionMoveDown(glm::ivec2(position_col.x, position_col.y + 5), size, &position_col.y))
			{
				setState(FALLING_RIGHT);
				setAnimation(FALL_RIGHT);
			}
			else if (right && shift) {
				setState(WALKING_RIGHT);
				setAnimation(WALK_RIGHT);
			}
			else if (right) {
				setState(PRE_RUNING_RIGHT);
				setAnimation(PRE_RUN_RIGHT);
			}
			else if (left) {
				setState(TURNING_LEFT);
				setAnimation(TURN_LEFT);
			}
			else if (up && shift) {
				setState(SWORDING_OUT_RIGHT);
				setAnimation(SWORD_OUT_RIGHT);
			}
			else if (up) {
				state = PRE_JUMPING_RIGHT;
				setAnimation(PRE_JUMP_RIGHT);
			}
			else if (down) {
				if (!map->collisionPoint(glm::ivec2(position_col.x, position_col.y+size.y + 5))) {
					setState(CLIMBING_RIGHT_DOWN);
					setAnimation(CLIMB_RIGHT_DOWN);
				}
				else{
					state = DOWNING_RIGHT;
					setAnimation(DOWN_RIGHT);
				}
			}
			break;
		case STANDING_LEFT:
			is_up = false;
			if (map->collisionPoint(glm::ivec2(position_col.x, position_col.y))) {
				position_col.x += 1;
			}
			else if (!map->collisionMoveDown(glm::ivec2(position_col.x, position_col.y + 5), size, &position_col.y))
			{
				setState(FALLING_LEFT);
				setAnimation(FALL_LEFT);
			}
			else if (left && shift) {
				setState(WALKING_LEFT);
				setAnimation(WALK_LEFT);
			}
			else if (left) {
				setState(PRE_RUNING_LEFT);
				setAnimation(PRE_RUN_LEFT);
			}
			else if (right) {
				setState(TURNING_RIGHT);
				setAnimation(TURN_RIGHT);
			}
			else if (up && shift) {
				setState(SWORDING_OUT_LEFT);
				setAnimation(SWORD_OUT_LEFT);
			}
			else if (up) {
				state = PRE_JUMPING_LEFT;
				setAnimation(PRE_JUMP_LEFT);
			}
			else if (down) {
				if (!map->collisionPoint(glm::ivec2(position_col.x + size.x, position_col.y+size.y + 5))) {
					setState(CLIMBING_LEFT_DOWN);
					setAnimation(CLIMB_LEFT_DOWN);
				}
				else{
					state = DOWNING_LEFT;
					setAnimation(DOWN_LEFT);
				}
			}
			break;
		case RUNING_LEFT:
			if (up && position_col.x % 32 == 0 && position_col != posStartAnim) {
				setState(JUMPING_LEFT);
				setAnimation(JUMP_RUN_LEFT);
			}
			else if (position_col.x % 64 == 0 && position_col != posStartAnim && !left) {
				if (right) {
					setState(TURN_RUNING_LEFT);
					setAnimation(TURN_RUN_LEFT);
				}
				else {
					//frenada
					setState(STOPING_LEFT);
					setAnimation(STOP_LEFT);
				}
			}
			else{
				glm::ivec2 new_pos = glm::ivec2(ceil(position_col.x - deltaTime / magic*speed), position_col.y);
				if (!map->collisionMoveDown(glm::ivec2(new_pos.x, position_col.y + 5), size, &position_col.y))
				{
					position_col.x = new_pos.x;
					setState(FALLING_LEFT);
					setAnimation(FALL_LEFT);
				}
				else if (!map->collisionMoveLeft(new_pos, size)){
					if (64 * int(position_col.x / 64) != 64 * int(new_pos.x / 64) && position_col.x % 64 != 0){
						position_col.x = 64 * int(position_col.x / 64);
					}
					else {
						position_col.x = new_pos.x;
					}
				}
				else{
					setState(STANDING_LEFT);
					setAnimation(STAND_LEFT);
				}
			}
			break;
		case RUNING_RIGHT:
			if (up && position_col.x % 32 == 0 && position_col != posStartAnim) {
				setState(JUMPING_RIGHT);
				setAnimation(JUMP_RUN_RIGHT);
			}
			else if (position_col.x % 64 == 0 && position_col != posStartAnim && !right) {
				if (left) {
					setState(TURN_RUNING_RIGHT);
					setAnimation(TURN_RUN_RIGHT);
				}
				else {
					//frenada
					setAnimation(STOP_RIGHT);
					setState(STOPING_RIGHT);
				}
			}
			else{
				glm::ivec2 new_pos = glm::ivec2((position_col.x + deltaTime / magic*speed), position_col.y);
				if (!map->collisionMoveDown(glm::ivec2(new_pos.x, position_col.y + 5), size, &position_col.y))
				{
					position_col.x = new_pos.x;
					setState(FALLING_RIGHT);
					setAnimation(FALL_RIGHT);
				}
				else if (!map->collisionMoveRight(new_pos, size)){
					if (64 * int(position_col.x / 64) != 64 * int(new_pos.x / 64)){

						position_col.x = 64 * int(new_pos.x / 64);
					}
					else {
						position_col.x = new_pos.x;
					}
				}
				else{
					setAnimation(STAND_RIGHT);
					setState(STANDING_RIGHT);
				}
			}
			break;
		case WALKING_RIGHT:
			is_up = false;
			if (position_col.x % 32 == 0 && position_col != posStartAnim && !left) {
				setAnimation(STAND_RIGHT);
				setState(STANDING_RIGHT);
			}
			else{
				glm::ivec2 new_pos = glm::ivec2((position_col.x + deltaTime / magic), position_col.y);
				if (!map->collisionMoveDown(glm::ivec2(new_pos.x + 10, position_col.y + 5), size, &position_col.y))
				{
					//position_col.x = new_pos.x;
					setState(STANDING_RIGHT);
					setAnimation(STAND_RIGHT);
				}
				else if (!map->collisionMoveRight(new_pos, size)){
					if (32 * int(position_col.x / 32) != 32 * int(new_pos.x / 32)){

						position_col.x = 32 * int(new_pos.x / 32);
					}
					else {
						position_col.x = new_pos.x;
					}
				}
				else{
					setAnimation(STAND_RIGHT);
					setState(STANDING_RIGHT);
				}
			}
			break;
		case WALKING_LEFT:
			is_up = false;
			if (position_col.x % 32 == 0 && position_col != posStartAnim && !right) {
				setAnimation(STAND_LEFT);
				setState(STANDING_LEFT);
			}
			else{
				glm::ivec2 new_pos = glm::ivec2(ceil(position_col.x - deltaTime / magic), position_col.y);
				if (!map->collisionMoveDown(glm::ivec2(new_pos.x - 10, position_col.y + 5), size, &position_col.y))
				{
					//position_col.x = new_pos.x;
					setState(STANDING_LEFT);
					setAnimation(STAND_LEFT);
				}
				else  if (!map->collisionMoveLeft(new_pos, size)){
					if (32 * int(position_col.x / 32) != 32 * int(new_pos.x / 32) && position_col.x % 32 != 0){
						position_col.x = 32 * int(position_col.x / 32);
					}
					else {
						position_col.x = new_pos.x;
					}
				}
				else {
					setState(STANDING_LEFT);
					setAnimation(STAND_LEFT);
				}
			}
			break;

		case JUMPING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 10){
				setState(STANDING_RIGHT);
				setAnimation(STAND_RIGHT);
			}
			else {
				glm::ivec2 new_pos = glm::ivec2((position_col.x + deltaTime / magic*speed), position_col.y);
				if (!map->collisionMoveRight(new_pos, size)) {
					if (64 * int(position_col.x / 64) != 64 * int(new_pos.x / 64)) {

						position_col.x = 64 * int(new_pos.x / 64);
					}
					else {
						position_col.x = new_pos.x;
					}
				}
				else {
					setAnimation(STAND_RIGHT);
					setState(STANDING_RIGHT);
				}
			}
			break;
		case JUMPING_LEFT:
			if (sprite->getCurrentKeyframe() >= 10) {
				setState(STANDING_LEFT);
				setAnimation(STAND_LEFT);
			}
			else {
				glm::ivec2 new_pos = glm::ivec2(ceil(position_col.x - deltaTime / magic*speed), position_col.y);
				if (!map->collisionMoveLeft(new_pos, size)) {
					if (64 * int(position_col.x / 64) != 64 * int(new_pos.x / 64) && position_col.x % 64 != 0) {
						position_col.x = 64 * int(position_col.x / 64);
					}
					else {
						position_col.x = new_pos.x;
					}
				}
				else {
					setState(STANDING_LEFT);
					setAnimation(STAND_LEFT);
				}
			}
			break;
		case TURNING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 5) {
				setState(STANDING_RIGHT);
				setAnimation(STAND_RIGHT);
			}
			else {
				frame++;
			}
			break;
		case TURNING_LEFT:
			if (sprite->getCurrentKeyframe() >= 5) {
				setState(STANDING_LEFT);
				setAnimation(STAND_LEFT);
			}
			else {
				frame++;
			}
			break;
		case STOPING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 6) {
				setState(STANDING_RIGHT);
				setAnimation(STAND_RIGHT);
			}
			else {
				frame++;
			}
			break;
		case STOPING_LEFT:
			if (sprite->getCurrentKeyframe() >= 6) {
				setState(STANDING_LEFT);
				setAnimation(STAND_LEFT);
			}
			else {
				frame++;
			}
			break;
		case FALLING_RIGHT:
			//posPlayer.y += FALL_STEP;
			position_col.y = position_col.y + deltaTime / magic*speed*2;
			if (map->collisionPoint(glm::ivec2(position_col.x+size.x, position_col.y))) {
				position_col.x -= 1;
			}
			else if (map->collisionMoveDown(position_col, size, &position_col.y))
			{
				//ajupir
				//posPlayer.y = posPlayer.y - deltaTime / magic*speed * 2;
				setState(DOWNING_RIGHT);
				setAnimation(DOWN_RIGHT);
			}
			else if (shift && !map->collisionPoint(glm::ivec2(old_position_col.x + size.x+2, old_position_col.y)) && map->collisionPoint(glm::ivec2(position_col.x + size.x+2, position_col.y))) {
				setState(GRABING_RIGHT);
				setAnimation(GRAB_RIGHT);
			}
			break;
		case FALLING_LEFT:
			//posPlayer.y += FALL_STEP;
			position_col.y = position_col.y + deltaTime / magic*speed*2;
			if (map->collisionPoint(glm::ivec2(position_col.x, position_col.y))) {
				position_col.x += 1;
			}
			else if (map->collisionMoveDown(position_col, size, &position_col.y)){
				//ajupir
				//posPlayer.y = posPlayer.y - deltaTime / magic*speed * 2;
				setState(DOWNING_LEFT);
				setAnimation(DOWN_LEFT);
			}
			else if (shift && !map->collisionPoint(glm::ivec2(old_position_col.x-2, old_position_col.y)) && map->collisionPoint(glm::ivec2(position_col.x-2, position_col.y))) {
				setState(GRABING_LEFT);
				setAnimation(GRAB_LEFT);
			}
			break;
		case DOWNING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 11) {
				setState(STANDING_RIGHT);
				setAnimation(STAND_RIGHT);
			}
			break;
		case DOWNING_LEFT:
			if (sprite->getCurrentKeyframe() >= 11) {
				setState(STANDING_LEFT);
				setAnimation(STAND_LEFT);
			}
			break;
		case JUMP_STANDING_RIGHT:
			jumpAngle += JUMP_ANGLE_STEP*deltaTime / magic;
			position_col.y = int(posStartAnim.y - JUMP * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				setState(FALLING_RIGHT);
				setAnimation(FALL_RIGHT);
			}
			if (map->collisionMoveDown(position_col, size, &position_col.y)) {
				setState(DOWNING_RIGHT);
				setAnimation(DOWN_RIGHT);
			}
			
			break;
		case JUMP_STANDING_LEFT:
			jumpAngle += JUMP_ANGLE_STEP*deltaTime / magic;
			position_col.y = int(posStartAnim.y - JUMP * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90) {
				setState(FALLING_LEFT);
				setAnimation(FALL_LEFT);
			}
			if (map->collisionMoveDown(position_col, size, &position_col.y)) {
				setState(DOWNING_LEFT);
				setAnimation(DOWN_LEFT);
			}
			
			break;
		case TURN_RUNING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 11) {
				setState(RUNING_LEFT);
				setAnimation(RUN_LEFT);
			}
			break;
		case TURN_RUNING_LEFT:
			if (sprite->getCurrentKeyframe() >= 11) {
				setState(RUNING_RIGHT);
				setAnimation(RUN_RIGHT);
			}
			break;
		case PRE_JUMPING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 8) {
				setState(JUMP_STANDING_RIGHT);
				setAnimation(JUMP_STAND_RIGHT);
			}
			break;
		case PRE_JUMPING_LEFT:
			if (sprite->getCurrentKeyframe() >= 8) {
				setState(JUMP_STANDING_LEFT);
				setAnimation(JUMP_STAND_LEFT);
			}
			break;
		case PRE_RUNING_RIGHT:
			if (up) {
				setState(PRE_JUMPING_RIGHT2);
				setAnimation(PRE_JUMP_RIGHT2);
			}
			else if (sprite->getCurrentKeyframe() >= 3) {
				setState(RUNING_RIGHT);
				setAnimation(RUN_RIGHT);
			}
			break;
		case PRE_RUNING_LEFT:
			if (up) {
				setState(PRE_JUMPING_LEFT2);
				setAnimation(PRE_JUMP_LEFT2);
			}
			else if (sprite->getCurrentKeyframe() >= 3) {
				setState(RUNING_LEFT);
				setAnimation(RUN_LEFT);
			}
			break;
		case GRABING_RIGHT:
			if (!shift) {
				setState(FALLING_RIGHT);
				setAnimation(FALL_RIGHT);
			}
			else if (sprite->getCurrentKeyframe() >= 15)  setAnimation(GRAB_RIGHT_STATIC);
			else if (up){
				setState(CLIMBING_RIGHT);
				setAnimation(CLIMB_RIGHT);
			}
			break;
		case GRABING_LEFT:
			if (!shift) {
				setState(FALLING_LEFT);
				setAnimation(FALL_LEFT);
			}
			else if (sprite->getCurrentKeyframe() >= 15) setAnimation(GRAB_LEFT_STATIC);
			else if (up){
				setState(CLIMBING_LEFT);
				setAnimation(CLIMB_LEFT);
			}
			break;
		case CLIMBING_LEFT:
			if (sprite->getCurrentKeyframe() >= 12){
				setState(WALKING_LEFT);
				setAnimation(WALK_LEFT);
				is_up = false;
			}
			else if (sprite->getCurrentKeyframe() >= 6 && !is_up){
				is_up = true;
				position_col.y -= 45;
				position_col.x -= 4;
			}
			break;
		case CLIMBING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 12){
				setState(WALKING_RIGHT);
				setAnimation(WALK_RIGHT);
				is_up = false;
			}
			else if (sprite->getCurrentKeyframe() >= 6 && !is_up){
				position_col.y -= 45;
				position_col.x += 4;
				is_up = true;
			}
			break;
		case CLIMBING_LEFT_DOWN:
			if (sprite->getCurrentKeyframe() >= 11){
				setState(GRABING_LEFT);
				setAnimation(GRAB_LEFT);
				is_up = false;
			}
			else if (sprite->getCurrentKeyframe() >= 5 && !is_up){
				is_up = true;
				position_col.y += 45;
				position_col.x += 4;
			}
			break;
		case CLIMBING_RIGHT_DOWN:
			if (sprite->getCurrentKeyframe() >= 11){
				setState(GRABING_RIGHT);
				setAnimation(GRAB_RIGHT);
				is_up = false;
			}
			else if (sprite->getCurrentKeyframe() >= 5 && !is_up){
				position_col.y += 45;
				position_col.x -= 4;
				is_up = true;
			}
			break;
		case SWORDING_OUT_RIGHT:
			if (sprite->getCurrentKeyframe() >= 5) {
				setState(SWORD_STANDING_RIGHT);
				setAnimation(SWORD_STAND_RIGHT);
			}
			break;
		case SWORD_STANDING_RIGHT:
			if (shift_released) {
				setState(SWORD_ATTACKING_RIGHT);
				setAnimation(SWORD_ATTACK_RIGHT);
			}
			else if (up) {
				setState(PARRYING_RIGHT);
				setAnimation(PARRY_RIGHT);
			}
			else if (down) {
				setState(SWORDING_IN_RIGHT);
				setAnimation(SWORD_IN_RIGHT);
			}
			else if (right) {	
				setState(SWORD_STEPING_F_RIGHT);
				setAnimation(SWORD_STEP_RIGHT);
			}
			else if (left) {
				setState(SWORD_STEPING_B_RIGHT);
				setAnimation(SWORD_STEP_RIGHT);
			}
			break;
		case SWORDING_IN_RIGHT:
			if(sprite->getCurrentKeyframe() >= 5) {
				setState(STANDING_RIGHT);
				setAnimation(STAND_RIGHT);
			}
			break;
		case SWORD_ATTACKING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 8) {
				setState(SWORD_STANDING_RIGHT);
				setAnimation(SWORD_STAND_RIGHT);
			}
			break;
		case PARRYING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 6) {
				setState(SWORD_STANDING_RIGHT);
				setAnimation(SWORD_STAND_RIGHT);
			}
			break;
		case SWORD_STEPING_F_RIGHT:
			if (!right) {
				setState(SWORD_STANDING_RIGHT);
				setAnimation(SWORD_STAND_RIGHT);
			}
			else {
				glm::ivec2 new_pos = glm::ivec2((position_col.x + deltaTime / magic), position_col.y);
				if (!map->collisionMoveDown(glm::ivec2(new_pos.x + 10, position_col.y + 5), size, &position_col.y))
				{
					setState(STANDING_RIGHT);
					setAnimation(STAND_RIGHT);
				}
				else if (!map->collisionMoveRight(new_pos, size)) {
					position_col.x = new_pos.x;
				}
			}
			break;
		case SWORD_STEPING_B_RIGHT:
			if (!left) {
				setState(SWORD_STANDING_RIGHT);
				setAnimation(SWORD_STAND_RIGHT);
			}
			else {
				glm::ivec2 new_pos = glm::ivec2(ceil(position_col.x - deltaTime / magic), position_col.y);
				if (!map->collisionMoveDown(glm::ivec2(new_pos.x - 10, position_col.y + 5), size, &position_col.y))
				{
					setState(STANDING_RIGHT);
					setAnimation(STAND_RIGHT);
				}
				else if (!map->collisionMoveLeft(new_pos, size)) {
					position_col.x = new_pos.x;
				}
			}
			break;

			/////////////////////////////////CUIDAOOOOO
		case SWORDING_OUT_LEFT:
			if (sprite->getCurrentKeyframe() >= 5) {
				setState(SWORD_STANDING_LEFT);
				setAnimation(SWORD_STAND_LEFT);
			}
			break;
		case SWORD_STANDING_LEFT:
			if (shift) {
				setState(SWORD_ATTACKING_LEFT);
				setAnimation(SWORD_ATTACK_LEFT);
			}
			else if (up) {
				setState(PARRYING_LEFT);
				setAnimation(PARRY_LEFT);
			}
			else if (down) {
				setState(SWORDING_IN_LEFT);
				setAnimation(SWORD_IN_LEFT);
			}
			else if (right) {
				setState(SWORD_STEPING_B_LEFT);
				setAnimation(SWORD_STEP_LEFT);
			}
			else if (left) {
				setState(SWORD_STEPING_F_LEFT);
				setAnimation(SWORD_STEP_LEFT);
			}
			break;
		case SWORDING_IN_LEFT:
			if (sprite->getCurrentKeyframe() >= 5) {
				setState(STANDING_LEFT);
				setAnimation(STAND_LEFT);
			}
			break;
		case SWORD_ATTACKING_LEFT:
			if (sprite->getCurrentKeyframe() >= 8) {
				setState(SWORD_STANDING_LEFT);
				setAnimation(SWORD_STAND_LEFT);
			}
			break;
		case PARRYING_LEFT:
			if (sprite->getCurrentKeyframe() >= 6) {
				setState(SWORD_STANDING_LEFT);
				setAnimation(SWORD_STAND_LEFT);
			}
			break;
		case SWORD_STEPING_F_LEFT:
			if (!left) {
				setState(SWORD_STANDING_LEFT);
				setAnimation(SWORD_STAND_LEFT);
			}
			else {
				glm::ivec2 new_pos = glm::ivec2(ceil(position_col.x - deltaTime / magic), position_col.y);
				if (!map->collisionMoveDown(glm::ivec2(new_pos.x - 10, position_col.y + 5), size, &position_col.y))
				{
					setState(STANDING_LEFT);
					setAnimation(STAND_LEFT);
				}
				else if (!map->collisionMoveLeft(new_pos, size)) {
					position_col.x = new_pos.x;
				}
			}
			break;
		case SWORD_STEPING_B_LEFT:
			if (!right) {
				setState(SWORD_STANDING_LEFT);
				setAnimation(SWORD_STAND_LEFT);
			}
			else {
				glm::ivec2 new_pos = glm::ivec2((position_col.x + deltaTime / magic), position_col.y);
				if (!map->collisionMoveDown(glm::ivec2(new_pos.x + 10, position_col.y + 5), size, &position_col.y))
				{
					setState(STANDING_LEFT);
					setAnimation(STAND_LEFT);
				}
				else if (!map->collisionMoveRight(new_pos, size)) {
					position_col.x = new_pos.x;
				}
			}
			break;
		case DRINKING_RIGHT:
			if (sprite->getCurrentKeyframe() >= 11) {
				setState(STANDING_RIGHT);
				setAnimation(STAND_RIGHT);
			}
			break;
		case DRINKING_LEFT:
			if (sprite->getCurrentKeyframe() >= 11) {
				setState(STANDING_LEFT);
				setAnimation(STAND_LEFT);
			}
			break;
		case PRE_JUMPING_RIGHT2:
			if (sprite->getCurrentKeyframe() >= 5) {
				setState(JUMPING_RIGHT2);
				setAnimation(JUMP_RIGHT2);
			}
			break;
		case PRE_JUMPING_LEFT2:
			if (sprite->getCurrentKeyframe() >= 5) {
				setState(JUMPING_LEFT2);
				setAnimation(JUMP_LEFT2);
			}
			break;
		case JUMPING_RIGHT2:
			if (sprite->getCurrentKeyframe() >= 4) {
				setState(POST_JUMPING_RIGHT2);
				setAnimation(POST_JUMP_RIGHT2);
			}
			else {
				glm::ivec2 new_pos = glm::ivec2((position_col.x + deltaTime / magic*speed), position_col.y);
				if (!map->collisionMoveRight(new_pos, size)) {
					if (64 * int(position_col.x / 64) != 64 * int(new_pos.x / 64)) {

						position_col.x = 64 * int(new_pos.x / 64);
					}
					else {
						position_col.x = new_pos.x;
					}
				}
				else {
					setState(STANDING_RIGHT);
					setAnimation(STAND_RIGHT);
				}
			}
			break;
		case JUMPING_LEFT2:
			if (sprite->getCurrentKeyframe() >= 4) {
				setState(POST_JUMPING_LEFT2);
				setAnimation(POST_JUMP_LEFT2);
			}
			else {
				glm::ivec2 new_pos = glm::ivec2(ceil(position_col.x - deltaTime / magic*speed), position_col.y);
				if (!map->collisionMoveLeft(new_pos, size)) {
					if (64 * int(position_col.x / 64) != 64 * int(new_pos.x / 64) && position_col.x % 64 != 0) {
						position_col.x = 64 * int(position_col.x / 64);
					}
					else {
						position_col.x = new_pos.x;
					}
				}
				else {
					setState(STANDING_LEFT);
					setAnimation(STAND_LEFT);
				}
			}
			break;
		case POST_JUMPING_RIGHT2:
			if (!map->collisionMoveDown(glm::ivec2(position_col.x, position_col.y + 5), size, &position_col.y)){
				setState(FALLING_RIGHT);
				setAnimation(FALL_RIGHT);
			}
			else if (sprite->getCurrentKeyframe() >= 6) {
				setState(STANDING_RIGHT);
				setAnimation(STAND_RIGHT);
			}
			break;
		case POST_JUMPING_LEFT2:
			if (!map->collisionMoveDown(glm::ivec2(position_col.x, position_col.y + 5), size, &position_col.y)){
				setState(FALLING_LEFT);
				setAnimation(FALL_LEFT);
			}
			else if (sprite->getCurrentKeyframe() >= 6) {
				setState(STANDING_LEFT);
				setAnimation(STAND_LEFT);
			}
			break;
			//end switch
		}
		posPlayer = glm::vec2(float(position_col.x - 24), float(position_col.y - 22));
		sprite->setPosition(glm::vec2(float(posPlayer.x + tileMapDispl.x), float(posPlayer.y + tileMapDispl.y)));
		//position_col = glm::vec2(float(posPlayer.x + tileMapDispl.x + 24), float(posPlayer.y + tileMapDispl.y + 22));
		//std::cout << "player " << posPlayer.x << " " << posPlayer.y << " to " << posPlayer.x + 64 << " " << posPlayer.y + 64 << std::endl;
		//std::cout << "player " << position_col.x << " " << position_col.y << " to " << position_col.x + size.x << " " << position_col.y + size.y << std::endl;
	}
}

void Player::render()
{
	if(alive)sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	position_col = glm::vec2(float(posPlayer.x + 24), float(posPlayer.y + 22));
	//std::cout << "player " << posPlayer.x << " " << posPlayer.y << " to " << position_col.x + size.x << " " << position_col.y + size.y << std::endl;
	//std::cout << "player " << position_col.x << " " << position_col.y << " to " << position_col.x + size.x << " " << position_col.y + size.y << std::endl;
	//std::cout << position_col.x << " " << position_col.y << std::endl;
}

glm::vec2 Player::getPosition()
{
	return position_col;
}

void Player::input() {
	left = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	right = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	up = Game::instance().getSpecialKey(GLUT_KEY_UP);
	down = down_key = Game::instance().getSpecialKey(GLUT_KEY_DOWN);
	shift = Game::instance().getSpecialKey(112);

	if (shift && !shift_released){
		shift_rel_soon = true;
	}
	else if (!shift && shift_rel_soon) {
		shift_rel_soon = false;
		shift_released = true;
	}
	else shift_released = false;
}

void Player::setState(PlayerState newState) {
	state = newState;
}

void Player::setAnimation(PlayerAnims newAnim) {
	sprite->changeAnimation(newAnim);
	posStartAnim = position_col;
	jumpAngle = 0;
	frame = 0;
}

void Player::DIE() {
	//TODO
}

void Player::drink() {
	cout << "Drinking!" << endl;
	if (state == DOWNING_RIGHT) {
		setState(DRINKING_RIGHT);
		setAnimation(DRINK_RIGHT);
	}
	else if (state == DOWNING_LEFT) {
		setState(DRINKING_LEFT);
		setAnimation(DRINK_LEFT);
	}
}

