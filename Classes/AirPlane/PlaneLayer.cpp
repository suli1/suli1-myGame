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

		// 创建飞机精灵前要先调用SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrameWithFile("shoot.plist")加载全局资源
		// 否则plane会空指针；  这个调用已经放在welcome.cpp中了
		auto plane = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
		plane->setPosition(winSize.width/2, plane->getContentSize().height/2);	// 飞机放置在中央底部
		this->addChild(plane, 0, AIRPLANE);

		auto blink = Blink::create(1.0, 3);		//闪烁动画
		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
		auto animate = Animate::create(animation);	// 帧动画

		plane->runAction(blink);		// 执行闪烁动画
		plane->runAction(RepeatForever::create(animate));		// 执行帧动画

		bRet = true;
	} while (0);

	return bRet;
}

void PlaneLayer::MoveTo(Point location)
{
	if(_isAlive && !Director::getInstance()->isPaused()) {
		// 进行边界判定
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


