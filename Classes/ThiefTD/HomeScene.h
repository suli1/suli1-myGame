#ifndef _TD_HOME_SCENE_H_
#define _TD_HOME_SCENE_H_


#include "../GameBasic.h"
#include "../define.h"

NS_TD_BEGIN

class HomeScene : public GameBasicScene
{
public:
    CREATE_FUNC(HomeScene);

protected:
    virtual bool init() override;

    virtual void runThisGame() override;
};

NS_TD_END

#endif // end _TD_HOME_SCENE_H_