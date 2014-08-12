#include "AirPlaneScene.h"
#include "GameScene_Plane.h"

USING_NS_AIRPLANE;


AirPlaneScene::AirPlaneScene()
	: GameBasicScene(false, true)
{

}

void AirPlaneScene::runThisGame()
{
	auto scene = GameScene::create();
	this->addChild(scene);

	Director::getInstance()->replaceScene(this);
}