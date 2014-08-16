#include "AppDelegate.h"
#include "GameController.h"
#include "AppMacros.h"

// android long
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <android/log.h>
#define  LOG_TAG    "AppDelegate"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#endif

// windows log
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define LOGD(...)	log(__VA_ARGS__)
#endif



USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    Size winSize = director->getWinSize();
    if(!glview) {
        //glview = GLView::createWithRect("My Game", Rect(0, 0, winSize.width, winSize.height), 1);
        glview = GLView::create("My Game");
        //glview->setFrameSize(540, 960);
        director->setOpenGLView(glview);
    }

    //director->setContentScaleFactor(MIN(birdResource.size.height/designResolutionSize.height, birdResource.size.width/designResolutionSize.width));
    //director->setContentScaleFactor(birdResource.size.height/designResolutionSize.height);
    //director->setContentScaleFactor(birdResource.size.width/designResolutionSize.width);
    //glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
    //director->setContentScaleFactor(1.0);
    float scale = director->getContentScaleFactor();
    LOGD("scale is %f", scale);



    this->setResourceSearchResolution();

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();

    auto scene = Scene::create();
    auto layer = new GameController();
    layer->autorelease();
    layer->addConsoleAutoGame();

    scene->addChild(layer);

    //auto scene = LoadingScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}


void AppDelegate::setResourceSearchResolution()
{
    //std::vector<std::string> paths;
    //paths.push_back("fonts");

    //// FlappyBird
    //paths.push_back("FlappyBird");
    ////paths.push_back("FlappyBird/image");
    ////paths.push_back("FlappyBird/sounds");

    //// AirPlane
    //paths.push_back("AirPlane");
    ////paths.push_back("AirPlane/sounds");
    ////paths.push_back("AirPlane/ui");

    //// Thief TD
    //paths.push_back("ThiefTD");

    //FileUtils::getInstance()->setSearchPaths(paths);
}


