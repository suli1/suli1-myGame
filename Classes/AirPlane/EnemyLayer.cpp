#include "EnemyLayer.h"
#include "GameLayer_Plane.h"
#include "SimpleAudioEngine.h"

EnemyLayer::EnemyLayer()
	: _enemy1SpriteFrame(nullptr)
	, _enemy2SpriteFrame(nullptr)
	, _enemy3SpriteFrame_1(nullptr)
	, _enemy3SpriteFrame_2(nullptr)
{

}

bool EnemyLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		_enemy1SpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1.png");
		_enemy2SpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2.png");
		_enemy3SpriteFrame_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png");
		_enemy3SpriteFrame_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png");

		// 创建敌机帧动画

		auto animation1 = Animation::create();
		animation1->setDelayPerUnit(0.1f);
		animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
		animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
		animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
		animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));

		auto animation2 = Animation::create();
		animation2->setDelayPerUnit(0.1f);
		animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
		animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
		animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
		animation2->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));

		auto animation3 = Animation::create();
		animation3->setDelayPerUnit(0.1f);
		animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png"));
		animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png"));
		animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png"));
		animation3->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png"));

		// 保存动画到动画缓存池
		AnimationCache::getInstance()->addAnimation(animation1, "Enemy1Blowup");
		AnimationCache::getInstance()->addAnimation(animation2, "Enemy2Blowup");
		AnimationCache::getInstance()->addAnimation(animation3, "Enemy3Blowup");


		bRet = true;
	} while (0);

	return bRet;
}

void EnemyLayer::addEnemy1(float dt)
{
	// bind enemy1
	Enemy* enemy1 = Enemy::create();
	enemy1->bindSprite(Sprite::createWithSpriteFrame(_enemy1SpriteFrame), ENEMY1_MAXLIFE);


	// random position to enemy1
	Size enemy1Size = enemy1->getSprite()->getContentSize();
	Size winSize = Director::getInstance()->getWinSize();
	int minX = enemy1Size.width/2;
	int maxX = winSize.width - enemy1Size.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) +minX;

	enemy1->setPosition(actualX, winSize.height +enemy1Size.height/2);
	this->addChild(enemy1);
	_vAllEnemy1.pushBack(enemy1);

	// speed
	float minDuration = 2.0f, maxDuration = 10.0f;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand()%rangeDuration) + minDuration;

	auto actionMove = MoveTo::create(actualDuration, Vec2(actualX, 0 - enemy1->getSprite()->getContentSize().height/2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy1MoveFinished, this));

	auto sequence = Sequence::create(actionMove, actionDone, nullptr);
	enemy1->runAction(sequence);
}

void EnemyLayer::enemy1MoveFinished(Node* pSender)
{

}


// 敌机爆炸
void EnemyLayer::enemy1Blowup(Enemy* enemy1)
{
	auto animation = AnimationCache::getInstance()->getAnimation("Enemy1Blowup");		// 动画事先加入动画池
	auto animate = Animate::create(animation);
	auto removeEnemy1 = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeEnemy1, this, enemy1));
	auto sequence = Sequence::create(animate, removeEnemy1);

	enemy1->getSprite()->runAction(sequence);		// 运动爆炸动画，并回收
}

void EnemyLayer::removeEnemy1(Node* pTarget)
{
	auto enemy1 = (Enemy*)pTarget;
	if(enemy1) {
		auto iter = _vAllEnemy1.find(enemy1);
		if(iter != _vAllEnemy1.end()) {
			_vAllEnemy1.erase(iter);
			this->removeChild(enemy1, true);
		}
	}

}


void EnemyLayer::removeAllEnemy1()
{
	for(auto iter : _vAllEnemy1 ) {
		Enemy* enemy1 = (Enemy*)iter;
		if(enemy1->getLife() > 0) {
			enemy1Blowup(enemy1);
		}
	}

}



void EnemyLayer::addEnemy2(float dt)
{
	auto enemy2 = Enemy::create();
	enemy2->bindSprite(Sprite::createWithSpriteFrame(_enemy2SpriteFrame), ENEMY2_MAXLIFE);

	auto enemy2Size = enemy2->getSprite()->getContentSize();
	auto winSize = Director::getInstance()->getWinSize();
	int minX = enemy2Size.width/2;
	int maxX = winSize.width - enemy2Size.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) + minX;

	enemy2->setPosition(actualX, winSize.height + enemy2Size.height/2);
	this->addChild(enemy2);
	_vAllEnemy2.pushBack(enemy2);

	float minDuration, maxDuration;

	switch(airplane::GameLayer::getCurLevel())
	{
	case EASY:
		minDuration = 3.0f;
		maxDuration = 6.0f;
		break;
	case MIDDLE:
		minDuration = 2.7f;
		maxDuration = 5.4f;
		break;
	case HARD:
		minDuration = 2.5f;
		maxDuration = 5.0f;
		break;
	default:
		minDuration = 3.0f;
		maxDuration = 6.0f;
		break;
	}

	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand()%rangeDuration) + minDuration;

	auto actionMove = MoveTo::create(actualDuration, Point(actualX, 0 - enemy2->getSprite()->getContentSize().height/2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy2MoveFinished, this));

	auto sequence = Sequence::create(actionMove, actionDone, nullptr);
	enemy2->runAction(sequence);

}

void EnemyLayer::enemy2MoveFinished(Node* pSender)
{
	auto enemy2 = (Enemy*)pSender;
	this->removeChild(enemy2, true);
	_vAllEnemy2.eraseObject(enemy2);
}

void EnemyLayer::enemy2Blowup(Enemy* enemy2)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy2_down.mp3");
	auto animation = AnimationCache::getInstance()->getAnimation("Enemy2Blowup");
	auto animate = Animate::create(animation);

	auto removeEnemy2 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemy2, this, enemy2));
}

void EnemyLayer::removeEnemy2(Node* pTarget)
{
	auto enemy2 = (Enemy*)pTarget;
	if(enemy2) {
		_vAllEnemy2.eraseObject(enemy2);
		this->removeChild(enemy2, true);
	}
}

void EnemyLayer::removeAllEnemy2()
{
	for(auto iter : _vAllEnemy2) {
		auto enemy2 = (Enemy*)iter;
		if(enemy2->getLife() > 0) {
			enemy2Blowup(enemy2);
		}
	}
}





void EnemyLayer::addEnemy3(float dt)
{
	auto enemy3 = Enemy::create();
	enemy3->bindSprite(Sprite::createWithSpriteFrame(_enemy3SpriteFrame_1), ENEMY3_MAXLIFE);

	auto enemy3Size = enemy3->getSprite()->getContentSize();
	auto winSize = Director::getInstance()->getWinSize();
	int minX = enemy3Size.width/2;
	int maxX = winSize.width - enemy3Size.width/2;
	int rangeX = maxX - minX;
	int actualX = (rand()%rangeX) + minX;

	enemy3->setPosition(actualX, winSize.height + enemy3Size.height/2);
	this->addChild(enemy3);
	_vAllEnemy2.pushBack(enemy3);

	float minDuration, maxDuration;
	switch(airplane::GameLayer::getCurLevel())
	{
	case EASY:
		minDuration = 4.0f;
		maxDuration = 8.0f;
		break;
	case MIDDLE:
		minDuration = 3.6f;
		maxDuration = 7.2f;
		break;
	case HARD:
		minDuration = 3.2f;
		maxDuration = 6.4f;
		break;
	default:
		minDuration = 4.0f;
		maxDuration = 8.0f;
		break;
	}
	int rangeDuration = maxDuration - minDuration;
	int acturalDuration = (rand()%rangeDuration) + minDuration;

	auto actionMove = MoveTo::create(acturalDuration, Point(actualX, -enemy3->getSprite()->getContentSize().height/2));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemy3MoveFinished, this));

	auto sequence = Sequence::create(actionMove, actionDone);
	enemy3->runAction(sequence);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2f);
	animation->addSpriteFrame(_enemy3SpriteFrame_1);
	animation->addSpriteFrame(_enemy3SpriteFrame_2);
	auto animate = Animate::create(animation);
	enemy3->getSprite()->runAction(RepeatForever::create(animate));

}

void EnemyLayer::enemy3MoveFinished(Node* pSender)
{
	auto enemy3 = (Enemy*)pSender;
	this->removeChild(enemy3, true);
	_vAllEnemy3.eraseObject(enemy3);
}

void EnemyLayer::enemy3Blowup(Enemy* enemy3)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("enemy3_down.mp3");
	auto animation = AnimationCache::getInstance()->getAnimation("Enemy3Blowup");
	
	auto animate = Animate::create(animation);
	auto removeEnemy3 = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemy3, this, enemy3));
	auto sequence = Sequence::create(animate, removeEnemy3, nullptr);
	enemy3->getSprite()->runAction(sequence);
}

void EnemyLayer::removeEnemy3(Node* pTarget)
{
	auto enemy3 = (Enemy*)pTarget;
	if(enemy3) {
		enemy3->stopAllActions();
		_vAllEnemy3.eraseObject(enemy3);
		this->removeChild(enemy3, true);
	}
}

void EnemyLayer::removeAllEnemy3()
{
	for(auto iter : _vAllEnemy3) {
		auto enemy3 = (Enemy*)iter;
		if(enemy3->getLife() > 0) {
			enemy3Blowup(enemy3);
		}
	}
}

void EnemyLayer::removeAllEnemy()
{
	removeAllEnemy1();
	removeAllEnemy2();
	removeAllEnemy3();
}

