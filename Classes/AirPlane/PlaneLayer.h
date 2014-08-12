#ifndef _PLANE_LAYER_H_
#define _PLANE_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

#define AIRPLANE 100

class PlaneLayer : public Layer {
public:
	static PlaneLayer* getInstance();

	virtual bool init();

	void MoveTo(Point location);

public:
	bool		_isAlive;

private:
	static PlaneLayer*	s_sharePlaneLayer;

	CC_SYNTHESIZE(int, _score, Score);
};

#endif // end _PLANE_LAYER_H_