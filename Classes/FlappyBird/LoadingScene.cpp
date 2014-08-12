#include "LoadingScene.h"
#include "AtlasLoader.h"
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"


NS_FLAPPYBIRD_BEGIN

bool LoadingScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Scene::init());

		bRet = true;
	} while (0);

	return bRet;
}

void LoadingScene::onEnter()
{
	// add background to current scene

	auto background = Sprite::create("splash.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	background->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
	this->addChild(background);

	// start ansyc method load the atlas.png
	Director::getInstance()->getTextureCache()->addImageAsync("atlas.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));

}

void LoadingScene::loadingCallBack(Texture2D *texture)
{
	// loading the texture
	AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);

	// preload all the sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");


	// change the scene to new one
	auto scene = WelcomeScene::create();
	TransitionScene* transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);

}

NS_FLAPPYBIRD_END