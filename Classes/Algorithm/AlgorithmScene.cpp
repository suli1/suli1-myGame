#include "AlgorithmScene.h"
#include "MapLayer.h"


void AlgorithmScene::runThisGame()
{
    std::vector<std::string> paths;
    paths.push_back("Algorithm");
    FileUtils::getInstance()->setSearchPaths(paths);

    auto layer = MapLayer::create();
    this->addChild(layer);

    Director::getInstance()->replaceScene(TransitionFade::create(0.1f, this));
}
