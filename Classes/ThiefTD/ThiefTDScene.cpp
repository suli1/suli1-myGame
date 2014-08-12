#include "ThiefTDScene.h"
#include "PlayLayer.h"


ThiefTDScene::ThiefTDScene()
{

}

void ThiefTDScene::runThisGame()
{

    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(480.0f, 320.0f, ResolutionPolicy::FIXED_HEIGHT);
    Director::getInstance()->setContentScaleFactor(864.0f / 320.0f);

    auto layer = PlayLayer::create();
    this->addChild(layer);

    Director::getInstance()->replaceScene(this);
}