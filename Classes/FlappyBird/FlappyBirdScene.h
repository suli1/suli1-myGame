#ifndef _FLAPPY_BIRD_H_
#define _FLAPPY_BIRD_H_

#include "../GameBasic.h"


class FlappyBirdScene : public GameBasicScene
{
public:
	FlappyBirdScene();

	virtual void runThisGame() override;

};


#endif // end _FLAPPY_BIRD_H_