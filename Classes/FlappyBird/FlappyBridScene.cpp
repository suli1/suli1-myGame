#include "FlappyBirdScene.h"
#include "LoadingScene.h"

USING_NS_FLAPPYBIRD;

FlappyBirdScene::FlappyBirdScene()
	:GameBasicScene(false, true)
{

}

void FlappyBirdScene::runThisGame()
{
	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(288, 512, ResolutionPolicy::SHOW_ALL);
    Director::getInstance()->setContentScaleFactor(1.0f);

	auto scene = LoadingScene::create();
	this->addChild(scene);
	
	Director::getInstance()->replaceScene(this);

}