#include "MysteryPrizeBag.h"
#include "MyGame.h"
#include "LocalUtil.h"

bool MysteryPrizeBag::init(){
	if(!CCSprite::init())return false;
	bool isCn=LocalUtil::getInstance()->getLanguage()==LanguageType::CHINESE;
	MyGame::getInstance()->setIsCreateMysteryPrize(true);
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

	//“神秘大奖”--标题
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath="fonts/haibao.ttf";
	ttfConfig.fontSize=isCn?50:40;
	ttfConfig.distanceFieldEnabled=true;
	std::string strTitle=LocalUtil::getInstance()->getKeyString("smdj");
	Label*bgTitleLabel=Label::createWithTTF(ttfConfig,strTitle);
	bgTitleLabel->enableOutline(Color4B(0,100,0,255),2);
	bgTitleLabel->enableShadow(Color4B(0,30,0,255));
	bgTitleLabel->setHorizontalAlignment(TextHAlignment::CENTER);
	bgTitleLabel->setVerticalAlignment(TextVAlignment::CENTER);
	bgTitleLabel->setPosition(0,296.8f);
	addChild(bgTitleLabel);

	std::string str=LocalUtil::getInstance()->getKeyString("gxnhd");
	Label*gongxi=Label::createWithTTF(str,"fonts/haibao.ttf",35);
	gongxi->setTextColor(Color4B(150,50,100,255));
	gongxi->enableShadow();
	gongxi->setPositionY(200);
	addChild(gongxi);
	
	CCSprite* shenmidajian = CCSprite::create(isCn?"shenMiDaJiang_text.png":"shenMiDaJiang_text_en.png");
	shenmidajian->setPosition(ccp(0,135));
	addChild(shenmidajian);

	CCSprite* zuanShi_a=CCSprite::create("zuanShi_a.png");
	zuanShi_a->setScale(0.6f);
	zuanShi_a->setPosition(ccp(46,50));
	addChild(zuanShi_a);

	Label*x50=Label::createWithTTF("x50","fonts/haibao.ttf",30);
	x50->setPosition(46,3);
	x50->enableOutline(Color4B(100,0,0,255),1);
	addChild(x50);

	CCSprite* zeng = CCSprite::create(isCn?"zeng.png":"zeng_en.png");
	zeng->setPosition(ccp(-114,-90));
	zeng->setScale(1.5f);
	addChild(zeng);

	CCSprite* guang = CCSprite::create("guang.png");
	guang->setPosition(ccp(65,-75));
	guang->setScale(0.9f);
	addChild(guang);

	CCSprite* zuanShi_b = CCSprite::create("zuanShi_a.png");
	zuanShi_b->setPosition(ccp(50,-90));
	addChild(zuanShi_b);

	Label*x40=Label::createWithTTF("x40","fonts/haibao.ttf",30);
	x40->setPosition(38,-153);
	x40->enableOutline(Color4B(100,0,0,255),1);
	addChild(x40);

	//领取按钮
	CCSprite* lingqu=CCSprite::create("lingqu.png");
	lingqu->setPositionY(-210);
	str=LocalUtil::getInstance()->getKeyString("lingqu");
	Label*label_lq=Label::createWithTTF(str,"fonts/haibao.ttf",30);
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
	tick->setPosition(ccp(182,246));
	addChild(tick);

	CCMenuItemImage* closeItem = CCMenuItemImage::create("close.png","close.png",this,menu_selector(MysteryPrizeBag::closeCallback));
	closeItem->setPosition(ccp(-170,251));

	CCMenuItemImage* rect_aItem = CCMenuItemImage::create("rect_a.png","rect_a.png",this,menu_selector(MysteryPrizeBag::okCallback));
	rect_aItem->setPosition(ccp(120,170));
	rect_aItem->setScaleY(1.2f);
	rect_aItem->setOpacity(0);
	CCMenuItemImage* rect_bItem = CCMenuItemImage::create("rect_b.png","rect_b.png",this,menu_selector(MysteryPrizeBag::okCallback));
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

void MysteryPrizeBag::closeCallback(CCObject* pSender){
	//CCLOG("%s","MysteryPrizeBag::closeCallback();");
	removeFromParentAndCleanup(true);
}

void MysteryPrizeBag::okCallback(CCObject* pSender){
	CCLOG("%s","MysteryPrizeBag::okCallback();");
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
   // MyGame::getInstance()->reqProduct("com.qywl.killBlock.bag0",90);
#endif
}

void MysteryPrizeBag::payCallback(bool isFinish, int buyCount){
	CCLOG("MysteryPrizeBag::payCallback():%s, %d",isFinish?"ok":"no", buyCount);
	if(isFinish){
		MyGame::getInstance()->setDiamondCount(buyCount,true);
	}
}

MysteryPrizeBag::~MysteryPrizeBag(){
	MyGame::getInstance()->setIsCreateMysteryPrize(false);
}