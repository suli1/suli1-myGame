#ifndef _ALG_MAP_LAYER_H_
#define _ALG_MAP_LAYER_H_

#include "cocos2d.h"
#include "Astar.h"

USING_NS_CC;

class MapLayer : public Layer
{
public:
    CREATE_FUNC(MapLayer);

protected:
    MapLayer();
    ~MapLayer();

    virtual bool init() override;

    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;

    void update(float dt) override;

    Point convertTo2d(Point position);

private:
    Sprite*         _tamara;
    Astar*          _myAstar;

    int             _vmove;
    int             _hmove;
    int             _stepIndex;
    int             _smallStepIndex;

    __Array*        _path;

};

#endif // end _ALG_MAP_LAYER_H_