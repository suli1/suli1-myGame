#include "WelcomeScene.h"
#include "WelcomeLayer.h"


NS_FLAPPYBIRD_BEGIN

WelcomeScene::WelcomeScene()
{

}

bool WelcomeScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Scene::init());

		auto welcomeLayer = WelcomeLayer::create();
		CC_BREAK_IF(!welcomeLayer);
		this->addChild(welcomeLayer);

		bRet = true;
	} while (0);

	return bRet;
}

NS_FLAPPYBIRD_END