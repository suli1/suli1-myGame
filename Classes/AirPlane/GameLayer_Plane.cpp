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

		// png����ȫ��cache��
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");

		// ����_background1
		_background1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
		_background1->setAnchorPoint(Point::ZERO);
		_background1->setPosition(Point::ZERO);
		this->addChild(_background1);

		// ����_background2
		_background2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
		_background2->setAnchorPoint(Point::ZERO);
		_background2->setPosition(0, _background2->getContentSize().height - 2);		// �����2��Ϊ�˷�ֹͼƬ����ĺ���
		this->addChild(_background2);

		// �ƶ������������ɻ����е�Ч��
		this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);

		// ��ӷɻ���
		auto planeLayer = PlaneLayer::getInstance();
		this->addChild(planeLayer);

		// ����ӵ���
		_bulletLayer = BulletLayer::create();
		this->addChild(_bulletLayer);
		_bulletLayer->startShoot(0.2f);

		// ��ӵл���
		_enemyLayer = EnemyLayer::create();
		this->addChild(_enemyLayer);


		//// ���ô����¼�
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

	//Ҫע����Ϊ����ͼ�߶���842������ÿ�μ�ȥ2�����Ե���0�����米���߶���841����ô���������Զ�ﲻ��������ʧ��  
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
		// �����Դ�һ�㴥��λ��
		planeRect.origin.x -= 15;
		planeRect.origin.y -= 15;
		planeRect.size.width += 30;
		planeRect.size.height += 30;

		if(planeRect.containsPoint(this->getParent()->convertToNodeSpace(beginPoint))) {
			auto endPoint = touches[0]->getPreviousLocationInView();
			endPoint = Director::getInstance()->convertToGL(endPoint);

			auto offset = beginPoint -  endPoint;
			// ��ȡ������ƶ�λ��
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