#ifndef BIRD_BIRD_SPRITE
#define BIRD_BIRD_SPRITE

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

const int BIRD_SPRITE_TAG = 10003;

class BirdSprite : public Sprite {
public:
	typedef enum{
		ACTION_STATE_IDLE,
		ACTION_STATE_FLY,
		ACTION_STATE_DIE
	}ActionState;

	static BirdSprite* getInstance();

	virtual bool init();

	// create and init the bird
	bool createBird();

	// 小鸟飞翔通过摆动翅膀， 但不受重力影响
	void idle();

	// 小鸟飞翔通过玩家驱动, 受重力影响，需要物理支持
	void fly();

	// 小鸟死亡
	void die();

protected:
	static Animation *createAnimation(const char* fmt, int count, float fps);

	void createBirdRandom();

private:
	bool changeState(ActionState state);

	static BirdSprite* s_shareBirdSprite;

	Action* _idleAction;
	Action* _swingAction;

	ActionState _currentStatus;

	string _birdName;
	string _birdNameFormat;

	unsigned int _isFirstTime;

};




#endif