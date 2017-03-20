#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define STEP 32;


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	state = STANDING_RIGHT;

	float stepX = 1.0f / 15.0f;
	float stepY = 1.0f / 20.0f;

	health = 3;
	max_health = 4;
	bJumping = false;
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);	//per a fer servir coordenades negatives i fer mirror
	//spritesheet.loadFromFile("images/prince-sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.loadFromFile("images/Prince.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(stepX, stepY), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(10);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(-1*stepX, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(RUN_LEFT, 10);
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-1 * stepX, 0.f));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-1*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-2*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-3*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-4*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-5*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-6*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-7*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-8*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-9*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-10*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-11*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-12*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-13*stepX, stepY));
		sprite->addKeyframe(RUN_LEFT, glm::vec2(-14*stepX, stepY));

		sprite->setAnimationSpeed(RUN_RIGHT, 10);
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(0*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(1*stepX, stepY));
		sprite->addKeyframe(RUN_RIGHT, glm::vec2(2*stepX, stepY));
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

		sprite->setAnimationSpeed(WALK_RIGHT, 10);
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(0 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(1 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(2 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(3 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(4 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(5 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(6 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_RIGHT, glm::vec2(7 * stepX, 3 * stepY));

		sprite->setAnimationSpeed(WALK_LEFT, 10);
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-1 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-2 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-3 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-4 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-5 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-6 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-7 * stepX, 3 * stepY));
		sprite->addKeyframe(WALK_LEFT, glm::vec2(-8 * stepX, 3 * stepY));


		sprite->setAnimationSpeed(JUMP_RUN_RIGHT, 6);
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
		
		sprite->setAnimationSpeed(JUMP_RUN_LEFT, 6);
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

		sprite->setAnimationSpeed(TURN_RIGHT, 10);
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(0 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(1 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(2 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(3 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_RIGHT, glm::vec2(4 * stepX, 4 * stepY));

		sprite->setAnimationSpeed(TURN_LEFT, 10);
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-1 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-2 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-3 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-4 * stepX, 4 * stepY));
		sprite->addKeyframe(TURN_LEFT, glm::vec2(-5 * stepX, 4 * stepY));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	input();

	switch (state) {
	case STANDING_RIGHT:
		if (right) {
			setState(WALKING_RIGHT);
			setAnimation(WALK_RIGHT);
		}
		if (left) {
			setState(TURNING_LEFT);
			setAnimation(TURN_LEFT);
		}
		if (up) {
			state = JUMPING_RIGHT;
			setAnimation(JUMP_RUN_RIGHT);
		}
		break;
	case STANDING_LEFT:
		if (left) {
			setState(RUNING_LEFT);
			setAnimation(RUN_LEFT);
		}
		if (right) {
			setState(TURNING_RIGHT);
			setAnimation(TURN_RIGHT);
		}
		break;
	case RUNING_LEFT:
		if (right) {
			setState(STANDING_RIGHT);
			setAnimation(STAND_RIGHT);
		}
		if (up) {
			setState(JUMPING_LEFT);
			setAnimation(JUMP_RUN_LEFT);
		}
		else if (posPlayer.x % 64 == 0 && posPlayer != posStartAnim && !left) {
			setState(STANDING_LEFT);
			setAnimation(STAND_LEFT);
		}
		else {
			posPlayer.x -= 1;
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 64))) {
				posPlayer.x += 1;
				setState(STANDING_LEFT);
				setAnimation(STAND_LEFT);
			}
		}
		break;
	case RUNING_RIGHT:
		if (left) {
			setState(STANDING_LEFT);
			setAnimation(STAND_LEFT);
		}
		if (up) {
			setState(JUMPING_RIGHT);
			setAnimation(JUMP_RUN_RIGHT);
		}
		else if (posPlayer.x % 64 == 0 && posPlayer != posStartAnim && !right) {
			//frenada
			setAnimation(STAND_RIGHT);
			setState(STANDING_RIGHT);
		}
		else {
			posPlayer.x += 1;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 64)))
			{
				posPlayer.x -= 1;
				setAnimation(STAND_RIGHT);
				setState(STANDING_RIGHT);
			}
		}
		break;
	case WALKING_RIGHT:
		if (left) {
			setState(STANDING_LEFT);
			setAnimation(STAND_LEFT);
		}
		if (up) {
			setState(JUMPING_RIGHT);
			setAnimation(JUMP_RUN_RIGHT);
		}
		else if (posPlayer.x % 32 == 0 && posPlayer != posStartAnim && !right) {
			//frenada
			setAnimation(STAND_RIGHT);
			setState(STANDING_RIGHT);
		}
		else {
			posPlayer.x += 1;
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 64)))
			{
				posPlayer.x -= 1;
				setAnimation(STAND_RIGHT);
				setState(STANDING_RIGHT);
			}
		}
		break;
	case JUMPING_RIGHT:
		if (right) {
			setState(STANDING_RIGHT);
			setAnimation(STAND_RIGHT);
		}
		break;
	case JUMPING_LEFT:
		if (left) {
			setState(STANDING_LEFT);
			setAnimation(STAND_LEFT);
		}
		break;
	case TURNING_RIGHT:
		if (frame == 25) {
			setState(STANDING_RIGHT);
			setAnimation(STAND_RIGHT);
		}
		else {
			frame++;
		}
		break;
	case TURNING_LEFT:
		if (frame == 25) {
			setState(STANDING_LEFT);
			setAnimation(STAND_LEFT);
		}
		else {
			frame++;
		}
		break;
	}


	//YOLO
	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				if (bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)) {
					if (facingRight) sprite->changeAnimation(STAND_RIGHT);
					else sprite->changeAnimation(STAND_LEFT);
				}

		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y))
		{
			if (up)
			{
				if (sprite->animation() != JUMP_RUN_RIGHT) sprite->changeAnimation(JUMP_RUN_RIGHT);
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}

	/*
	if(left)
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(32, 64))){
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(right)
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 64)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				if (bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y)) {
					if(facingRight) sprite->changeAnimation(STAND_RIGHT);
					else sprite->changeAnimation(STAND_LEFT);
				}

		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 64), &posPlayer.y))
		{
			if(up)
			{
				if (sprite->animation() != JUMP_RUNNING_RIGHT) sprite->changeAnimation(JUMP_RUNNING_RIGHT);
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}*/
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::vec2 Player::getPosition()
{
	return posPlayer;
}

void Player::input() {
	left = Game::instance().getSpecialKey(GLUT_KEY_LEFT);
	right = Game::instance().getSpecialKey(GLUT_KEY_RIGHT);
	up = Game::instance().getSpecialKey(GLUT_KEY_UP);
	down = Game::instance().getSpecialKey(GLUT_KEY_DOWN);
	//shift = left = Game::instance().getSpecialKey(..);
}

void Player::setState(PlayerState newState) {
	state = newState;
}

void Player::setAnimation(PlayerAnims newAnim) {
	sprite->changeAnimation(newAnim);
	posStartAnim = posPlayer;
	frame = 0;
}



