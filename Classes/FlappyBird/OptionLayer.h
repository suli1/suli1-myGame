/* 控制层
 * 该层主要是响应OnTouch事件， 以实现游戏当中控制小鸟的飞行轨迹的目的
 *
 *
*/



#ifndef BIRD_OPTION_LAYER
#define BIRD_OPTION_LAYER

#include "cocos2d.h"

USING_NS_CC;

class OptionDelegate
{
public:
	virtual void onTouch() = 0;
};

class OptionLayer:public Layer
{
public:
	OptionLayer() {}
	~OptionLayer() {}

	virtual bool init();
	CREATE_FUNC(OptionLayer);

	// override
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *event) override;

	CC_SYNTHESIZE(OptionDelegate*, delegator, Delegator);
};

#endif