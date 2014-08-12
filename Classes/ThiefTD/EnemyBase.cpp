#include "EnemyBase.h"


EnemyBase::EnemyBase()
    : _pointCounter(0)
    , _runSpeed(0)
    , _animationLeft(nullptr)
    , _animationRight(nullptr)
    , _maxHp(0)
    , _currHp(0)
    , _spriteBody(nullptr)
    , _hpPercentage(0.0f)
{

}

bool EnemyBase::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(!Node::init());

        bRet = true;
    } while (0);

    return bRet;
}

Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay)
{
    Vector<SpriteFrame*> vAnimFrames;

    for(int i = 1; i <= framesNum; i++) {
        char buffer[20] = {0};
        sprintf_s(buffer, "_%i.png", i);
        std::string str = prefixName + buffer;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        vAnimFrames.pushBack(frame);
    }

    return Animation::createWithSpriteFrames(vAnimFrames, delay);
}

Node* EnemyBase::currPoint()
{
    Node* curr = nullptr;
    if(_vPoints.size() > 0 && _vPoints.size() > _pointCounter) {
        curr = _vPoints.at(_pointCounter);
    }

    return curr;
}

Node* EnemyBase::nextPoint()
{
    Node* next = nullptr;

    if(++_pointCounter <  _vPoints.size()) {
        next = _vPoints.at(_pointCounter);
    } else {
        // 敌人成功到达基地
    }

    return next;
}

void EnemyBase::runFllowPoint()
{
    auto curr = currPoint();
    assert(curr != nullptr);
    //this->setPosition(curr->getPosition());
    _spriteBody->setPosition(curr->getPosition());

    auto next = nextPoint();
    if(next) {
        float duration = curr->getPosition().distance(next->getPosition()) / getRunSpeed();
        _spriteBody->runAction(Sequence::create(MoveTo::create(duration, next->getPosition()),
                                        CallFuncN::create(CC_CALLBACK_0(EnemyBase::runFllowPoint, this)), 
                                        nullptr));
    }
}

void EnemyBase::setPointsVector(const Vector<Node*>& points)
{
    _vPoints = points;
}

void EnemyBase::createAndSetHpBar()
{
    _spriteHpBg = Sprite::createWithSpriteFrameName("hpBg1.png");
    _spriteHpBg->setPosition(Point(_spriteBody->getContentSize().width/2, _spriteBody->getContentSize().height));
    _spriteBody->addChild(_spriteHpBg);

    _hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("hp1.png"));
    _hpBar->setType(ProgressTimer::Type::BAR);
    _hpBar->setMidpoint(Point(0, 0.5f));
    _hpBar->setBarChangeRate(Point(1, 0));
    _hpBar->setPercentage(_hpPercentage);
    _hpBar->setPosition(_spriteHpBg->getContentSize().width/2, _spriteHpBg->getContentSize().height/3*2);

    _spriteHpBg->addChild(_hpBar);
}
