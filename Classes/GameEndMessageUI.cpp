#include "GameEndMessageUI.h"
#include <iostream>
#include <string>
#include "LocalUtil.h"
using namespace std;

bool GameEndMessageUI::init(){
	if(!CCLayer::init())return false;
	_instance=this;
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	std::string fontFile=isCn?(isTaiwanCn?"fonts/jianzhi_taiwancn.ttf":"fonts/jianzhi.ttf"):"fonts/haibao.ttf";
	//奖励分数
	std::string str_rewardScore =LocalUtil::getInstance()->getKeyString("rewardScore");
	_labelRewardScore = Label::createWithTTF(str_rewardScore,fontFile,40);
	_labelRewardScore->setScale(0.7f);
	_labelRewardScore->setPositionY(18);
	addChild(_labelRewardScore);
	//剩下的星星
	std::string str_remainStars = LocalUtil::getInstance()->getKeyString("remainStars");
	_labelRemainStars = Label::createWithTTF(str_remainStars,fontFile,40);
	_labelRemainStars->setScale(0.7f);
	_labelRemainStars->setPositionY(-18);
	addChild(_labelRemainStars);
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	setPosition(ccp(visibleSize.width+boundingBox().size.width*0.5,visibleSize.height*0.5f));

	CCMoveTo* moveIn = CCMoveTo::create(0.25f,ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	runAction(moveIn);

	return true;
}

void GameEndMessageUI::moveOut(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCMoveTo* moveOut = CCMoveTo::create(0.25f,ccp(-boundingBox().size.width*0.5,visibleSize.height*0.5f));
	runAction(moveOut);
	scheduleOnce(schedule_selector(GameEndMessageUI::dispose),0.25f);
}

void GameEndMessageUI::dispose(float t){
	removeFromParentAndCleanup(true);
}


void GameEndMessageUI::setRemainStars(int value){
	std::string str_remainStars=LocalUtil::getInstance()->getKeyString("remainStars");
	std::string str_count = Value(value).asString();
	log("str_remainStars:%s",str_remainStars.c_str());
	std::string newStr=str_remainStars;
	//log("newStr string:%s",newStr);
	newStr+=str_count;
	_labelRemainStars->setString(newStr);
}

void GameEndMessageUI::updateLabelReWardScore(int value){
	std::string str_rewardScore=LocalUtil::getInstance()->getKeyString("rewardScore");
	std::string str_count=Value(value).asString();
	std::string newStr=str_rewardScore;
	newStr+=str_count;
	_labelRewardScore->setString(newStr);
}

void GameEndMessageUI::setRewardScore(int value){
	_rewardScore=value;
	updateLabelReWardScore(value);
}

int GameEndMessageUI::getRewardScore(){
	return _rewardScore;
}

GameEndMessageUI* GameEndMessageUI::_instance=NULL;
GameEndMessageUI* GameEndMessageUI::getInstance(){
	return _instance;
}
GameEndMessageUI::~GameEndMessageUI(){
	_instance=NULL;
}