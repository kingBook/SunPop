#ifndef __GOOD_EFFECT_H__
#define __GOOD_EFFECT_H__
#include "MyGame.h"

USING_NS_CC;

class GoodEffect:public cocos2d::CCLayer{
public:
	void initInstance(const char* fileName);
	CREATE_FUNC(GoodEffect);
private:
	void animationComplete(float t);
};
#endif