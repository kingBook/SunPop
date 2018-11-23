#include "ScreenText.h"
#include "LocalUtil.h";

bool ScreenText::init(){
	if(!CCSprite::init())return false;
	
	
	return true;
}

void ScreenText::initInstance(const char* text){
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint pos = ccp(visibleSize.width*0.5f,575);//text position
	Label* label = Label::createWithTTF(text,isTaiwanCn?"fonts/haibao_taiwancn.ttf":"fonts/haibao.ttf",40);
	label->setTextColor(Color4B(255,255,0,255));
	label->setWidth(visibleSize.width);
	label->setScale(0.7f);
	label->setPosition(ccp(pos.x,pos.y-50));
	label->setOpacity(0);
	addChild(label);

	CCFadeIn* fadeIn = CCFadeIn::create(0.25f);
	CCFadeOut* fadeOut = CCFadeOut::create(0.25f);
	CCSequence* seq0 = CCSequence::create(fadeIn, CCDelayTime::create(1.0f),fadeOut,NULL);

	CCMoveTo* moveTo = CCMoveTo::create(0.25f,pos);
	CCMoveTo* moveOut = CCMoveTo::create(0.25f,ccp(pos.x,pos.y+50));
	CCSequence* seq1 = CCSequence::create(moveTo,CCDelayTime::create(1.0f),moveOut,CCCallFunc::create(this,callfunc_selector(ScreenText::animationComplete)),NULL);

	label->runAction(seq0);
	label->runAction(seq1);
}

void ScreenText::animationComplete(){
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
}