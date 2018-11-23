#include "GoodEffect.h"

void GoodEffect::initInstance(const char* fileName){
	CCSprite* sp0=CCSprite::create(fileName);
	sp0->setOpacity(0);
	addChild(sp0);
	CCScaleTo* scaleTo = CCScaleTo::create(0.3f,5,5);
	sp0->runAction(scaleTo);
	CCFadeIn* fadeIn0 = CCFadeIn::create(0.1f);
	CCFadeOut* fadeOut0 = CCFadeOut::create(0.1f);
	CCSequence* seq0 = CCSequence::create(fadeIn0,CCDelayTime::create(0.1f),fadeOut0,NULL);
	sp0->runAction(seq0);

	CCSprite* sp1 = CCSprite::create(fileName);
	sp1->setScale(0.01f);
	addChild(sp1);
	CCScaleTo* scaleTo1_0 = CCScaleTo::create(0.1f,1.2f,1.2f);
	CCScaleTo* scaleTo1_1 = CCScaleTo::create(0.1f,1.0f,1.0f);
	CCFadeOut* fadeOut1 = CCFadeOut::create(0.1f);
	CCSequence* seq1 = CCSequence::create(scaleTo1_0,scaleTo1_1,CCDelayTime::create(0.8f),fadeOut1,NULL);
	sp1->runAction(seq1);

	scheduleOnce(schedule_selector(GoodEffect::animationComplete),1.5f);
}

void GoodEffect::animationComplete(float t){
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
}