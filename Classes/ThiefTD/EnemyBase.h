#ifndef _TD_ENEMY_BASE_H_
#define  _TD_ENEMY_BASE_H_

#include "cocos2d.h"

USING_NS_CC;

class EnemyBase : public Node
{
public:
    CREATE_FUNC(EnemyBase);

protected:
    EnemyBase();

    virtual bool init() override;


public:
    virtual void changeDirection(float dt) {}

    virtual void enemyExpload() {}

    Animation* createAnimation(std::string prefixName, int framesNum, float delay);

    Node* currPoint();
    Node* nextPoint();

    void runFllowPoint();

    void setPointsVector(const Vector<Node*>& points);

    void createAndSetHpBar();

private:

private:
    Vector<Node*>       _vPoints;
protected:
    int                 _pointCounter;
    Animation*          _animationRight;
    Animation*          _animationLeft;
    Animation*          _animationExplode;

    Sprite*             _spriteHpBg;        // ÑªÌõ±³¾°
    ProgressTimer*      _hpBar;             // ÑªÌõ
    float               _hpPercentage;


    CC_SYNTHESIZE(int, _maxHp, MaxHp);
    CC_SYNTHESIZE(int, _currHp, CurrHp);
    CC_SYNTHESIZE(float, _runSpeed, RunSpeed);
    CC_SYNTHESIZE(Sprite*, _spriteBody, SpriteBody);
};


#endif // end _TD_ENEMY_BASE_H_