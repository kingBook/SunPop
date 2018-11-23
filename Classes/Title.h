#ifndef __TITLE_H__
#define __TITLE_H__
#include "cocos2d.h"
USING_NS_CC;

class Title : public cocos2d::CCLayer{
private:
	static Title* _instance;
	CCMenuItemImage* _shopOnceItem;
	void createBg();
	void createMenuItem();
	void startCallback(CCObject* pSender);
	void continueCallback(CCObject* pSender);
	void shopCallback(CCObject* pSender);
	void leaderboardCallback(CCObject* pSender);
	void shopOnceCallback(CCObject* pSender);
	void helpCallback(CCObject* pSender);
	void muteCallback(CCObject* pSender);
	bool _enabled;
public :
	~Title();
	virtual bool init();
	static Title* getInstance();
	void setEnabled(bool value);
	void hideShopOnceItem();//隐藏新手礼包按钮
	CREATE_FUNC(Title);
};
#endif