	#include "GameController.h"
#include "GameBasic.h"
#include "VisibleRect.h"
#include "games.h"

typedef struct _Controller{
	const char *game_name;
	std::function<GameBasicScene*()> callback;
}_Controller;

_Controller g_aGameNames[] = {
	{ "Flappy bird", [](){ return new FlappyBirdScene(); } } ,

	{ "Piano piece", [](){ return nullptr; } },

	{ "Air plane", [](){ return new AirPlaneScene(); } },

    { "Thief TD", [](){ return new ThiefTDScene(); } },
};

static int g_gameCount = sizeof(g_aGameNames)/sizeof(g_aGameNames[0]);
static _Controller* g_currentController = nullptr;
static Vec2 g_tCurPos = Vec2::ZERO;


#define LINE_SPACE			40
#define ZORDER_BASE			10000


GameController::GameController()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add close menu
	auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(GameController::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);



	// add menu items for small games
	TTFConfig ttfConfig("fonts/Marker Felt.ttf", 24);
	_itemMenu = Menu::create();
	for(int i = 0; i < g_gameCount; i++){
		auto label = Label::createWithTTF(ttfConfig, g_aGameNames[i].game_name);
		//auto label = Label::createWithSystemFont(g_aGameNames[i].game_name, "Consolas", 24);
		auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(GameController::menuCallback, this));

		_itemMenu->addChild(menuItem, i + ZORDER_BASE);
		menuItem->setPosition(Vec2(VisibleRect::center().x, (VisibleRect::top().y - (i + 1)*LINE_SPACE)));
	}

	_itemMenu->setContentSize(Size(VisibleRect::getVisibleRect().size.width, (g_gameCount + 1)*LINE_SPACE));
	_itemMenu->setPosition(g_tCurPos);
	this->addChild(_itemMenu);

}

GameController::~GameController()
{

}


void GameController::menuCallback(Ref* sender)
{
	// Çå¿Õ»º´æ
	Director::getInstance()->purgeCachedData();

    
	auto menuItem = static_cast<MenuItem*>(sender);
	int idx = menuItem->getLocalZOrder() - ZORDER_BASE;

	auto scene = g_aGameNames[idx].callback();

	if(scene) {
		scene->runThisGame();
		scene->release();
	}
}

void GameController::menuCloseCallback(Ref* sender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}

void GameController::addConsoleAutoGame()
{
	//auto console = Director::getInstance()->getConsole();

	//static struct Console::Command autogame = {
	//	"autogame",
	//	""

	//};

	//console->addCommand(autogame);
}



