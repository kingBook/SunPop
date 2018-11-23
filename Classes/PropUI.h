#ifndef __PROP_UI_H__
#define __PROP_UI_H__
#include "cocos2d.h"
USING_NS_CC;

class PropUI : public cocos2d::CCLayer{
public:
	static PropUI* getInstance();
	~PropUI();
	virtual bool init();
	void setEnabled(bool value);
	void updateDiamondText();
	CREATE_FUNC(PropUI);
private:
	CCMenu* _menu;
	bool _enabled;
	Label* _diamondCountText;
	static PropUI* _instance;
	void createMenuItem();
	void randCallback(CCObject* pSender);
	void selectColorCallback(CCObject* pSender);
	void coinAddCallback(CCObject* pSender);
	void popOneCallback(CCObject* pSender);
	void addDiamondCallback(CCObject* pSender);
	void playerClickSound();
	void createScreenText(const char* stringKey);
};
#endif