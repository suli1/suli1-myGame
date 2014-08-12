#ifndef _PLANE_ENEMY_LAYER_H_
#define _PLANE_ENEMY_LAYER_H_

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

#define ENEMY1_MAXLIFE		10
#define ENEMY2_MAXLIFE		15
#define ENEMY3_MAXLIFE		30

class EnemyLayer : public Layer {
public:
	EnemyLayer();

	virtual bool init();

	CREATE_FUNC(EnemyLayer);

	// 添加随机初始化位置和速度的敌机
	void addEnemy1(float dt);
	// 敌机1移动动画
	void enemy1MoveFinished(Node* pSender);
	// 敌机1爆炸
	void enemy1Blowup(Enemy* enemy1);
	// 移除单架敌机1
	void removeEnemy1(Node* pTarget);
	// 移除所有敌机1
	void removeAllEnemy1();

	void addEnemy2(float dt);
	void enemy2MoveFinished(Node* pSender);
	void enemy2Blowup(Enemy* enemy2);
	void removeEnemy2(Node* pTarget);
	void removeAllEnemy2();

	void addEnemy3(float dt);
	void enemy3MoveFinished(Node* pSender);
	void enemy3Blowup(Enemy* enemy3);
	void removeEnemy3(Node* pTarget);
	void removeAllEnemy3();

	void removeAllEnemy();


private:
	SpriteFrame*		_enemy1SpriteFrame;
	SpriteFrame*		_enemy2SpriteFrame;
	SpriteFrame*		_enemy3SpriteFrame_1;
	SpriteFrame*		_enemy3SpriteFrame_2;

	Vector<Enemy*>		_vAllEnemy1;
	Vector<Enemy*>		_vAllEnemy2;
	Vector<Enemy*>		_vAllEnemy3;

};

#endif // end _PLANE_ENEMY_LAYER_H_
