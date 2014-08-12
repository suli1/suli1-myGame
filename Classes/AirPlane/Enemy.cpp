#include "Enemy.h"

Enemy::Enemy()
{
	_sprite = nullptr;
	_life = 0;
}

Enemy::~Enemy()
{

}


Enemy* Enemy::create()
{
	Enemy* pRet = new Enemy();
	pRet->autorelease();

	return pRet;
}

void Enemy::bindSprite(Sprite* sprite, int life)
{
	_sprite = sprite;
	_life = life;
	this->addChild(_sprite);
}

int Enemy::getLife()
{
	return _life;
}

void Enemy::loseLife()
{
	--_life;
}

Rect Enemy::getBoundingBox()
{
	Rect rect = _sprite->getBoundingBox();
	auto pos = this->convertToWorldSpace(rect.origin);
	Rect enemyRect(pos.x, pos.y, rect.size.width, rect.size.width);

	return enemyRect;
}