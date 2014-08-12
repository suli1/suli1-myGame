#ifndef _PLANE_GAMESCENE_H_
#define _PLANE_GAMESCENE_H_

#include "define.h"
#include "cocos2d.h"

USING_NS_CC;

NS_AIRPLANE_BEGIN

class GameScene : public Scene {
public:
	GameScene() {}

	virtual bool init();

	CREATE_FUNC(GameScene);

private:

};

NS_AIRPLANE_END

#endif	// end _PLANE_GAMESCENE_H_