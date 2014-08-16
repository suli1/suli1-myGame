#include "HomeLayer.h"
#include "PlayLayer.h"
#include "SimpleAudioEngine.h"


NS_TD_BEGIN

bool HomeLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(!Layer::init());

        Size winSize = Director::getInstance()->getWinSize();

        // 1.添加背景
        Sprite* spriteBg = Sprite::create("playbg.png");
        spriteBg->setPosition(winSize.width/2, winSize.height/2);
        //spriteBg->setAnchorPoint(Point(0.5f, 0.5f));
        this->addChild(spriteBg, -1);

        Sprite* spriteTitle = Sprite::createWithSpriteFrameName("title.png");
        spriteTitle->setPosition(winSize.width/3, winSize.height/3*2);
        //spriteTitle->setAnchorPoint(Point(0.));
        this->addChild(spriteTitle);
        auto move = MoveBy::create(1.0f, Point(0, 10));
        spriteTitle->runAction(RepeatForever::create(Sequence::create(move, move->reverse(), nullptr)));

        // 2.添加开始菜单
        auto itemStart = MenuItemImage::create("start_1.png",
                                               "start_2.png",
                                               CC_CALLBACK_1(HomeLayer::menuStartCallback, this));
        itemStart->setPosition((winSize.width - itemStart->getContentSize().width)/2, winSize.height/6);
        itemStart->setAnchorPoint(Point::ZERO);
        auto menuStart = Menu::create(itemStart, nullptr);
        menuStart->setPosition(Point::ZERO);
        this->addChild(menuStart, 1);


        // 围绕startMenu旋转的星星
        auto spriteStar = Sprite::createWithSpriteFrameName("star.png");
        spriteStar->setScale(0.7f);
        spriteStar->setPosition(itemStart->getPositionX(), itemStart->getPositionY());
        this->addChild(spriteStar, 11);

        // 星星尾巴的粒子效果
        auto emitter = ParticleSystemQuad::create("button.plist");
        emitter->retain();
        auto batch = ParticleBatchNode::createWithTexture(emitter->getTexture());
        batch->addChild(emitter);

        emitter->setPosition(itemStart->getPositionX(), itemStart->getPositionY());

        auto path = myPathFun(1, itemStart->getContentSize().height, itemStart->getContentSize().width);
        spriteStar->runAction(path);

        emitter->runAction(path->clone());
        this->addChild(batch, 10);
        emitter->release();

        bRet = true;
    } while (0);

    return bRet;
}

void HomeLayer::menuStartCallback(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str());

    auto scene = Scene::create();
    auto layer = PlayLayer::create();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f, scene));

}

//void HomeLayer::menuCloseCallback(Ref* pSender)
//{
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//
//}

RepeatForever* HomeLayer::myPathFun(float controlX, float controlY, float w)
{
    ccBezierConfig bezier1;
    bezier1.controlPoint_1 = Point(-controlX, 0);
    bezier1.controlPoint_2 = Point(-controlX, controlY);
    bezier1.endPosition = Point(0, controlY);
    auto bezierBy1 = BezierBy::create(0.6f, bezier1);

    auto move1 = MoveBy::create(0.7f, Point(w, 0));

    ccBezierConfig bezier2;
    bezier2.controlPoint_1 = Point(controlX, 0);
    bezier2.controlPoint_2 = Point(controlX, -controlY);
    bezier2.endPosition = Point(0, -controlY);
    auto bezierBy2 = BezierBy::create(0.6f, bezier2);

    auto move2 = MoveBy::create(0.7f, Point(-w, 0));

    auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, nullptr));

    return path;
}

NS_TD_END
