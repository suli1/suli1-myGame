#include "GameLayer_Plane.h"
#include "PlaneLayer.h"

NS_AIRPLANE_BEGIN

GameLayer::GameLayer()
: _background1(nullptr)
, _background2(nullptr)
, _bulletLayer(nullptr)
, _enemyLayer(nullptr)
{
}

int GameLayer::_curLevel = EASY;

bool GameLayer::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!Layer::init());

		// png加入全局cache中
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");

		// 加载_background1
		_background1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
		_background1->setAnchorPoint(Point::ZERO);
		_background1->setPosition(Point::ZERO);
		this->addChild(_background1);

		// 加载_background2
		_background2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
		_background2->setAnchorPoint(Point::ZERO);
		_background2->setPosition(0, _background2->getContentSize().height - 2);		// 这里减2是为了防止图片交界的黑线
		this->addChild(_background2);

		// 移动背景，产生飞机飞行的效果
		this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);

		// 添加飞机层
		auto planeLayer = PlaneLayer::getInstance();
		this->addChild(planeLayer);

		// 添加子弹层
		_bulletLayer = BulletLayer::create();
		this->addChild(_bulletLayer);
		_bulletLayer->startShoot(0.2f);

		// 添加敌机层
		_enemyLayer = EnemyLayer::create();
		this->addChild(_enemyLayer);


		//// 设置触摸事件
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		this->scheduleUpdate();

		//// test custonEvent
		//_eventDispatcher->addCustomEventListener("customEvent", [&](EventCustom* event){
		//	log("custom event run");
		//});
	
		bRet = true;
	} while (0);


	return bRet;
}

void GameLayer::backgroundMove(float dt)
{
	_background1->setPositionY(_background1->getPositionY() - 2);
	_background2->setPositionY(_background1->getPositionY() + _background1->getContentSize().height - 2);

	//要注意因为背景图高度是842，所以每次减去2最后可以到达0，假如背景高度是841，那么这个条件永远达不到，滚动失败  
	// 
	if(_background2->getPositionY() == 0) {
		_background1->setPositionY(0);
	}

}

void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{

}

void GameLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
	auto planeLayer = PlaneLayer::getInstance();
	if(planeLayer->_isAlive) {
		Vec2 beginPoint = touches[0]->getLocation();
		auto planeRect = planeLayer->getChildByTag(AIRPLANE)->getBoundingBox();
		// 允许稍大一点触摸位置
		planeRect.origin.x -= 15;
		planeRect.origin.y -= 15;
		planeRect.size.width += 30;
		planeRect.size.height += 30;

		if(planeRect.containsPoint(this->getParent()->convertToNodeSpace(beginPoint))) {
			auto endPoint = touches[0]->getPreviousLocationInView();
			endPoint = Director::getInstance()->convertToGL(endPoint);

			auto offset = beginPoint -  endPoint;
			// 获取正真的移动位置
			auto toPoint = planeLayer->getChildByTag(AIRPLANE)->getPosition() + offset;
			planeLayer->MoveTo(toPoint);
		}

	}
}

void GameLayer::update(float dt)
{
	if(_curLevel == EASY && _score >= 10000) {
		_curLevel = MIDDLE;
	} else if(_curLevel == MIDDLE && _score >= 20000) {
		_curLevel = HARD;
	}

	auto bulletsToDelete = __Array::create();
	bulletsToDelete->retain();
	Ref *bt, *et, *ut;



}


NS_AIRPLANE_END