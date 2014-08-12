#include "GameScene.h"
#include "BackgroundLayer.h"
#include "OptionLayer.h"
#include "GameLayer.h"
#include "StatusLayer.h"

NS_FLAPPYBIRD_BEGIN

GameScene::GameScene() 
{

}

bool GameScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Scene::initWithPhysics());
		this->getPhysicsWorld()->setGravity(Vect(0, -900));

		auto backgroundLayer = BackgroundLayer::create();
		if(backgroundLayer) {
			this->addChild(backgroundLayer);
		}

		auto statusLayer = StatusLayer::create();
		auto gameLayer = GameLayer::create();
		if(gameLayer) {
			gameLayer->setPhyWorld(this->getPhysicsWorld());
			gameLayer->setDelegator(statusLayer);
			this->addChild(gameLayer);
		}

		if(statusLayer) {
			this->addChild(statusLayer);
		}


		
		auto optionLayer = OptionLayer::create();
		if(optionLayer) {
			optionLayer->setDelegator(gameLayer);
			this->addChild(optionLayer);
		}
		
		bRet = true;
	} while (0);

	return bRet;
}

void GameScene::restart()
{
	this->removeAllChildrenWithCleanup(true);
	this->init();
}

NS_FLAPPYBIRD_END