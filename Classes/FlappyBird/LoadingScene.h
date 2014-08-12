// �����loading����

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

	// ��scene����ʱ��������øķ���������scene������ʱ
	virtual void onEnter() override;


private:
	// called when the texture(exp.atlas.png) is loading finish
	void loadingCallBack(Texture2D *texture);


};

NS_FLAPPYBIRD_END


#endif