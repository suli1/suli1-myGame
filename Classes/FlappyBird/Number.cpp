#include "Number.h"
#include "AtlasLoader.h"


/*
 * NumberSeries
*/

bool NumberSeries::init()
{
	this->_numberSeries = Vector<SpriteFrame*>(10);
	return true;
}

void NumberSeries::loadNumber(const char *fmt, int base /* = 0 */)
{
	for(int i = base; i < 10 + base; i++) {
		const char* filename = String::createWithFormat(fmt, i)->getCString();
		auto frame = AtlasLoader::getInstance()->getSpriteFrameByName(filename);
		_numberSeries.pushBack(frame);
	}

}


SpriteFrame* NumberSeries::at(int index)
{
	return this->_numberSeries.at(index);
}



/*
 * Number
*/

Number* Number::s_shareNumber = NULL;


Number* Number::getInstance()
{
	if(NULL == s_shareNumber) {
		s_shareNumber = new Number();
		if(!s_shareNumber->init()) {
			delete s_shareNumber;
			s_shareNumber = NULL;
		}
	}

	return s_shareNumber;
}

void Number::destroyInstance()
{
	CC_SAFE_DELETE(s_shareNumber);
}

bool Number::init()
{
	return true;
}

bool Number::loadNumber(const char* name, const char* fmt, int base /* = 0 */)
{
	auto numberSeries = NumberSeries::create();
	numberSeries->loadNumber(fmt, base);
	_numberContainer.insert(name, numberSeries);
	return true;
}


Node* Number::convert(const char* name, int number, Gravity gravity /* = Gravity::GRAVITY_CENTER */)
{
	auto numbers = _numberContainer.at(name);
	if (number == 0) {
		auto numberZero = Sprite::createWithSpriteFrame(numbers->at(0));
		numberZero->setAnchorPoint(Point(0.5, 0));
		return numberZero;
	}

	auto numberNode = Node::create();
	float totalWidth = 0;
	while(number){
		int temp = number % 10;
		number /= 10;
		auto sprite = Sprite::createWithSpriteFrame(numbers->at(temp));
		totalWidth += sprite->getContentSize().width;
		numberNode->addChild(sprite);
	}

	auto numberZero = Sprite::createWithSpriteFrame(numbers->at(0));
	numberNode->setContentSize(Size(totalWidth, numberZero->getContentSize().height));

	if(gravity == Gravity::GRAVITY_CENTER) {
		float singleWidth = totalWidth/numberNode->getChildrenCount();
		int index = numberNode->getChildrenCount()/2;
		for(auto child : numberNode->getChildren()) {
			child->setAnchorPoint(Point(0.5, 0));
			float offLength = singleWidth*index--;
			child->setPositionX(offLength);
		}
	}else if(gravity == Gravity::GRAVITY_RIGHT) {
		float singleWidth = totalWidth/numberNode->getChildrenCount();
		int index = numberNode->getChildrenCount();
		for(auto child : numberNode->getChildren()) {
			child->setAnchorPoint(Point(1, 0));
			float offLength = singleWidth*index--;
			child->setPositionX(offLength);
		} 
	}else if(gravity == Gravity::GRAVITY_LEFT) {
		float singleWidth = totalWidth/numberNode->getChildrenCount();
		int index = 0;
		for(auto child : numberNode->getChildren()) {
			child->setAnchorPoint(Point::ZERO);
			float offLength = singleWidth*index++;
			child->setPositionX(offLength);
		} 
	}

	return numberNode;
}





