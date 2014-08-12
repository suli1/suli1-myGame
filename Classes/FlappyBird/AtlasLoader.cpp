#include "AtlasLoader.h"


AtlasLoader* AtlasLoader::s_sharedAtlasLoader = NULL;

AtlasLoader* AtlasLoader::getInstance()
{
	if(NULL == s_sharedAtlasLoader) {
		s_sharedAtlasLoader = new AtlasLoader();
		if(!s_sharedAtlasLoader->init()) {
			delete s_sharedAtlasLoader;
			s_sharedAtlasLoader = NULL;
			CCLOG("ERROR: Could not init AltasLoader");
		}
	}

	return s_sharedAtlasLoader;
}

void AtlasLoader::destoryInstance()
{
	CC_SAFE_DELETE(s_sharedAtlasLoader);
}

AtlasLoader::AtlasLoader()
{
}

bool AtlasLoader::init()
{
	return true;
}


void AtlasLoader::loadAtls(std::string filename)
{
	auto textureAtlas = Director::getInstance()->getTextureCache()->addImage("atlas.png");
	this->loadAtlas(filename, textureAtlas);
}

void AtlasLoader::loadAtlas(std::string filename, Texture2D *texture)
{
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	unsigned pos;
	Atlas atlas;
	pos = data.find_first_of("\n");
	std::string line = data.substr(0, pos);
	data = data.substr(pos + 1);
	while(line != "") {
		sscanf(line.c_str(), "%s %d %d %f %f %f %f",
			atlas.name, &atlas.width, &atlas.height,
			&atlas.start.x, &atlas.start.y,
			&atlas.end.x, &atlas.end.y);

		atlas.start.x *= 1024;
		atlas.start.y *= 1024;
		atlas.end.x *= 1024;
		atlas.end.y *= 1024;

		pos = data.find_first_of("\n");
		line = data.substr(0, pos);
		data = data.substr(pos + 1);

		// use the data to create a sprint frame
		// fix 1px edge bug
		if(atlas.name == std::string("land")) {
			atlas.start.x += 1;
		}
		Rect rect = Rect(atlas.start.x, atlas.start.y, atlas.width, atlas.height);
		auto frame = SpriteFrame::createWithTexture(texture, rect);
		this->_spriteFrames.insert(std::string(atlas.name), frame);
	}

}

SpriteFrame* AtlasLoader::getSpriteFrameByName(std::string name)
{
	return this->_spriteFrames.at(name);
}