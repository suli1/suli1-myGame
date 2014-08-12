#ifndef BIRD_BACKGROUND_LAYER
#define BIRD_BACKGROUND_LAYER

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public Layer {
public:
	BackgroundLayer() {}
	~BackgroundLayer() {}

	virtual bool init();

	CREATE_FUNC(BackgroundLayer);

	static float getLandHeight();
};

#endif