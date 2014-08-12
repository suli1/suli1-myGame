#ifndef _PLANE_ENEMY_H_
#define _PLANE_ENEMY_H_ 

#include "cocos2d.h"

USING_NS_CC;


class Enemy : public Node {
public:
	Enemy();
	~Enemy();

	static Enemy* create();

	void bindSprite(Sprite* sprite, int life);

	Sprite* getSprite() { return _sprite; }

	int getLife();

	void loseLife();

	Rect getBoundingBox();


private:
	Sprite*			_sprite;			//
	int				_life;

};


#endif // end _PLANE_ENEMY_H_
