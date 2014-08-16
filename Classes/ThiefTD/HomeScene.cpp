#include "HomeScene.h"
#include "HomeLayer.h"

NS_TD_BEGIN

bool HomeScene::init()
{
    bool bRet = false;

    do 
    {
        CC_BREAK_IF(!GameBasicScene::init());

        auto layer = HomeLayer::create();
        this->addChild(layer);

        bRet = true;
    } while (0);


    return bRet;
}


void HomeScene::runThisGame()
{

}


NS_TD_END