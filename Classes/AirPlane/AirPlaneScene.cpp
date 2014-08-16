#include "AirPlaneScene.h"
#include "GameScene_Plane.h"

USING_NS_AIRPLANE;


AirPlaneScene::AirPlaneScene()
    : GameBasicScene(false, true)
{

}

void AirPlaneScene::runThisGame()
{
    std::vector<std::string> paths;
    paths.push_back("AirPlane/sound");
    paths.push_back("AirPlane/ui");
    FileUtils::getInstance()->setSearchPaths(paths);

    auto scene = GameScene::create();
    this->addChild(scene);

    Director::getInstance()->replaceScene(this);
}

