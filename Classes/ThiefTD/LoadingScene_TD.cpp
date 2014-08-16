#include "LoadingScene_TD.h"
#include "SimpleAudioEngine.h"
#include "HomeScene.h"
#include "../GameBasic.h"

using namespace CocosDenshion;

NS_TD_BEGIN

LoadingScene::LoadingScene()
    : _progressBar(nullptr)
    , _loadedResNum(0)
    , _loadedResTotal(22)
{

}

bool LoadingScene::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(!Scene::init());


        Size winSzie = Director::getInstance()->getWinSize();
        auto progressBarBg = Sprite::create("load.png");
        progressBarBg->setPosition(winSzie.width/2, winSzie.height/2);
        this->addChild(progressBarBg);

        _progressBar = ProgressTimer::create(Sprite::create("loadBar.png"));
        _progressBar->setType(ProgressTimer::Type::BAR);
        _progressBar->setMidpoint(Point(0, 0.5f));
        _progressBar->setBarChangeRate(Point(1, 0));
        _progressBar->setPercentage(0);
        _progressBar->setPosition(progressBarBg->getContentSize().width/2, progressBarBg->getContentSize().height/6);
        progressBarBg->addChild(_progressBar);
        

        bRet = true;
    } while (0);

    return bRet;

}

void LoadingScene::onEnter()
{
    // 1. add background


    // 2.start sync method loading the resources
    loadResources();

}


void LoadingScene::loadResources()
{
    // 1.加载音频文件

    // cocos2dx中preloadBackgroundMusic实现为空，后期需要修改
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/music.mp3").c_str());
    _loadedResNum++;

    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.wav").c_str());
    _loadedResNum++;

    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str());
    _loadedResNum++;

    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str());
    _loadedResNum++;

    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/shoot.wav").c_str());
    _loadedResNum++;

    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str());
    _loadedResNum++;

    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.wav").c_str());
    _loadedResNum++;

    // 2.加载plist
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");
    _loadedResNum++;

    // 3.加载图片纹理
    auto cache = Director::getInstance()->getTextureCache();
    cache->addImageAsync("playbg.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("playbg1.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("successfulBg.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("btn_back.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("btn_back_press.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("card_1.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("card_2.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("card_3.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("LevelInfoPanel.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("House.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("selectLevelBg.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("selectLevelBg1.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("selectLevelBg2.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("start_1.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));
    cache->addImageAsync("start_2.png", CC_CALLBACK_1(LoadingScene::loadingCallback, this));

}

void LoadingScene::loadingCallback(Texture2D* texture)
{
    ++_loadedResNum;
    float percent = (float)_loadedResNum/(float)_loadedResTotal * 100;
    _progressBar->setPercentage(percent);

    if(_loadedResNum == _loadedResTotal) {
        // 切换场景
        transitionScene();

        SimpleAudioEngine::getInstance()->playBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/music.mp3").c_str());
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.1f);
    }
}

void LoadingScene::transitionScene()
{
    auto scene = HomeScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(0.1f, scene));
}


NS_TD_END