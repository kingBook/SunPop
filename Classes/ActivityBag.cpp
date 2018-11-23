#include "ActivityBag.h"
#include "Title.h"
#include "MyGame.h"
#include "LocalUtil.h"

bool ActivityBag::init(){
	if(!CCSprite::init())return false;
	CCLOG("%s","ActivityBag::init();");
	if(Title::getInstance()!=NULL){
		Title::getInstance()->setEnabled(false);
	}
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

	//“领取大礼包”
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath=haibaottfFile;
	ttfConfig.fontSize=isCn?50:40;
	ttfConfig.distanceFieldEnabled=true;
	std::string strTitle=LocalUtil::getInstance()->getKeyString("hddlb",true);
	Label*bgTitleLabel=Label::createWithTTF(ttfConfig,strTitle);
	bgTitleLabel->enableOutline(Color4B(0,100,0,255),2);
	bgTitleLabel->enableShadow(Color4B(0,30,0,255));
	bgTitleLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	bgTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
	bgTitleLabel->setPosition(0,246.8f);
	addChild(bgTitleLabel);

	//“购买”
	ttfConfig.fontFilePath=haibaottfFile;
	ttfConfig.fontSize=isCn?50:50;
	ttfConfig.distanceFieldEnabled=true;
	std::string str=LocalUtil::getInstance()->getKeyString("goumai",true);
	Label*buyLabel=Label::createWithTTF(ttfConfig,str);
	buyLabel->setTextColor(Color4B(255,255,220,255));
	buyLabel->enableShadow(Color4B(100,50,0,255),Size(4,-4));
	buyLabel->setPosition(Vec2(-83,117));
	addChild(buyLabel);

	CCSprite* zuanShi_a=CCSprite::create("zuanShi_a.png");
	zuanShi_a->setScale(0.6f);
	zuanShi_a->setPosition(ccp(46,125));
	addChild(zuanShi_a);

	Label*x30=Label::createWithTTF("x30",haibaottfFile,30);
	x30->setPosition(46,78);
	x30->enableOutline(Color4B(100,0,0,255),1);
	addChild(x30);

	std::string zengFile="zeng_en.png";
	if(isCn)zengFile="zeng.png";
	CCSprite* zeng = CCSprite::create(zengFile);
	zeng->setPosition(ccp(-114,-11.5f));
	zeng->setScale(1.5f);
	addChild(zeng);

	CCSprite* guang = CCSprite::create("guang.png");
	guang->setPosition(ccp(65,0));
	guang->setScale(0.9f);
	addChild(guang);

	CCSprite* zuanShi_b = CCSprite::create("zuanShi_a.png");
	zuanShi_b->setPosition(ccp(50,-15));
	addChild(zuanShi_b);

	Label*x20=Label::createWithTTF("x20",haibaottfFile,30);
	x20->setPosition(38,-78);
	x20->enableOutline(Color4B(100,0,0,255),1);
	addChild(x20);

	//领取按钮
	CCSprite* lingqu=CCSprite::create("lingqu.png");
	lingqu->setPositionY(-140);
	str=LocalUtil::getInstance()->getKeyString("lingqu",true);
	Label*label_lq=Label::createWithTTF(str,haibaottfFile,30);
	label_lq->setHorizontalAlignment(TextHAlignment::CENTER);
	label_lq->setPosition(lingqu->getContentSize().width*0.5f,lingqu->getContentSize().height*0.6f);
	label_lq->setTextColor(Color4B(0,50,0,255));
	lingqu->addChild(label_lq);
	addChild(lingqu);
	//领取按钮缩放动作
	CCScaleTo* scaleTo_a=CCScaleTo::create(0.5f,0.8f,0.8f);
	CCScaleTo* scaleTo_b=CCScaleTo::create(0.5f,1,1);
	CCSequence* scaleSeq = CCSequence::create(scaleTo_a,scaleTo_b,NULL);
	CCRepeatForever* repeatForever=CCRepeatForever::create(scaleSeq);
	lingqu->runAction(repeatForever);

	CCSprite* tick = CCSprite::create("tick.png");
	tick->setPosition(ccp(182,196));
	addChild(tick);

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png","close.png",this,menu_selector(ActivityBag::closeCallback));
	closeItem->setPosition(ccp(-170,201));

	CCMenuItemImage* rect_aItem = CCMenuItemImage::create("rect_a.png","rect_a.png",this,menu_selector(ActivityBag::okCallback));
	rect_aItem->setPosition(ccp(120,120));
	rect_aItem->setOpacity(0);
	CCMenuItemImage* rect_bItem = CCMenuItemImage::create("rect_b.png","rect_b.png",this,menu_selector(ActivityBag::okCallback));
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

void ActivityBag::closeCallback(CCObject* pSender){
	CCLOG("%s","ActivityBag::closeCallback();");
	removeFromParentAndCleanup(true);
}

void ActivityBag::okCallback(CCObject* pSender){
	CCLOG("%s","ActivityBag::okCallback();");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	MyGame::getInstance()->purchaseIAP("bag1");//"com.qywl.killBlock.bag1",50
#endif
	//MyGame::getInstance()->gamePay(12,"bigBag","",this,pay_cb(ActivityBag::payCallback),220);
}

void ActivityBag::payCallback(bool isFinish, int buyCount){
	CCLOG("ActivityBag::payCallback():%s, %d",isFinish?"ok":"no", buyCount);
	if(isFinish){
		MyGame::getInstance()->setDiamondCount(buyCount,true);
	}
}

ActivityBag::~ActivityBag(){
	if(Title::getInstance()!=NULL){
		Title::getInstance()->setEnabled(true);
	}
}