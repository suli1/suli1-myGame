// 数字类的封装
// 用图片来显示分数等


#ifndef BIRD_NUMBER
#define BIRD_NUMBER

#include "cocos2d.h"

USING_NS_CC;

typedef enum _gravity {
	GRAVITY_CENTER = 1,
	GRAVITY_LEFT,
	GRAVITY_RIGHT
}Gravity;


// 两个数之间的距离
const int Numberinterval = 4;

class NumberSeries : public Ref {
public:
	NumberSeries() {}
	~NumberSeries() {}
	
	virtual bool init();

	CREATE_FUNC(NumberSeries);

	void loadNumber(const char *fmt, int base = 0);

	SpriteFrame* at(int index);

private:
	Vector<SpriteFrame*> _numberSeries;
};

class Number {
public:
	static Number* getInstance();
	static void destroyInstance();

	virtual bool init();

	virtual bool loadNumber(const char* name, const char* fmt, int base = 0);

	Node* convert(const char* name, int number, Gravity gravity = Gravity::GRAVITY_CENTER);

private:
	Map<std::string, NumberSeries*> _numberContainer;

	static Number*					s_shareNumber;
};

#endif