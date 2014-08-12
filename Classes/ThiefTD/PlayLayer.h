#ifndef _TD_PLAYER_H_
#define _TD_PLAYER_H_

#include "cocos2d.h"
#include "TowerPanelLayer.h"

USING_NS_CC;


#define  ZORDER_BG          -20
#define  ZORDER_MAP         -10
#define  ZORDER_THIEF       10
#define  ZORDER_PLANEL      20


class TowerBase;

class PlayLayer : public Layer
{
public:
    CREATE_FUNC(PlayLayer);

protected:
    PlayLayer();

    ~PlayLayer();

    virtual bool init();

    bool onTouchBegan(Touch *touch, Event *unused_event) override;

    virtual void update(float delay) override;

private:
    // 初始化Ojb层(Enemy运动轨迹)PointVector
    void initPointsVector(float offX);

    // 添加炮塔选择面板
    void addTowerChoosePanel(Point position);

    // 检测是否能添加炮塔到Panle，能则添加，否则提示no
    void checkAndAddTowerPanle(Point position);

    // 将本地坐标(OpenGL坐标)转换为地图坐标
    Point convertToTileCoord(Point position);

    // 将本地坐标(OpenGL坐标)转换为数组坐标
    Point convertToMatrixCoord(Point position);

    // 添加防御塔，用于在update中更新
    void addTower();

    // 按不同关卡需求添加敌人
    void addEnemy();

    // 敌人与子弹的碰撞检测
    void collisionDetection();

    // 游戏逻辑规则刷新函数
    void logic(float dt);
      
private:
    TMXLayer*           _bgLayer;
    TMXTiledMap*        _map;
    TMXObjectGroup*     _objects;

    TowerPanelLayer*    _chooseTowerPanel;


    Vector<Node*>       _vPoints;

    TowerBase**               _towerMatrix;

    float               _offX;

    Point               _towerPos;      // 在地图上添加箭塔的位置

    int                 _money;
};


#endif // end _TD_PLAYER_H_
