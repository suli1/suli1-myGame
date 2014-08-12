#include "StatusLayer.h"
#include "Number.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"


NS_FLAPPYBIRD_BEGIN

bool StatusLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		this->_bestScore = 0;
		this->_currentScore = 0;
		this->_isNewRecord = false;

		Number::getInstance()->loadNumber(NUMBER_FONT.c_str(), "font_0%02d", 48);
		Number::getInstance()->loadNumber(NUMBER_SCORE.c_str(), "number_score_%02d");
		this->_visibleSize = Director::getInstance()->getVisibleSize();
		this->_originPoint = Director::getInstance()->getVisibleOrigin();
		this->showReadyStatus();
		this->loadWhiteSprite();

		bRet = true;
	} while (0);

	return bRet;
}


// 显示游戏开始画面
void StatusLayer::onGameStart()
{
	this->showStartStatus();
}

// 主要负责显示实时得分
void StatusLayer::onGamePlaying(int score)
{
	this->removeChild(this->_scoreSprite);
	this->_scoreSprite = (Sprite*)Number::getInstance()->convert(NUMBER_FONT.c_str(), score);
	_scoreSprite->setPosition(Point(this->_originPoint.x + this->_visibleSize.width / 2,this->_originPoint.y + this->_visibleSize.height *5/6));
	this->addChild(_scoreSprite);
}

void StatusLayer::onGameEnd(int curScore, int bestScore)
{
	this->showOverStatus(curScore, bestScore);
}

void StatusLayer::showStartStatus()
{
	this->_getreadySprite->runAction(FadeOut::create(0.4f));
	this->_tutorialSprite->runAction(FadeOut::create(0.4f));
}

void StatusLayer::showReadyStatus()
{
	_scoreSprite = (Sprite *)Number::getInstance()->convert(NUMBER_FONT.c_str(), 0);
	_scoreSprite->setPosition(Point(this->_originPoint.x + this->_visibleSize.width / 2,this->_originPoint.y + this->_visibleSize.height *5/6));
	this->addChild(_scoreSprite);

	_getreadySprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_ready"));
	_getreadySprite->setPosition(Point(this->_originPoint.x + this->_visibleSize.width / 2, this->_originPoint.y + this->_visibleSize.height *2/3));
	this->addChild(_getreadySprite);

	_tutorialSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("tutorial"));
	_tutorialSprite->setPosition(Point(this->_originPoint.x + this->_visibleSize.width / 2, this->_originPoint.y + this->_visibleSize.height * 1/2));
	this->addChild(_tutorialSprite);
}


void StatusLayer::showOverStatus(int curScore, int bestScore)
{
	this->_currentScore = curScore;
	this->_bestScore = bestScore;
	if(curScore > bestScore) {
		this->_bestScore = curScore;
		this->_isNewRecord = true;
	} else {
		this->_isNewRecord = false;
	}
	this->removeChild(_scoreSprite);
	this->blinkFullScreen();
}

void StatusLayer::loadWhiteSprite()
{
	// this white sprite is used for blinking the screen for a short while
	_whiteSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("white"));
	_whiteSprite->setScale(100);
	_whiteSprite->setOpacity(0);
	this->addChild(_whiteSprite, 10000);

}

void StatusLayer::blinkFullScreen()
{
	//display a flash blink
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
	auto blinkAction = Sequence::create(fadeIn,fadeOut,NULL);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInGameOver, this));
	auto sequence = Sequence::createWithTwoActions(blinkAction, actionDone);
	_whiteSprite->stopAllActions();
	_whiteSprite->runAction(sequence);
}

void StatusLayer::fadeInGameOver()
{
	// create the game over panel
	Sprite* gameoverSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("text_game_over"));
	gameoverSprite->setPosition(Point(this->_originPoint.x + this->_visibleSize.width / 2, this->_originPoint.y + this->_visibleSize.height *2/3));
	this->addChild(gameoverSprite);
	auto gameoverFadeIn = FadeIn::create(0.5f);

	// Start next action
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::jumpToScorePanel, this));
	auto sequence = Sequence::createWithTwoActions(gameoverFadeIn, actionDone);
	gameoverSprite->stopAllActions();
	gameoverSprite->runAction(sequence);
}

void StatusLayer::jumpToScorePanel()
{
	// create the score panel
	Sprite* scorepanelSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("score_panel"));
	scorepanelSprite->setPosition(Point(this->_originPoint.x + this->_visibleSize.width / 2, this->_originPoint.y - scorepanelSprite->getContentSize().height));
	this->addChild(scorepanelSprite);

	//display the  best score on the score panel
	auto bestScoreSprite = (Sprite *)Number::getInstance()->convert(NUMBER_SCORE.c_str(), this->_bestScore, Gravity::GRAVITY_RIGHT);
	bestScoreSprite->setAnchorPoint(Point(1, 1));
	bestScoreSprite->setPosition(scorepanelSprite->getContentSize().width - 28 ,
		50);
	scorepanelSprite->addChild(bestScoreSprite);


	string medalsName = this->getMedalsName(_currentScore);
	if(medalsName != "") {
		Sprite* medalsSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName(medalsName));
		medalsSprite->addChild(this->_blink);
		medalsSprite->setPosition(54, 58);
		scorepanelSprite->addChild(medalsSprite);
	}

	//if the current score is higher than the best score.
	//the panel will appear a "new" tag.
	if(this->_isNewRecord){
		Sprite* newTagSprite = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("new"));
		newTagSprite->setPosition(-16, 12);
		bestScoreSprite->addChild(newTagSprite);
	}

	// Start next action
	auto scorePanelMoveTo = MoveTo::create(0.8f ,Point(this->_originPoint.x + this->_visibleSize.width / 2,this->_originPoint.y + this->_visibleSize.height/2 - 10.0f));
	// add variable motion for the action
	EaseExponentialOut* sineIn = EaseExponentialOut::create(scorePanelMoveTo);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInRestartBtn, this));
	auto sequence = Sequence::createWithTwoActions(sineIn, actionDone);
	scorepanelSprite->stopAllActions();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	scorepanelSprite->runAction(sequence);
}

void StatusLayer::fadeInRestartBtn()
{
	Node * tmpNode = Node::create();

	//create the restart menu;
	Sprite* restartBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	Sprite* restartBtnActive = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_play"));
	restartBtnActive->setPositionY(-4);
	auto  menuItem = MenuItemSprite::create(restartBtn,restartBtnActive,NULL,CC_CALLBACK_1(StatusLayer::menuRestartCallback,this));
	auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(this->_originPoint.x + this->_visibleSize.width / 2 - restartBtn->getContentSize().width / 2, this->_originPoint.y + this->_visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(menu);


	//create the rate button. however ,this button is not available yet = =
	Sprite* rateBtn = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("button_score"));
	rateBtn->setPosition(Point(this->_originPoint.x + this->_visibleSize.width / 2 + rateBtn->getContentSize().width / 2, this->_originPoint.y + this->_visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(rateBtn);
	this->addChild(tmpNode);

	//fade in the two buttons
	auto fadeIn = FadeIn::create(0.1f);
	//tmpNode->stopAllActions();
	//tmpNode->runAction(fadeIn);

	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::refreshScoreCallback,this));
	auto sequence = Sequence::createWithTwoActions(fadeIn,actionDone);
	tmpNode->stopAllActions();
	tmpNode->runAction(sequence);
}

void StatusLayer::refreshScoreCallback()
{
	this->_tmpScore = 0;
	schedule(schedule_selector(StatusLayer::refreshScoreExecutor), 0.1f);
}

void StatusLayer::refreshScoreExecutor(float dt)
{
	if(this->getChildByTag(CURRENT_SCORE_SPRITE_TAG)){
		this->removeChildByTag(CURRENT_SCORE_SPRITE_TAG);
	}
	_scoreSprite = (Sprite *)Number::getInstance()->convert(NUMBER_SCORE.c_str(), this->_tmpScore, Gravity::GRAVITY_RIGHT);
	_scoreSprite->setAnchorPoint(Point(1,0));
	_scoreSprite->setPosition(Point(this->_originPoint.x + this->_visibleSize.width * 3 / 4 + 20.0f, this->_originPoint.y + this->_visibleSize.height *  1 / 2));
	_scoreSprite->setTag(CURRENT_SCORE_SPRITE_TAG);
	this->addChild(_scoreSprite,1000);
	this->_tmpScore++;
	if(this->_tmpScore > this->_currentScore){
		unschedule(schedule_selector(StatusLayer::refreshScoreExecutor));
	}
}

string StatusLayer::getMedalsName(int score)
{
	this->setBlinkSprite();

	//display the golden silver or bronze iron
	string medalsName = "";
	if(this->_currentScore >=10 && this->_currentScore < 20){//iron medals
		medalsName = "medals_0";
	}else if(this->_currentScore >= 20 && _currentScore < 30){//bronze medals
		medalsName = "medals_1";
	}else if(_currentScore >=30 && _currentScore < 50){//silver medals
		medalsName = "medals_2";
	}else if(_currentScore >=50){//golden medals
		medalsName = "medals_3";
	}
	return medalsName;
}

void StatusLayer::setBlinkSprite()
{
	this->_blink = Sprite::createWithSpriteFrame(AtlasLoader::getInstance()->getSpriteFrameByName("blink_00"));
	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	for (int i = 0; i < 3; i++){
		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	for (int i = 2; i >= 0; i--){
		const char *filename = String::createWithFormat("blink_%02d", i)->getCString();
		SpriteFrame *frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	auto animate = Animate::create(animation);
	auto actionDone = CallFunc::create(bind(&StatusLayer::blinkAction,this));
	auto sequence = Sequence::createWithTwoActions(animate, actionDone);
	_blink->runAction(RepeatForever::create(sequence));
}

void StatusLayer::blinkAction()
{
	if(this->_blink && this->_blink->getParent()) {
		Size activeSize = this->_blink->getParent()->getContentSize();
		this->_blink->setPosition(rand()%((int)(activeSize.width)), rand()%((int)(activeSize.height)));
	}
}

void StatusLayer::menuRestartCallback(Ref *sender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.ogg");
	auto scene = GameScene::create();
	TransitionScene *transition = TransitionFade::create(1, scene);
	Director::getInstance()->replaceScene(transition);
}

NS_FLAPPYBIRD_END

