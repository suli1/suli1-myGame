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

	// С�����ͨ���ڶ���� ����������Ӱ��
	void idle();

	// С�����ͨ���������, ������Ӱ�죬��Ҫ����֧��
	void fly();

	// С������
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