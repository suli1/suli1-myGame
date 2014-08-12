#ifndef _PLANE_GAME_LAYER_H_
#define _PLANE_GAME_LAYER_H_

#include "define.h"
#include "cocos2d.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"

USING_NS_CC;

NS_AIRPLANE_BEGIN

#define EASY			0
#define MIDDLE			1
#define HARD			2

class GameLayer : public Layer {
public:
	GameLayer();

	virtual bool init();

	CREATE_FUNC(GameLayer);

	static int getCurLevel() { return _curLevel; }

protected:
	void onTouchesBegan(const std::vector<Touch*>& touches, Event* event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event* event);

	void update(float dt) override;

private:
	void backgroundMove(float dt);

private:
	Sprite*			_background1;
	Sprite*			_background2;
	BulletLayer*	_bulletLayer;
	EnemyLayer*		_enemyLayer;

	static int		_curLevel;

	int				_score;
};


NS_AIRPLANE_END

#endif	// end _PLANE_GAME_LAYER_H_