#include "ThiefTDScene.h"
#include "LoadingScene_TD.h"


ThiefTDScene::ThiefTDScene()
{

}

void ThiefTDScene::runThisGame()
{

    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(480.0f, 320.0f, ResolutionPolicy::FIXED_HEIGHT);
    Director::getInstance()->setContentScaleFactor(864.0f / 320.0f);

    std::vector<std::string> paths;
    paths.push_back("ThiefTD");
    FileUtils::getInstance()->setSearchPaths(paths);

    auto layer = td::LoadingScene::create();
    this->addChild(layer);

    Director::getInstance()->replaceScene(this);
}
