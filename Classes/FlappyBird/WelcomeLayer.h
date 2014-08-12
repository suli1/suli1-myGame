#ifndef BIRD_WELCOME_LAYER
#define BIRD_WELCOME_LAYER

#include "define.h"
#include "cocos2d.h"
#include "BirdSprite.h"

USING_NS_CC;

NS_FLAPPYBIRD_BEGIN

const int START_BUTTON_TAG = 100;

class WelcomeLayer : public Layer {
public:
	WelcomeLayer(){}
	~WelcomeLayer(){}

	virtual bool init();

	CREATE_FUNC(WelcomeLayer);
	
private:
	void menuStartCallback(Ref *sender);
	void scrollLand(float dt);

private:
	Sprite* _land1;
	Sprite* _land2;
	BirdSprite*_bird;
};

NS_FLAPPYBIRD_END

#endif
