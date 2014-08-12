#ifndef _TD_TOWER_PANEL_LAYER_
#define _TD_TOWER_PANEL_LAYER_

#include "cocos2d.h"

USING_NS_CC;

// ������������
typedef enum {
    ARROW_TOWER = 0,
    ATTACK_TOWER,
    MULTIDIR_TOWER,
    ANOTHER
}TowerType;

class TowerPanelLayer : public Layer
{
public:
    CREATE_FUNC(TowerPanelLayer);

protected:
    TowerPanelLayer();

    virtual bool init() override;

    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    virtual void onTouchEnded(Touch *touch, Event *event) override;

    CC_SYNTHESIZE(TowerType, _chooseTowerType, ChooseTowerType);

private:
    Sprite*     _spriteArrow;           // ����
    Sprite*     _spriteAttack;          // ������
    Sprite*     _spriteMulitdir;        // �෽�򹥻���
};


#endif // end _TD_TOWER_PANEL_LAYER_