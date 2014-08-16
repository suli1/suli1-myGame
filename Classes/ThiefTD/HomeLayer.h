#ifndef _TD_HOME_LAYER_H_
#define _TD_HOME_LAYER_H_

// 塔防游戏开始的主界面

#include "cocos2d.h"
#include "../define.h"

USING_NS_CC;

NS_TD_BEGIN

class HomeLayer : public Layer
{
public:
    CREATE_FUNC(HomeLayer);
protected:

    virtual bool init() override;

    void menuStartCallback(Ref* pSender);
    //void menuCloseCallback(Ref* pSender);

    RepeatForever* myPathFun(float controlX, float controlY, float w);

private:


};

NS_TD_END


#endif // end _TD_HOME_SCENE_H_