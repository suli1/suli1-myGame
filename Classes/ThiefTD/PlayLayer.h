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
    // ��ʼ��Ojb��(Enemy�˶��켣)PointVector
    void initPointsVector(float offX);

    // �������ѡ�����
    void addTowerChoosePanel(Point position);

    // ����Ƿ������������Panle��������ӣ�������ʾno
    void checkAndAddTowerPanle(Point position);

    // ����������(OpenGL����)ת��Ϊ��ͼ����
    Point convertToTileCoord(Point position);

    // ����������(OpenGL����)ת��Ϊ��������
    Point convertToMatrixCoord(Point position);

    // ��ӷ�������������update�и���
    void addTower();

    // ����ͬ�ؿ�������ӵ���
    void addEnemy();

    // �������ӵ�����ײ���
    void collisionDetection();

    // ��Ϸ�߼�����ˢ�º���
    void logic(float dt);
      
private:
    TMXLayer*           _bgLayer;
    TMXTiledMap*        _map;
    TMXObjectGroup*     _objects;

    TowerPanelLayer*    _chooseTowerPanel;


    Vector<Node*>       _vPoints;

    TowerBase**               _towerMatrix;

    float               _offX;

    Point               _towerPos;      // �ڵ�ͼ����Ӽ�����λ��

    int                 _money;
};


#endif // end _TD_PLAYER_H_
