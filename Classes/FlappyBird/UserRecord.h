// 
// 以XML格式将数据保存在本地
//

#ifndef BIRD_USER_RECORD
#define BIRD_USER_RECORD

#include "cocos2d.h"

USING_NS_CC;

class UserRecord : public Ref {
public:
	static UserRecord* getInstance();
	static void destoryInstance();

	virtual bool init();

	void saveIntegerToUserDefault(const char* key, int value);

	int readIntegerFromUserDefault(const char* key);

private:
	static UserRecord*	s_shareUserRecord;
};

#endif