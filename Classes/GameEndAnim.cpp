#include "GameEndAnim.h"
#include "MyGame.h"
#include "LocalUtil.h"

bool GameEndAnim::init(){
	if(!CCSprite::init())return false;
	_completeTarget=NULL;
	_completeCallFunc=NULL;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	CCSprite* sp = CCSprite::create(isCn?(isTaiwanCn?"gameOverText_taiwancn.png":"gameOverText.png"):"gameOverText_en.png");
	sp->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	sp->setOpacity(0);
	addChild(sp);

	CCFadeIn* fadeIn=CCFadeIn::create(0.1f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.5f,0.1f,0.1f);
	CCFadeOut* fadeOut = CCFadeOut::create(0.5f);
	CCSpawn* spawn = CCSpawn::create(scaleTo,fadeOut,NULL);
	CCSequence* seq1 = CCSequence::create(fadeIn,CCDelayTime::create(0.6f), spawn, CCCallFunc::create(this,callfunc_selector(GameEndAnim::animationComplete)),NULL);
	sp->runAction(seq1);
	
	return true;
}

void GameEndAnim::initInstance(CCObject* completeTarget, SEL_CallFunc completeCallFunc){
	_completeTarget = completeTarget;
	_completeCallFunc = completeCallFunc;
}

void GameEndAnim::animationComplete(){
	if(_completeTarget!=NULL&&_completeCallFunc!=NULL){
		(_completeTarget->*_completeCallFunc)();
	}
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);

	MyGame::getInstance()->createTitle(true,true);//清除当前分数，关卡，消毁关卡，返回标题
}