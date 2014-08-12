#include "OptionLayer.h"


bool OptionLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(OptionLayer::onTouchesBegan, this);
		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		bRet = true;
	} while (0);

	return bRet;
}

void OptionLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
	this->delegator->onTouch();
}