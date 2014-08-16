#ifndef _TD_LOADING_SCENE_H_
#define _TD_LOADING_SCENE_H_

// 加载游戏资源

#include "cocos2d.h"
#include "../define.h"

USING_NS_CC;


NS_TD_BEGIN

class LoadingScene : public Scene
{
public:
    CREATE_FUNC(LoadingScene);

protected:
    LoadingScene();

    virtual bool init() override;

    virtual void onEnter() override;

    void loadResources();

    void loadingCallback(Texture2D* texture);

    void transitionScene();

private:
    ProgressTimer*      _progressBar;
    int                 _loadedResNum;
    int                 _loadedResTotal;
};

NS_TD_END


#endif //end _TD_LOADING_SCENE_H_