#ifndef _ALG_MAP_SCENE_H_
#define _ALG_MAP_SCENE_H_

#include "../GameBasic.h"

class AlgorithmScene : public GameBasicScene
{
public:
    virtual void runThisGame() override;

private:
    void setSearchPath();
};


#endif // end _ALG_MAP_SCENE_H_