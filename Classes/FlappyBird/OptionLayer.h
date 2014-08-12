/* ���Ʋ�
 * �ò���Ҫ����ӦOnTouch�¼��� ��ʵ����Ϸ���п���С��ķ��й켣��Ŀ��
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