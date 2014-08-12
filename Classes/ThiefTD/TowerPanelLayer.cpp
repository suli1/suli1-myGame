#include "TowerPanelLayer.h"


TowerPanelLayer::TowerPanelLayer()
    : _spriteArrow(nullptr)
    , _spriteAttack(nullptr)
    , _spriteMulitdir(nullptr)
{

}

bool TowerPanelLayer::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(!Layer::init());

        setChooseTowerType(TowerType::ANOTHER);

        auto spriteTowerPos = Sprite::createWithSpriteFrameName("towerPos.png");
        spriteTowerPos->setPosition(0, 0);
        this->addChild(spriteTowerPos);

        _spriteAttack = Sprite::createWithSpriteFrameName("AttackTower1.png");
        _spriteAttack->setAnchorPoint(Point(0.5f, 0));
        _spriteAttack->setPosition(Point(0, spriteTowerPos->getContentSize().height/2));
        this->addChild(_spriteAttack);

        _spriteArrow = Sprite::createWithSpriteFrameName("ArrowTower1.png");
        _spriteArrow->setAnchorPoint(Point(0.5f, 0));
        _spriteArrow->setPosition(Point(-_spriteAttack->getContentSize().width, spriteTowerPos->getContentSize().height/2));
        this->addChild(_spriteArrow);

        _spriteMulitdir = Sprite::createWithSpriteFrameName("MultiDirTower1.png");
        _spriteMulitdir->setAnchorPoint(Point(0.5f, 0));
        _spriteMulitdir->setPosition(Point(_spriteAttack->getContentSize().width, spriteTowerPos->getContentSize().height/2));
        this->addChild(_spriteMulitdir);

        // ����¼�����
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true); // ���ò������´��ݴ���
        touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanelLayer::onTouchBegan, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanelLayer::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, _spriteArrow);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), _spriteAttack);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), _spriteMulitdir);

        bRet = true;
    } while (0);

    return bRet;
}

// �����ѡ��ʱ������������͸���ȣ��������ѡ��
bool TowerPanelLayer::onTouchBegan(Touch *touch, Event *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());
    Point locationInNode = target->convertTouchToNodeSpace(touch);
    Size size = target->getContentSize();
    Rect rect(0, 0, size.width, size.height);

    if(rect.containsPoint(locationInNode)) {
        target->setOpacity(180);
        return true;
    }

    return false;
}

// ������ɿ���ʱ��ȷ����ѡ�еķ���������
void TowerPanelLayer::onTouchEnded(Touch *touch, Event *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    if(target == _spriteArrow) {
        _chooseTowerType = ARROW_TOWER;
    } else if(target == _spriteAttack) {
        _chooseTowerType = ATTACK_TOWER;
    } else if(target == _spriteMulitdir) {
        _chooseTowerType = MULTIDIR_TOWER;
    } else {
        _chooseTowerType = ANOTHER;
    }

}

