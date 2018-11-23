#ifndef __HELP_UI_H__
#define __HELP_UI_H__
#include "cocos2d.h"
USING_NS_CC;
class HelpUI:public cocos2d::CCSprite{
public:
	~HelpUI();
	virtual bool init();
	CREATE_FUNC(HelpUI);
private:
	void closeCallback(CCObject* pSender);
};

#endif