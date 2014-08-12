#include "PlaneLayer.h"


PlaneLayer* PlaneLayer::s_sharePlaneLayer = nullptr;

PlaneLayer* PlaneLayer::getInstance()
{
	if(!s_sharePlaneLayer) {
		s_sharePlaneLayer = new PlaneLayer();
		if(!(s_sharePlaneLayer && s_sharePlaneLayer->init())) {
			CC_SAFE_DELETE(s_sharePlaneLayer);
			log("error, can't create PlaneLayer");

		}
		log("create PlaneLayer!");

	}

	return s_sharePlaneLayer;
}


bool PlaneLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		_isAlive = true;
		_score = 0;

		Size winSize = Director::getInstance()->getWinSize();

		// �����ɻ�����ǰҪ�ȵ���SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrameWithFile("shoot.plist")����ȫ����Դ
		// ����plane���ָ�룻  ��������Ѿ�����welcome.cpp����
		auto plane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
		plane->setPosition(winSize.width/2, plane->getContentSize().height/2);	// �ɻ�����������ײ�
		this->addChild(plane, 0, AIRPLANE);

		auto blink = Blink::create(1.0, 3);		//��˸����
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
		auto animate = Animate::create(animation);	// ֡����

		plane->runAction(blink);		// ִ����˸����
		plane->runAction(RepeatForever::create(animate));		// ִ��֡����

		bRet = true;
	} while (0);

	return bRet;
}

void PlaneLayer::MoveTo(Point location)
{
	if(_isAlive && !Director::getInstance()->isPaused()) {
		// ���б߽��ж�
		auto winSize = Director::getInstance()->getWinSize();
		auto planeSize = this->getChildByTag(AIRPLANE)->getContentSize();
		if(location.x < planeSize.width/2) {
			location.x = planeSize.width/2;
		} else if(location.x > winSize.width - planeSize.width/2) {
			location.x = winSize.width - planeSize.width/2;
		}

		if(location.y < planeSize.height/2) {
			location.y = planeSize.height/2;
		} else if(location.y > winSize.height - planeSize.height/2) {
			location.y = winSize.height - planeSize.height/2;
		}

		this->getChildByTag(AIRPLANE)->setPosition(location);
	}
}


