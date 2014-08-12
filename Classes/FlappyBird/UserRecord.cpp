#include "UserRecord.h"

UserRecord* UserRecord::s_shareUserRecord = NULL;


UserRecord* UserRecord::getInstance()
{
	if(NULL == s_shareUserRecord) {
		s_shareUserRecord = new UserRecord();
		if(!s_shareUserRecord->init()) {
			delete s_shareUserRecord;
			s_shareUserRecord = NULL;
		}
	}

	return s_shareUserRecord;
}

void UserRecord::destoryInstance()
{
	if(s_shareUserRecord) {
		delete s_shareUserRecord;
		s_shareUserRecord = NULL;
	}
}

bool UserRecord::init()
{
	return true;
}


void UserRecord::saveIntegerToUserDefault(const char* key, int value)
{
	UserDefault::getInstance()->setIntegerForKey(key, value);
}

int UserRecord::readIntegerFromUserDefault(const char* key)
{
	return UserDefault::getInstance()->getIntegerForKey(key);
}