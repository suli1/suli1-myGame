#include "GameBasic.h"
#include "VisibleRect.h"
#include "GameController.h"


GameBasicScene::GameBasicScene(bool bPortrait /* = false */, bool physics /* = false */)
{
    if(physics) 
    {
#if CC_USE_PHYSICS
        GameBasicScene::initWithPhysics();
#else
        GameBasicScene::init();
#endif
    }
    else
    {
        Scene::init();
    }
}

void gameScene_callback(Ref *sender )
{
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(960, 540, ResolutionPolicy::SHOW_ALL);
    Director::getInstance()->setContentScaleFactor(1.0f);

    auto scene = Scene::create();
    auto layer = new GameController();
    scene->addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(scene);

    //cocostudio::ArmatureDataManager::destroyInstance();
}

void GameBasicScene::onEnter()
{
    Scene::onEnter();

    //add the menu item for back to main menu
    TTFConfig ttfConfig("fonts/Marker Felt.ttf", 20);
    auto label = Label::createWithTTF(ttfConfig,"MainMenu");

    auto menuItem = MenuItemLabel::create(label, gameScene_callback );
    auto menu = Menu::create(menuItem, NULL);

    menu->setPosition( Vec2::ZERO );
    menuItem->setPosition( Vec2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    addChild(menu, 1);
}