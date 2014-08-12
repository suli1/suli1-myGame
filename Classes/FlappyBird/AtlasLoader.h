#ifndef BIRD_ATLAS_LOADER
#define BIRD_ATLAS_LOADER

#include "cocos2d.h"

USING_NS_CC;


typedef struct _atlas {
	char name[255];
	int width;
	int height;
	Point start;
	Point end;
}Atlas;


// 专门处理图片资源的获取
// 全局共享，设计成单例

class AtlasLoader {
public:
	static AtlasLoader* getInstance();

	static void destoryInstance();

	void loadAtls(std::string filename);
	void loadAtlas(std::string filename, Texture2D *texture);

	SpriteFrame* getSpriteFrameByName(std::string name);
protected:
	AtlasLoader();

	virtual bool init();


	static AtlasLoader* s_sharedAtlasLoader;

	Map<std::string, SpriteFrame*> _spriteFrames;

};

#endif