#include "GameLayer.h"
#include "BackgroundLayer.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "UserRecord.h"


NS_FLAPPYBIRD_BEGIN

bool GameLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		//get the origin point of the X-Y axis, and the visiable size of the screen
		Size visiableSize = Director::getInstance()->getVisibleSize();
		Point origin = Director::getInstance()->getVisibleOrigin();

		this->_gameStatus = GAME_STATUS_READY;
		this->_score = 0;

		// add the bird
		this->_bird = BirdSprite::getInstance();
		this->_bird->createBird();
		this->_bird->setOpacity(255);		// restart 后bird->_realOpacity会置为0，
		PhysicsBody* body = PhysicsBody::create();
		body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));

		body->setCategoryBitmask(0x01);
		body->setContactTestBitmask(0x03);
		body->setCollisionBitmask(0x03);

		body->setDynamic(true);
		body->setLinearDamping(0.0f);
		body->setGravityEnable(false);


		this->_bird->setPhysicsBody(body);
		this->_bird->setPosition(origin.x +visiableSize.width/3 - 5, origin.y + visiableSize.height/2 + 5);
		this->_bird->idle();
		this->addChild(this->_bird);

		// add the ground
		this->_groundNode = Node::create();
		float landHeight = BackgroundLayer::getLandHeight();
		auto groundBody = PhysicsBody::create();
		groundBody->addShape(PhysicsShapeBox::create(Size(288, landHeight)));

		groundBody->setCategoryBitmask(0x01);
		groundBody->setContactTestBitmask(0x03);
		groundBody->setCollisionBitmask(0x03);

		groundBody->setDynamic(false);
		groundBody->setLinearDamping(0.0f);
		this->_groundNode->setPhysicsBody(groundBody);
		this->_groundNode->setPosition(144, landHeight/2);
		this->addChild(this->_groundNode);


		// init land
		this->_landSprite1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
		this->_landSprite1->setAnchorPoint(Point::ZERO);
		this->_landSprite1->setPosition(Point::ZERO);
		this->addChild(this->_landSprite1, 30);

		this->_landSprite2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
		this->_landSprite2->setAnchorPoint(Point::ZERO);
		this->_landSprite2->setPosition(this->_landSprite1->getContentSize().width - 2.0f, 0);
		this->addChild(this->_landSprite2, 30);

		this->_shiftLand = schedule_selector(GameLayer::scrollLand);
		this->schedule(_shiftLand, 0.01f);

		this->scheduleUpdate();

		auto contactListener = EventListenerPhysicsContact::create();
		contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
		this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

		this->delegator = NULL;

		bRet = true;
	} while (0);

	return bRet;
}

void GameLayer::onTouch()
{
	if(GAME_STATUS_OVER == this->_gameStatus)
		return;

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_wing.ogg");
	if(GAME_STATUS_READY == this->_gameStatus) {
		this->delegator->onGameStart();
		this->_bird->fly();
		this->_gameStatus = GAME_STATUS_START;
		this->createPips();

	} else if(GAME_STATUS_START == this->_gameStatus) {
		this->_bird->getPhysicsBody()->setVelocity(Vect(0, 260));
	}
}

void GameLayer::update(float delta)
{
	if(GAME_STATUS_START == this->_gameStatus) {
		this->rotateBird();
		this->checkHit();
	}
}

// 设置小鸟旋转， 让它看起来有重量
void GameLayer::rotateBird()
{
	float verticalSpeed = this->_bird->getPhysicsBody()->getVelocity().y;
	//this->_bird->setRotation(MIN(MAX(-90, (verticalSpeed*0.2 + 60)), -30));
	this->_bird->setRotation(-10);
}

// 创建新的管道， 让它从左到右移动
void GameLayer::createPips()
{
	for(int i = 0; i < PIP_COUNT; i++) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Sprite* pipUp = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_up"));
		Sprite* pipDown = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("pipe_down"));
		Node* singlePip = Node::create();

		// bind to pair
		pipDown->setPosition(0, PIP_HEIGHT + PIP_DISTANCE);
		singlePip->addChild(pipUp, 0, UP_PIP);
		singlePip->addChild(pipDown, 0, DOWN_PIP);
		singlePip->setPosition(visibleSize.width + i*PIP_INTERVAL + WAIT_DISTANCE, this->getRandomHeight());

		auto body = PhysicsBody::create();
		auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, PIP_HEIGHT +PIP_DISTANCE));
		body->addShape(shapeBoxDown);
		body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));

		body->setCategoryBitmask(0x01);
		body->setContactTestBitmask(0x03);
		body->setCollisionBitmask(0x03);


		body->setDynamic(false);
		singlePip->setPhysicsBody(body);
		singlePip->setTag(PIP_NEW); 
		this->addChild(singlePip);
		this->_pips.push_back(singlePip);
	}
}

int GameLayer::getRandomHeight()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	return rand()%(int)(2*PIP_HEIGHT + PIP_DISTANCE - visibleSize.height);
}

// 检测小鸟的碰撞
void GameLayer::checkHit()
{
	for(auto pip : this->_pips) {
		if(pip->getTag() == PIP_NEW) {
			if(pip->getPositionX() < this->_bird->getPositionX()) {
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_point.ogg");
				this->_score++;
				this->delegator->onGamePlaying(this->_score);
				pip->setTag(PIP_PASS);
			}
		}
	}
}


void GameLayer::birdSpriteFadeOut()
{
	FadeOut* animation = FadeOut::create(1.5);
	CallFunc* animationDone = CallFunc::create(bind(&GameLayer::birdSpriteRemove, this));
	Sequence* sequence = Sequence::createWithTwoActions(animation, animationDone);
	this->_bird->stopAllActions();
	this->_bird->runAction(sequence);
}

void GameLayer::birdSpriteRemove()
{
	this->_bird->setRotation(0);
	this->removeChild(this->_bird);
}

void GameLayer::scrollLand(float dt)
{
	this->_landSprite1->setPositionX(this->_landSprite1->getPositionX() - 2.0f);
	this->_landSprite2->setPositionX(this->_landSprite1->getPositionX() + this->_landSprite1->getContentSize().width - 2.0f);

	if(this->_landSprite2->getPositionX() == 0) {
		this->_landSprite1->setPositionX(0);
	}

	// move the pips
	for(auto singlePip : this->_pips) {
		singlePip->setPositionX(singlePip->getPositionX() - 2);
		if(singlePip->getPositionX() < -PIP_WIDTH) {
			singlePip->setTag(PIP_NEW);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			singlePip->setPosition(visibleSize.width, this->getRandomHeight());
		}
	}
}

bool GameLayer::onContactBegin(/*EventCustom *event,*/ PhysicsContact& contact)
{
	this->gameOver();

	return true;
}

void GameLayer::gameOver()
{
	if(GAME_STATUS_OVER == this->_gameStatus)
		return;

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_hit.ogg");

	// update score
	int bestScore = UserRecord::getInstance()->readIntegerFromUserDefault("best_score");
	if(this->_score > bestScore) {
		UserRecord::getInstance()->saveIntegerToUserDefault("best_score", this->_score);
	}

	this->delegator->onGameEnd(this->_score, bestScore);
	this->unschedule(this->_shiftLand);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_die.ogg");
	this->_bird->die();
	this->_bird->setRotation(90);
	this->birdSpriteFadeOut();

	this->_gameStatus = GAME_STATUS_OVER;

	log("game over");

}

NS_FLAPPYBIRD_END



