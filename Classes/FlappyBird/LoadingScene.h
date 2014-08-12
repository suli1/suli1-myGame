// 程序的loading界面

#ifndef BIRD_LOADING_SCENE
#define BIRD_LOADING_SCENE

#include "define.h"
#include "cocos2d.h"

USING_NS_CC;

NS_FLAPPYBIRD_BEGIN

class LoadingScene: public Scene {
public:
	LoadingScene(){}
	~LoadingScene(){}

	virtual bool init() override;

	CREATE_FUNC(LoadingScene);

	// 当scene出现时，将会调用改方法而不是scene被创建时
	virtual void onEnter() override;


private:
	// called when the texture(exp.atlas.png) is loading finish
	void loadingCallBack(Texture2D *texture);


};

NS_FLAPPYBIRD_END


#endif