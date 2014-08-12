#include "BackgroundLayer.h"
#include "AtlasLoader.h"


bool BackgroundLayer::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!Layer::init());

		// 根据当前时间来设置背景: bg_day or bg_nignth
		time_t t = time(NULL);
		tm* lt = localtime(&t);
		int hour = lt->tm_hour;

		Sprite* background;
		if(hour >= 6 && hour <= 17) {
			background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
		} else {
			background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_night"));
		}
		background->setAnchorPoint(Point::ZERO);
		background->setPosition(Point::ZERO);
		this->addChild(background);

		bRet = true;
	} while (0);


	return bRet;
}

float BackgroundLayer::getLandHeight()
{
	return Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"))->getContentSize().height;
}