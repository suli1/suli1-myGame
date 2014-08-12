#ifndef _SMALL_GAME_CONTROLLER_H_
#define _SMALL_GAME_CONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class GameController: public Layer
{
public:
	GameController();
	~GameController();

	void addConsoleAutoGame();

protected:
	void menuCallback(Ref* sender);
	void menuCloseCallback(Ref* sender);

private:
	Menu*	_itemMenu;

};


#endif // end _SMALL_GAME_CONTROLLER_H_