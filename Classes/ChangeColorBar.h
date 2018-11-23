#ifndef __CHANGE_COLOR_BAR_H__
#define __CHANGE_COLOR_BAR_H__
#include "cocos2d.h"
USING_NS_CC;

class ChangeColorBar:public cocos2d::CCLayer{
public:
	~ChangeColorBar();
	virtual bool init();
	virtual void onEnter();
	void initInstance(int curColor, int curPosId);
	CREATE_FUNC(ChangeColorBar);
private:
	CCSprite* _paintArrow;
	CCSprite* _bgRect;
	int _curColor;
	int _curPosId;
	CCMenu* _menu;
	void createPaintArrow();
	void createBgRect();
	void createMenuItems();
	void r_menuCallback(CCObject* pSender);
	void g_menuCallback(CCObject* pSender);
	void b_menuCallback(CCObject* pSender);
	void v_menuCallback(CCObject* pSender);
	void y_menuCallback(CCObject* pSender);
	void playSelectSound();
};
#endif