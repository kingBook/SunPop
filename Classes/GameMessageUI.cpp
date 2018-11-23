#include "GameMessageUI.h"
#include "MyGame.h"
#include <iostream>
#include <string>
#include "LocalUtil.h"
using namespace std;

bool GameMessageUI::init(){
	if(!CCLayer::init())return false;
	_instance = this;
	createBg();
	createLabels();
	setPositionY(boundingBox().size.height);

	//暂停按钮
	CCMenuItemImage* pauseItem = CCMenuItemImage::create("Button_pause.png","Button_pause.png",this,menu_selector(GameMessageUI::pauseCallback));
	pauseItem->setPosition(Point(60,750));
	CCMenu* menu = CCMenu::create(pauseItem,NULL);
	menu->setPosition(Point());
	addChild(menu);

	//添加滑入动作
	CCMoveTo* moveTo = CCMoveTo::create(0.8f,Point());
	CCSequence* seq = CCSequence::create(CCDelayTime::create(0.1f),moveTo,NULL);
	runAction(seq);
	return true;
}

void GameMessageUI::createBg(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	float cx = visibleSize.width*0.5f;
	float cy = visibleSize.height*0.5f;
	CCSprite* bg = CCSprite::create("messageUI_bg.png");
	bg->setPosition(ccp(cx,visibleSize.height-bg->getContentSize().height*0.5f));
	this->addChild(bg);

}

void GameMessageUI::createLabels(){
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	float scale = 0.5f;
	if(isCn){
		//"第"
		std::string str_di=LocalUtil::getInstance()->getKeyString("di");
		Label*_label_di=Label::createWithTTF(str_di,isTaiwanCn?"fonts/jianzhi_taiwancn.ttf":"fonts/jianzhi.ttf",40);
		_label_di->setScale(scale);
		_label_di->setPosition(110.0f,750.0f);
		this->addChild(_label_di);
	}else{
		//"level"
		std::string str_lv=LocalUtil::getInstance()->getKeyString("level");
		Label*label_lv=Label::createWithTTF(str_lv,"fonts/haibao.ttf",15);
		label_lv->setPosition(150.0f,770.0f);
		this->addChild(label_lv);
	}
	//"1"
	std::string strLevel=Value(MyGame::getInstance()->getLevel()).asString();
	_labelLevel=Label::create(strLevel,"fonts/jianzhi.ttf",40);
	_labelLevel->setScale(scale);
	_labelLevel->setPosition(150.0f,750.0f);
	this->addChild(_labelLevel);
	if(isCn){
		//"关"
		std::string str_guan=LocalUtil::getInstance()->getKeyString("guan");
		Label*label_guan=Label::createWithTTF(str_guan,isTaiwanCn?"fonts/jianzhi_taiwancn.ttf":"fonts/jianzhi.ttf",40);
		label_guan->setScale(scale);
		label_guan->setPosition(190.0f,750.0f);
		this->addChild(label_guan);
	}
	//分数
	std::string char_score=Value(MyGame::getInstance()->getScore()).asString();
	_labelScore=Label::createWithTTF(char_score,"fonts/jianzhi.ttf",40);
	_labelScore->setScale(scale);
	_labelScore->setPosition(275.0f,752.0f);
	this->addChild(_labelScore);
	//"最高纪录"
	std::string str_maxRecord=LocalUtil::getInstance()->getKeyString("maxRecord");
	std::string fontFile=isCn?(isTaiwanCn?"fonts/jianzhi_taiwancn.ttf":"fonts/jianzhi.ttf"):"fonts/haibao.ttf";
	Label*label_maxRecord=Label::create(str_maxRecord,fontFile,40);
	label_maxRecord->setScale(0.4f);
	label_maxRecord->setPosition(398.0f,765.0f);
	this->addChild(label_maxRecord);
	//最高纪录分值
	std::string str_maxRecordScore=Value(MyGame::getInstance()->getMaxRecord()).asString();
	Label*label_maxRecordScore=Label::createWithTTF(str_maxRecordScore,"fonts/jianzhi.ttf",40);
	label_maxRecordScore->setScale(0.4f);
	label_maxRecordScore->setPosition(398.0f,740.0f);
	this->addChild(label_maxRecordScore);
	//目标:1000
	fontFile=isCn?(isTaiwanCn?"fonts/jianzhi_taiwancn.ttf":"fonts/jianzhi.ttf"):"fonts/haibao.ttf";
	std::string str_target=LocalUtil::getInstance()->getKeyString("mubiao");
	str_target+=LocalUtil::getInstance()->getKeyString("yinhao");
	str_target+=Value(MyGame::getInstance()->getTargetScore()).asString();

	Label*label_target=Label::createWithTTF(str_target,fontFile,40);
	label_target->setColor(Color3B(100,200,0));
	label_target->setScale(0.4f);
	label_target->setAnchorPoint(Vec2(0,0.5f));
	label_target->setPosition(Vec2(20,675));
	addChild(label_target);
}

void GameMessageUI::updateLabelLevelText(){
	std::string strLevel=Value(MyGame::getInstance()->getLevel()).asString();
	_labelLevel->setString(strLevel);
}

void GameMessageUI::updateLabelScoreText(){
	std::string str_score=Value(MyGame::getInstance()->getScore()).asString();
	_labelScore->setString(str_score);
}

float GameMessageUI::getScorePosX(){
	return _labelScore->getPositionX();
}

float GameMessageUI::getScorePosY(){
	return _labelScore->getPositionY();
}

void GameMessageUI::pauseCallback(CCObject* pSender){
	MyGame*game=MyGame::getInstance();
	if(game->getIsGameOver())return;
	if(game->getPause())return;
	CCLOG("%s","GameMessageUI::pauseCallback();");
	game->createPauseUI();
}

GameMessageUI::~GameMessageUI(){
	_instance=NULL;
}
GameMessageUI* GameMessageUI::_instance=NULL;
GameMessageUI* GameMessageUI::getInstance(){
	return _instance;
}

