#ifndef _PLANE_BULLET_LAYER_H_
#define _PLANE_BULLET_LAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class BulletLayer : public Layer {
public:
	BulletLayer() {}

	virtual bool init();

	CREATE_FUNC(BulletLayer);

	void startShoot(float delay = 0.01f);
	void stopShoot();

	void removeBullet(Sprite* bullet);

private:
	void addBullet(float dt);

	void bulletMoveFinished(Node* pSender);

private:
	SpriteBatchNode*	_bulletBatchNode;

	Vector<Sprite*>		_vAllBullet;
};


#endif // end _PLANE_BULLET_LAYER_H_
