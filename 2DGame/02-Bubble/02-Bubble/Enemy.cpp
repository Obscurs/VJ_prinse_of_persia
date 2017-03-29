#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	alive = true;
	float stepX = 1.0f / 8.0f; //CHECK
	float stepY = 1.0f / 8.0f;
	tileMapDispl = tileMapPos;
	health = 3;
	max_health = 4;
	spritesheet.setWrapS(GL_MIRRORED_REPEAT);	//per a fer servir coordenades negatives i fer mirror
	spritesheet.loadFromFile("images/Enemy.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMagFilter(GL_NEAREST);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(stepX, stepY), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(eANIMATION_COUNT);

	sprite->setAnimationSpeed(eSTAND_RIGHT, 1);
	sprite->addKeyframe(eSTAND_RIGHT, glm::vec2(0 * stepX, 0 * stepY));

	sprite->setAnimationSpeed(eSTAND_LEFT, 1);
	sprite->addKeyframe(eSTAND_LEFT, glm::vec2(-1 * stepX, 0 * stepY));

	sprite->setAnimationSpeed(eWALK_RIGHT, 8);
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(0 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(1 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(2 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(3 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(4 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_RIGHT, glm::vec2(5 * stepX, 1 * stepY));

	sprite->setAnimationSpeed(eWALK_LEFT, 8);
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-1 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-2 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-3 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-4 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-5 * stepX, 1 * stepY));
	sprite->addKeyframe(eWALK_LEFT, glm::vec2(-6 * stepX, 1 * stepY));

	sprite->setAnimationSpeed(eATACK_RIGHT, 7);
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(0 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(1 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(2 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_RIGHT, glm::vec2(3 * stepX, 2 * stepY));

	sprite->setAnimationSpeed(eATACK_LEFT, 7);
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-1 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-2 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-3 * stepX, 2 * stepY));
	sprite->addKeyframe(eATACK_LEFT, glm::vec2(-4 * stepX, 2 * stepY));

	sprite->setAnimationSpeed(eDIE_RIGHT, 7);
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(2 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(3 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(4 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(5 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_RIGHT, glm::vec2(6 * stepX, 4 * stepY));

	sprite->setAnimationSpeed(eDIE_LEFT, 7);
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-3 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-4 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-5 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-6 * stepX, 4 * stepY));
	sprite->addKeyframe(eDIE_LEFT, glm::vec2(-7 * stepX, 4 * stepY));

	sprite->setAnimationSpeed(eDAMAGE_RIGHT, 6);
	sprite->addKeyframe(eDAMAGE_RIGHT, glm::vec2(0 * stepX, 4 * stepY));
	sprite->addKeyframe(eDAMAGE_RIGHT, glm::vec2(1 * stepX, 4 * stepY));
	sprite->addKeyframe(eDAMAGE_RIGHT, glm::vec2(1 * stepX, 4 * stepY)); //copy

	sprite->setAnimationSpeed(eDAMAGE_LEFT, 6);
	sprite->addKeyframe(eDAMAGE_LEFT, glm::vec2(-1 * stepX, 4 * stepY));
	sprite->addKeyframe(eDAMAGE_LEFT, glm::vec2(-2 * stepX, 4 * stepY));
	sprite->addKeyframe(eDAMAGE_LEFT, glm::vec2(-2 * stepX, 4 * stepY)); //copy

	//sprite->addKeyframe(eATACK_RIGHT, glm::vec2(6 * stepX, 1 * stepY)); //maybe parry?

	setAnimation(eSTAND_LEFT);
	setState(STANDING_LEFT);

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	size = glm::vec2(float(19), float(42));
	position_col = glm::vec2(float(posPlayer.x + 16), float(posPlayer.y + 16));
	old_position_col = position_col;
}

void Enemy::update(int deltaTime)
{
	//deltaTime = 50;
	if (alive) {
		//...
		sprite->update(deltaTime);

		posPlayer = glm::vec2(float(position_col.x - 24), float(position_col.y - 22));
		sprite->setPosition(glm::vec2(float(posPlayer.x + tileMapDispl.x), float(posPlayer.y + tileMapDispl.y)));
	}
}


void Enemy::render()
{
	if (alive)sprite->render();
}

void Enemy::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(posPlayer.x), float(posPlayer.y)));
	position_col = glm::vec2(float(posPlayer.x + 24), float(posPlayer.y + 22));
}

glm::vec2 Enemy::getPosition()
{
	return position_col;
}

void Enemy::setState(PlayerState newState) {
	state = newState;
}

void Enemy::setAnimation(EnemyAnims newAnim) {
	sprite->changeAnimation(newAnim);
}

void Enemy::DIE() {
	//TODO
}