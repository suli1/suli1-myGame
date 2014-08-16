#ifndef _SMALL_GAME_BASIC_H_
#define _SMALL_GAME_BASIC_H_

#include "cocos2d.h"

USING_NS_CC;

class GameBasicScene : public Scene
{
public: 
    GameBasicScene(bool bPortrait = false, bool physics = false);
    virtual void onEnter() override;

    virtual void runThisGame() = 0;
};

#endif // end _SMALL_GAME_BASIC