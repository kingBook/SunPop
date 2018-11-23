#include "FailureUI.h"
#include "MyGame.h"
#include "GameEndAnim.h"
#include "LocalUtil.h"
#include "GameData.h"

bool FailureUI::init(){
	if(!CCSprite::init())return false;
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	std::string haibaottfFile=isTaiwanCn?"fonts/haibao_taiwancn.ttf":"fonts/haibao.ttf";
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

	//“再接再厉”
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath=haibaottfFile;
	ttfConfig.fontSize=isCn?50:40;
	ttfConfig.distanceFieldEnabled=true;
	std::string strTitle=LocalUtil::getInstance()->getKeyString("zaijiezaili",true);
	Label*bgTitleLabel=Label::createWithTTF(ttfConfig,strTitle);
	bgTitleLabel->enableOutline(Color4B(0,100,0,255),2);
	bgTitleLabel->enableShadow(Color4B(0,30,0,255));
	bgTitleLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	bgTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
	bgTitleLabel->setPosition(0,246.8f);
	addChild(bgTitleLabel);


	CCSprite* failureText = CCSprite::create(isCn?(isTaiwanCn?"failureText_taiwancn.png":"failureText.png"):"failureText_en.png");
	failureText->setScale(0.9f);
	failureText->setPositionY(20);
	addChild(failureText);

	//继续按钮
	CCSprite* continueGame=CCSprite::create("lingqu.png");
	continueGame->setPositionY(-140);
	std::string str=LocalUtil::getInstance()->getKeyString("continueBtn",true);
	Label*label_cg=Label::createWithTTF(str,haibaottfFile,30);
	label_cg->setHorizontalAlignment(TextHAlignment::CENTER);
	label_cg->setPosition(continueGame->getContentSize().width*0.5f,continueGame->getContentSize().height*0.6f);
	label_cg->setTextColor(Color4B(0,50,0,255));
	continueGame->addChild(label_cg);
	addChild(continueGame);

	//继续按钮缩放动作
	CCScaleTo* scaleTo_a=CCScaleTo::create(0.5f,0.8f,0.8f);
	CCScaleTo* scaleTo_b=CCScaleTo::create(0.5f,1,1);
	CCSequence* scaleSeq = CCSequence::create(scaleTo_a,scaleTo_b,NULL);
	CCRepeatForever* repeatForever=CCRepeatForever::create(scaleSeq);
	continueGame->runAction(repeatForever);

	CCSprite* tick = CCSprite::create("tick.png");
	tick->setPosition(ccp(182,196));
	addChild(tick);

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png","close.png",this,menu_selector(FailureUI::closeCallback));
	closeItem->setPosition(ccp(-170,201));

	CCMenuItemImage* rect_aItem = CCMenuItemImage::create("rect_a.png","rect_a.png",this,menu_selector(FailureUI::okCallback));
	rect_aItem->setPosition(ccp(120,120));
	rect_aItem->setOpacity(0);
	CCMenuItemImage* rect_bItem = CCMenuItemImage::create("rect_b.png","rect_b.png",this,menu_selector(FailureUI::okCallback));
	rect_bItem->setPositionY(-200);
	rect_bItem->setOpacity(0);

	CCMenu* menu =CCMenu::create(closeItem,rect_aItem,rect_bItem,NULL);
	menu->setPosition(Point());
	addChild(menu);
	//放大出现
	setScale(0.1f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.5f,1.0f,1.0f);
	runAction(scaleTo);
	return true;
}

void FailureUI::closeCallback(CCObject* pSender){
	CCLOG("%s","FailureUI::closeCallback();");
	removeFromParentAndCleanup(true);

	GameEndAnim* endAnim = GameEndAnim::create();
	GameLevel::getInstance()->addChild(endAnim);
}

void FailureUI::okCallback(CCObject* pSender){
	CCLOG("%s","FailureUI::okCallback();");
	removeFromParentAndCleanup(true);
#if GAME_IS_CREATE_SHOP
	MyGame::getInstance()->createWantContinueUI();
#else
	MyGame::getInstance()->continueGame();
#endif/*end GAME_IS_CREATE_SHOP*/

}