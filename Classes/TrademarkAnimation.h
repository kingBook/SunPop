#ifndef __TRADEMARK_ANIMATION_H__
#define __TRADEMARK_ANIMATION_H__
#include "cocos2d.h"
USING_NS_CC;

class TrademarkAnimation : public cocos2d::CCLayer{
	private:
	std::function<void()> _completeCallback=nullptr;
	void createAnimate();
	void createBg();
public :
	~TrademarkAnimation();
	virtual bool init();
	void setCompleteCallback(const std::function<void()>& func);
	CREATE_FUNC(TrademarkAnimation);
};
#endif