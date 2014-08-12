#ifndef BIRD_WELCOME_SCENE
#define BIRD_WELCOME_SCENE

#include "define.h"
#include "cocos2d.h"
#include "..//GameBasic.h"

USING_NS_CC;

NS_FLAPPYBIRD_BEGIN

class WelcomeScene : public GameBasicScene {
public:
	WelcomeScene();

	virtual bool init();

	CREATE_FUNC(WelcomeScene);

	virtual void runThisGame() {}
};

NS_FLAPPYBIRD_END

#endif