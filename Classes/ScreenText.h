#ifndef __SCREEN_TEXT_H__
#define __SCREEN_TEXT_H__
#include "cocos2d.h"
USING_NS_CC;
class ScreenText:public cocos2d::CCSprite{
public:
	virtual bool init();
	void initInstance(const char* text);
	CREATE_FUNC(ScreenText);
private:
	void animationComplete();
};
#endif