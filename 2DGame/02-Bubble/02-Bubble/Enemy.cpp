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

	sprite->setNumberAnimations(ANIMATION_COUNT);

	sprite->setAnimationSpeed(STAND_RIGHT, 1);
	sprite->addKeyframe(STAND_RIGHT, glm::vec2(0 * stepX, 0.f));

	sprite->setAnimationSpeed(STAND_LEFT, 1);
	sprite->addKeyframe(STAND_LEFT, glm::vec2(-1 * stepX, 0.f));


	setAnimation(STAND_LEFT);
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