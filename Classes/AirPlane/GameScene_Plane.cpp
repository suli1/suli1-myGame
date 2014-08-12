#include "GameScene_Plane.h"
#include "GameLayer_Plane.h"

NS_AIRPLANE_BEGIN

bool GameScene::init()
{
	bool bRet = false;

	do 
	{
		CC_BREAK_IF(!Scene::init());

		auto layer = GameLayer::create();

		this->addChild(layer);

		bRet = true;
	} while (0);


	return bRet;
}

NS_AIRPLANE_END