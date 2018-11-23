#include "HelpUI.h"
#include "Title.h"
#include "LocalUtil.h"

bool HelpUI::init(){
	if(!CCSprite::init())return false;
	if(Title::getInstance()!=NULL){
		Title::getInstance()->setEnabled(false);
	}
	bool isCn=LocalUtil::getInstance()->getIsCn();
	bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//创建背景
	CCLayerColor* bgColor = CCLayerColor::create(ccc4(0,0,0,125));
	bgColor->setPosition(ccp(-visibleSize.width*0.5f,-visibleSize.height*0.5f));
	addChild(bgColor);
	
	CCSprite* bg = CCSprite::create("bagBg.png");
	bg->setScaleY(1.3f);
	addChild(bg);

	CCSprite* caiDai = CCSprite::create("caiDai.png");
	caiDai->setPositionY(261);
	addChild(caiDai);

	//帮助
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath=isTaiwanCn?"fonts/haibao_taiwancn.ttf":"fonts/haibao.ttf";
	ttfConfig.fontSize=isCn?50:40;
	ttfConfig.distanceFieldEnabled=true;
	std::string strTitle=LocalUtil::getInstance()->getKeyString("help",true);
	Label*bgTitleLabel=Label::createWithTTF(ttfConfig,strTitle);
	bgTitleLabel->enableOutline(Color4B(0,100,0,255),2);
	bgTitleLabel->enableShadow(Color4B(0,30,0,255));
	bgTitleLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	bgTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
	bgTitleLabel->setPosition(0,296.8f);
	addChild(bgTitleLabel);

	CCSprite* content = CCSprite::create(isCn?(isTaiwanCn?"helpContent_taiwancn.png":"helpContent.png"):"helpContent_en.png");
	content->setPosition(ccp(0,-25));
	addChild(content);

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png","close.png",this,menu_selector(HelpUI::closeCallback));
	closeItem->setPosition(ccp(-170,251));

	CCMenu* menu =CCMenu::create(closeItem,NULL);
	menu->setPosition(Point(0,0));
	addChild(menu);
	//放大出现
	setScale(0.1f);
	CCScaleTo* scaleTo = CCScaleTo::create(0.5f,1.0f,1.0f);
	runAction(scaleTo);
	return true;
}

void HelpUI::closeCallback(CCObject* pSender){
	//CCLOG("%s","MysteryPrizeBag::closeCallback();");
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
}

HelpUI::~HelpUI(){
	if(Title::getInstance()!=NULL){
		Title::getInstance()->setEnabled(true);
	}
}