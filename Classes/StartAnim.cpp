#include "StartAnim.h"
#include "MyGame.h"
#include "LocalUtil.h"
USING_NS_CC;
bool StartAnim::init(){
	if(!CCLayer::init())return false;
	createLevelText();
	createTargetScoreText();
	schedule(schedule_selector(StartAnim::scheduleCallback),1.5f);
	return true;
}

void StartAnim::createLevelText(){
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	CCSize visibleSize=CCDirector::sharedDirector()->getVisibleSize();
	float cx = visibleSize.width*0.5f;
	float cy = visibleSize.height*0.5f;
	
	CCLayer* layer = CCLayer::create();
	this->addChild(layer);

	//���ֲ���
	std::string str=LocalUtil::getInstance()->getKeyString("level");
	str+="  ";
	std::string fontFile=isCn?(isTaiwanCn?"fonts/jianzhi_taiwancn.ttf":"fonts/jianzhi.ttf"):"fonts/haibao.ttf";
	Label*label_a=Label::createWithTTF(str,fontFile,40);
	label_a->setAnchorPoint(Vec2(0.0f,0.5f));
	layer->addChild(label_a);

	//���ֲ���
	str=Value(MyGame::getInstance()->getLevel()).asString();
	Label*label_b=Label::createWithTTF(str,"fonts/jianzhi.ttf",40);
	label_b->setAnchorPoint(Vec2(0.0f,0.5f));
	label_b->setPosition(Vec2(label_a->getContentSize().width,0.0f));
	layer->addChild(label_b);

	//����
	float totalW = label_a->getContentSize().width+label_b->getContentSize().width;
	label_a->setPositionX(label_a->getPositionX()-totalW*0.5f);
	label_b->setPositionX(label_b->getPositionX()-totalW*0.5f);
	//��С
	float scale = 1.0f;
	layer->setScale(scale);
	layer->setPosition(ccp(visibleSize.width*scale,(cy+30)*scale));//��������Ļ�ұ�
	//ִ�ж���
	CCMoveTo* moveTo0 = CCMoveTo::create(0.25,ccp(cx*scale,(cy+30)*scale));
	CCMoveTo* moveTo1 = CCMoveTo::create(0.25,ccp(-totalW*scale,(cy+30)*scale));
	CCSequence* actionSequence = CCSequence::create(moveTo0,CCDelayTime::create(1.0f),moveTo1,NULL);
	layer->runAction(actionSequence);
}

void StartAnim::createTargetScoreText(){
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	CCSize visibleSize=CCDirector::sharedDirector()->getVisibleSize();
	float cx = visibleSize.width*0.5f;
	float cy = visibleSize.height*0.5f;

	CCLayer* layer = CCLayer::create();
	this->addChild(layer);
	//���ֲ���
	std::string str=LocalUtil::getInstance()->getKeyString("targetScore");
	std::string fontFile=isCn?(isTaiwanCn?"fonts/jianzhi_taiwancn.ttf":"fonts/jianzhi.ttf"):"fonts/haibao.ttf";
	Label*label_a=Label::createWithTTF(str,fontFile,40);
	label_a->setAnchorPoint(Vec2(0.0f,0.5f));
	layer->addChild(label_a);

	//���ֲ���
	str=Value(MyGame::getInstance()->getTargetScore()).asString();
	Label*label_b=Label::createWithTTF(str,"fonts/jianzhi.ttf",40);
	label_b->setAnchorPoint(Vec2(0.0f,0.5f));
	label_b->setPosition(Vec2(label_a->getContentSize().width,0.0f));
	layer->addChild(label_b);

	//����
	float totalW = label_a->getContentSize().width+label_b->getContentSize().width;
	label_a->setPositionX(label_a->getPositionX()-totalW*0.5f);
	label_b->setPositionX(label_b->getPositionX()-totalW*0.5f);
	//��С
	float scale = 0.8f;
	layer->setScale(scale);
	layer->setPosition(ccp(visibleSize.width*scale,(cy-30)*scale));//��������Ļ�ұ�
	//ִ�ж���
	CCMoveTo* moveTo0 = CCMoveTo::create(0.25,ccp(cx*scale,(cy-30)*scale));
	CCMoveTo* moveTo1 = CCMoveTo::create(0.25,ccp(-totalW*scale,(cy-30)*scale));
	CCSequence* actionSequence = CCSequence::create(CCDelayTime::create(0.25f),moveTo0,CCDelayTime::create(0.75f),moveTo1,NULL);
	layer->runAction(actionSequence);
}

void StartAnim::scheduleCallback(float t){
	unschedule(schedule_selector(StartAnim::scheduleCallback));
	this->removeFromParentAndCleanup(true);
}