#include "BirdSprite.h"
#include "AtlasLoader.h"


BirdSprite* BirdSprite::s_shareBirdSprite = nullptr;

BirdSprite* BirdSprite::getInstance()
{
	if(NULL == s_shareBirdSprite) {
		s_shareBirdSprite = new BirdSprite();
		if(!s_shareBirdSprite->init()) {
			delete(s_shareBirdSprite);
			s_shareBirdSprite = NULL;
			CCLOG("ERROR: Could not init s_shareBirdSprite");
		}
		log("create bird first");
	}

	return s_shareBirdSprite;

}



bool BirdSprite::init()
{
	this->_isFirstTime = 3;

	return true;
}

bool BirdSprite::createBird()
{
	bool bRet = false;
	do 
	{
		this->createBirdRandom();
		auto birdFrame = AtlasLoader::getInstance()->getSpriteFrameByName(this->_birdName);
		CC_BREAK_IF(!Sprite::initWithSpriteFrame(birdFrame));

		// create the bird animation
		auto animation = this->createAnimation(this->_birdNameFormat.c_str(), 3, 10);
		auto animate = Animate::create(animation);
		this->_idleAction = RepeatForever::create(animate);

		// create the swing action
		ActionInterval*up = CCMoveBy::create(0.4f, Point(0, 8));
		ActionInterval* upBack = up->reverse();
		this->_swingAction = RepeatForever::create(Sequence::create(up, upBack, NULL));

		bRet = true;
	} while (0);

	return bRet;
}

void BirdSprite::idle()
{
	if(changeState(ACTION_STATE_IDLE)) {
		this->runAction(_idleAction);
		this->runAction(_swingAction);
	}

}

void BirdSprite::fly()
{
	if(changeState(ACTION_STATE_FLY)) {
		this->stopAction(_swingAction);
		this->getPhysicsBody()->setGravityEnable(true);
	}

}

void BirdSprite::die()
{
	if(changeState(ACTION_STATE_DIE)) {
		//this->stopAllActions();
		this->cleanup();
	}
}

Animation* BirdSprite::createAnimation(const char* fmt, int count, float fps)
{
	auto animation = Animation::create();
	animation->setDelayPerUnit(1/fps);
	for(int i = 0; i < count; i++) {
		const char* filename = String::createWithFormat(fmt, i)->getCString();
		auto frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}

	return animation;
}

void BirdSprite::createBirdRandom()
{
	if(_isFirstTime & 1) {
		_isFirstTime &= 2;
	} else if(_isFirstTime & 2){
		_isFirstTime &= 1;
		return;
	}

	srand((unsigned)time(NULL));
	int type = ((int)rand())%3;

	switch (type)
	{
	case 0:
		_birdName = "bird0_0";
		_birdNameFormat = "bird0_%d";
		break;
	case 1:
		_birdName = "bird1_0";
		_birdNameFormat = "bird1_%d";
		break;
	case 2:
		_birdName = "bird2_0";
		_birdNameFormat = "bird2_%d";
		break;
	default:
		break;
	}
}

bool BirdSprite::changeState(ActionState state)
{
	_currentStatus = state;

	return true;
}
