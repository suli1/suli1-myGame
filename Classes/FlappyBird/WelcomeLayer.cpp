#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"
#include "AtlasLoader.h"
#include "GameScene.h"

NS_FLAPPYBIRD_BEGIN

bool WelcomeLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		// 获取原点和屏幕的大小
		Point origin = Director::getInstance()->getVisibleOrigin();
		Size visiableSize = Director::getInstance()->getVisibleSize();

		// 获取当前时间，背景图片会根据当前时间选择白天或晚上的图片: bg_day or bg_night
		time_t t = time(NULL);
		tm* lt = localtime(&t);
		int hour = lt->tm_hour;

		Sprite* background;
		if(hour >= 6 && hour <= 17) {
		background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_day"));
		} else {
		background = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("bg_night"));
		}
		CC_BREAK_IF(!background);
		background->setAnchorPoint(Point::ZERO);
		background->setPosition(Point::ZERO);
		this->addChild(background);


		// add title
		Sprite* title = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("title"));
		CC_BREAK_IF(!title);
		title->setPosition(Point(origin.x +visiableSize.width/2, (visiableSize.height*5)/7));
		this->addChild(title);
		
		// add start-menu
		Sprite* startButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
		CC_BREAK_IF(!startButton);
		Sprite* activeStartButton = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
		CC_BREAK_IF(!activeStartButton);
		activeStartButton->setPositionY(5);
		auto menuItem = MenuItemSprite::create(startButton, activeStartButton, NULL, CC_CALLBACK_1(WelcomeLayer::menuStartCallback, this));
		CC_BREAK_IF(!menuItem);
		menuItem->setPosition(Point(origin.x +visiableSize.width/2, origin.y +visiableSize.height*2/5));

		auto menu = Menu::create(menuItem, NULL);
		CC_BREAK_IF(!menu);
		menu->setPosition(Point(origin.x, origin.y));
		this->addChild(menu, 1);


		// 在屏幕中间创建一个小鸟
		this->_bird = BirdSprite::getInstance();
		this->_bird->createBird();
		this->_bird->setTag(BIRD_SPRITE_TAG);
		this->_bird->setPosition(Point(origin.x + visiableSize.width/2, origin.y +visiableSize.height*3/5 - 10));
		this->_bird->idle();
		this->addChild(this->_bird);


		// add land
		this->_land1 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
		this->_land1->setAnchorPoint(Point::ZERO);
		this->_land1->setPosition(Point::ZERO);
		this->addChild(this->_land1);

		this->_land2 = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("land"));
		this->_land2->setAnchorPoint(Point::ZERO);
		this->_land2->setPosition(this->_land1->getContentSize().width - 2.0f, 0);
		this->addChild(this->_land2);

		this->schedule(schedule_selector(WelcomeLayer::scrollLand), 0.01f);

		// add the copyright-text
		auto copyright = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("brand_copyright"));
		CC_BREAK_IF(!copyright);
		copyright->setPosition(Point(origin.x + visiableSize.width/2, origin.y + visiableSize.height/6));
		this->addChild(copyright, 10);

		bRet = true;
	} while (0);

	return bRet;
}


void WelcomeLayer::menuStartCallback(Ref *sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	this->removeChildByTag(BIRD_SPRITE_TAG);
	auto scene = GameScene::create();

	// 切换场景
	TransitionScene* transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

void WelcomeLayer::scrollLand(float dt)
{
	this->_land1->setPositionX(this->_land1->getPositionX() - 2.0f);
	this->_land2->setPositionX(this->_land1->getPositionX() + this->_land1->getContentSize().width - 2.0f);

	if(this->_land2->getPositionX() == 0) {
		this->_land1->setPositionX(0);
	}

}

NS_FLAPPYBIRD_END


