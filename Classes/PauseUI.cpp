#include "PauseUI.h"
#include "MyGame.h"
#include "PropUI.h"
#include "LocalUtil.h"

bool PauseUI::init(){
	if(!CCSprite::init())return false;
	MyGame::getInstance()->setPause(true);
	if(PropUI::getInstance()!=NULL){
		PropUI::getInstance()->setEnabled(false);
	}
	//
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//创建背景
	CCLayerColor* bgColor = CCLayerColor::create(ccc4(0,0,0,125));
	bgColor->setPosition(ccp(-visibleSize.width*0.5f,-visibleSize.height*0.5f));
	addChild(bgColor);
	
	CCSprite* bg = CCSprite::create("bagBg.png");
	addChild(bg);

	CCSprite* caiDai = CCSprite::create("caiDai.png");
	caiDai->setPositionY(211);
	addChild(caiDai);

	//暂停
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath=isTaiwanCn?"fonts/haibao_taiwancn.ttf":"fonts/haibao.ttf";
	ttfConfig.fontSize=isCn?50:40;
	ttfConfig.distanceFieldEnabled=true;
	std::string strTitle=LocalUtil::getInstance()->getKeyString("pause",true);
	Label*bgTitleLabel=Label::createWithTTF(ttfConfig,strTitle);
	bgTitleLabel->enableOutline(Color4B(0,100,0,255),2);
	bgTitleLabel->enableShadow(Color4B(0,30,0,255));
	bgTitleLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	bgTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
	bgTitleLabel->setPosition(0,246.8f);
	addChild(bgTitleLabel);


	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png","close.png",this,menu_selector(PauseUI::continueCallback));
	closeItem->setPosition(ccp(-170,201));

	//继续按钮
	std::string continueFile=isCn?(isTaiwanCn?"continueGame_taiwancn.png":"continueGame.png"):"continueGame_en.png";
	CCMenuItemImage* continueItem = CCMenuItemImage::create(continueFile,continueFile,this,menu_selector(PauseUI::continueCallback));
	continueItem->setPositionY(60);
	continueItem->setScale(1.2f);

	//按钮缩放动作
	CCScaleTo* scaleTo_a=CCScaleTo::create(0.5f,1.0f,1.0f);
	CCScaleTo* scaleTo_b=CCScaleTo::create(0.5f,1.2f,1.2f);
	CCSequence* scaleSeq = CCSequence::create(scaleTo_a,scaleTo_b,NULL);
	CCRepeatForever* repeatForever=CCRepeatForever::create(scaleSeq);
	continueItem->runAction(repeatForever);

	std::string backFile=isCn?"back.png":"back_en.png";
	CCMenuItemImage* backItem = CCMenuItemImage::create(backFile,backFile,this,menu_selector(PauseUI::backCallback));
	backItem->setPositionY(-60);

	CCMenu* menu =CCMenu::create(closeItem,continueItem,backItem,NULL);
	menu->setPosition(Point());
	addChild(menu);
	//放大出现
	setScale(0.1f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.5f,1.0f,1.0f);
	runAction(scaleTo);
	return true;
}

void PauseUI::backCallback(CCObject* pSender){
	//CCLOG("%s","PauseUI::backCallback();");
	removeFromParentAndCleanup(true);
	MyGame::getInstance()->setPause(false);
	MyGame::getInstance()->createTitle(false,true);
}

void PauseUI::continueCallback(CCObject* pSender){
//	CCLOG("%s","PauseUI::continueCallback();");
	removeFromParentAndCleanup(true);
	MyGame::getInstance()->setPause(false);

}

PauseUI::~PauseUI(){
	if(PropUI::getInstance()!=NULL){
		PropUI::getInstance()->setEnabled(true);
	}
	MyGame::getInstance()->setPause(false);
}