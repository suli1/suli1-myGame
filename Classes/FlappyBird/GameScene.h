#ifndef BIRD_GAME_SCENE
#define BIRD_GAME_SCENE

#include "define.h"
#include "cocos2d.h"
#include "..//GameBasic.h"

USING_NS_CC;

NS_FLAPPYBIRD_BEGIN

class GameScene : public GameBasicScene {
public:
	GameScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	virtual void runThisGame() {}

	void restart();

};

NS_FLAPPYBIRD_END

#endif
