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

    std::vector<std::string> paths;
    paths.push_back("FlappyBird/image");
    paths.push_back("FlappyBird/sounds");
    FileUtils::getInstance()->setSearchPaths(paths);


    auto scene = LoadingScene::create();
    this->addChild(scene);
    
    Director::getInstance()->replaceScene(this);

}