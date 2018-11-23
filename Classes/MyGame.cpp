#include "MyGame.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include "GameEndMessageUI.h"
#include "PropUI.h"
#include "Shop.h"
#include "PauseUI.h"
#include "ReceiveBag.h"
#include "MysteryPrizeBag.h"
#include "WantContinueUI.h"
#include "ActivityBag.h"
#include "FailureUI.h"
#include "NoviceBag.h"
#include "LocalUtil.h"
#include "GoodEffect.h"
#include "TrademarkAnimation.h"

/*#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../proj.android/jni/hellocpp/ttest.h"
#endif*/

using namespace CocosDenshion;

MyGame* MyGame::_instance=NULL;
MyGame* MyGame::getInstance(){
	if (!_instance)_instance=new MyGame();
	return _instance;
}

void MyGame::showScreenMessage(const std::string &str){
	/*Vec2 origin=Director::getInstance()->getVisibleOrigin();
	Size visibleSize=Director::getInstance()->getVisibleSize();
	Label* label=Label::createWithTTF(str,"",20);
	label->setPosition(origin.x+visibleSize.width*0.5f,
					   origin.y+visibleSize.height*0.5f);
	label->setHorizontalAlignment(TextHAlignment::CENTER);
	label->setVerticalAlignment(TextVAlignment::CENTER);*/

}

void MyGame::onKeyReleased(EventKeyboard::KeyCode keyCode,Event* event){
	if(_gameLevel!=NULL)return;
	switch(keyCode){
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			if(_isCreateMysteryPrize) exitGame();
			else createMysteryPrizeBag();
			break;
		default:
			break;
	}
}

void MyGame::exitGame(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

bool MyGame::init(){
	if(!Layer::init())return false;
	_instance=this;

	TrademarkAnimation* td=TrademarkAnimation::create();
	addChild(td);
	td->setCompleteCallback(CC_CALLBACK_0(MyGame::initGame,this));
    
    Size size=Director::getInstance()->getOpenGLView()->getFrameSize();
    log("w:%f,h:%f",size.width,size.height);
    bool isIpad=Application::getInstance()->getTargetPlatform()==Application::Platform::OS_IPAD;
    log("============================isIpad:%s",Value(isIpad).asString().c_str());
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    if(isIpad){
        _bannerKey="ipad";
    }else{
        if(size.width<1242)_bannerKey="iphone5s";
        else _bannerKey="iphone6s";
    }
    _fullScreenAdsKey="fullScreenAds";
    //>20%显示别人的广告
    /*if(cocos2d::random(0,100)>20){
     _bannerKey+="b";
     }*/
    sdkbox::PluginAdMob::cache(_bannerKey.c_str());
    sdkbox::PluginAdMob::cache(_fullScreenAdsKey.c_str());
    //---------------IAP------------------
    sdkbox::IAP::setListener(this);
#endif/*CC_PLATFORM_IOS*/
	return true;
}

void MyGame::initGame(){
	_mute=false;
	_diamondCount=0;
	_isGameOver=true;
	_pause=false;
	_scoreMul = 1;
	_gameLevel=NULL;
    //
    
    //
	_isReceiveNoviceBag=CCUserDefault::sharedUserDefault()->getBoolForKey("isReceiveNoviceBag",false);
	//
	setDiamondCount(-1);
	//开始赠送20颗钻石
	if(!CCUserDefault::sharedUserDefault()->getBoolForKey("isgived",false)){
		setDiamondCount(20);
		CCUserDefault::sharedUserDefault()->setBoolForKey("isgived",true);
	}
	//
	createTitle();
#if GAME_IS_CREATE_SHOP
	if(!_isReceiveNoviceBag){
		//创建新手大礼包
		scheduleOnce(schedule_selector(MyGame::startDelayComplete),0.5f);
	}
#endif/*end GAME_IS_CREATE_SHOP*/
	EventListenerKeyboard* listener=EventListenerKeyboard::create();
	listener->onKeyReleased=CC_CALLBACK_2(MyGame::onKeyReleased,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);

#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    std::string iosLanguage=LocalUtil::getInstance()->getIosLanguage();
    bool isTaiwanCn=LocalUtil::getInstance()->getIsTaiwanCn();
    print("iosLanguage:"+iosLanguage);
    print("isTaiWanCn:"+Value(isTaiwanCn).asString());
    showFullScreenAds();
#endif
}

void MyGame::startDelayComplete(float t){
	createNoviceBag();
}

void MyGame::setDiamondCount(int value/*=-1*/,bool isAdd/*=false*/){
	const char* key = "diamondCount";
	if(value==-1){
		_diamondCount=CCUserDefault::sharedUserDefault()->getIntegerForKey(key,0);
	}else{
		if(isAdd) _diamondCount+=value;
		else _diamondCount = value;
		CCUserDefault::sharedUserDefault()->setIntegerForKey(key,_diamondCount);
	}

	//更新钻石颗数
	if(Shop::getInstance()!=NULL){
		Shop::getInstance()->updateDiamondText();
	}
	if(PropUI::getInstance()!=NULL){
		PropUI::getInstance()->updateDiamondText();
	}
}


void MyGame::clearSaveData(){
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level",1);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("score",0);
}

void MyGame::newGame(){
	clearSaveData();
	createGameLevel();
}

void MyGame::continueGame(){
	createGameLevel();
}

void MyGame::createGameLevel(){
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	_isPopOneing=false;
	_isSelectColoring=false;
	_isGameOver=false;
	_pause=false;
	_isMissionFinish=false;

	_level = CCUserDefault::sharedUserDefault()->getIntegerForKey("level",1);
	_score = CCUserDefault::sharedUserDefault()->getIntegerForKey("score",0);
	_maxRecord = CCUserDefault::sharedUserDefault()->getIntegerForKey("maxRecord",0);
	_targetScore = GameData::getTargetScore(_level);
	_gameLevel = GameLevel::create();
	this->addChild(_gameLevel);

	if(_score>=_targetScore)createMissionFinishEff();
    showBannerAd(1);
}

void MyGame::hideBannerAds(){
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    unschedule(schedule_selector(MyGame::showBannerAd));
    sdkbox::PluginAdMob::hide(_bannerKey.c_str());
#endif
}

void MyGame::showBannerAd(float t){
    //显示广告
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    bool isVal=sdkbox::PluginAdMob::isAvailable(_bannerKey.c_str());
    log("isVal:%s",Value(isVal).asString().c_str());
    print("isVal:"+Value(isVal).asString());
    sdkbox::PluginAdMob::show(_bannerKey.c_str());
    //if(isVal)sdkbox::PluginAdMob::show(_bannerKey.c_str());
    //else scheduleOnce(schedule_selector(MyGame::showBannerAd), 1);
#endif
}

void MyGame::addAdsCount(){
    _adsCount++;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    if((_adsCount&1)==0){
        showFullScreenAds();
    }
#endif
}

/**显示全屏广告*/
void MyGame::showFullScreenAds(){
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	 bool isVal=sdkbox::PluginAdMob::isAvailable(_fullScreenAdsKey.c_str());
    log("FullScreenAds isAvailable:%s",Value(isVal).asString().c_str());
	 /*if(isVal)*/sdkbox::PluginAdMob::show(_fullScreenAdsKey.c_str());
#endif
}

void MyGame::hideFullScreenAds(){
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	 sdkbox::PluginAdMob::hide(_fullScreenAdsKey.c_str());
#endif
}

void MyGame::createMissionFinishEff(){
	if(_isMissionFinish)return;
	_isMissionFinish=true;
	Size size=Director::getInstance()->getVisibleSize();
	bool isCn=LocalUtil::getInstance()->getIsCn();
	GoodEffect*eff=GoodEffect::create();
	eff->initInstance(isCn?"levelComplete.png":"levelComplete_en.png");
	eff->setPosition(size.width*0.5f,size.height*0.5f);
	this->addChild(eff);
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/targetScore.ogg");
}

void MyGame::checkGameVictoryFailure(){
	_pause=false;
	if(_score>=_targetScore)victory();
	else failure();
}

void MyGame::victory(){
	//保存最高记录
    if(_score>_maxRecord){
		CCUserDefault::sharedUserDefault()->setIntegerForKey("maxRecord",_score);
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		if(_isAuthenticated){
			submitScore(_score);
		}
#endif
	}
    //保存得分
	CCUserDefault::sharedUserDefault()->setIntegerForKey("score",_score);
    //保存关卡
	CCUserDefault::sharedUserDefault()->setIntegerForKey("level",_level+1);
    //////////////////////////////////////////////////////////////////////////
	 addAdsCount();
#if GAME_IS_CREATE_SHOP
    //创建领取大礼包
    createReceiveBag(true);
#else
	 continueGame();
#endif/*end GAME_IS_CREATE_SHOP*/
}



void MyGame::failure(){
    //创建失败界面
	createFailureUI();
    addAdsCount();
}

void MyGame::addScore(int value){
	_score+=value;
}

void MyGame::setPause(bool value, bool isStopOpengl/*=false*/,bool isStopSound/*=false*/){
	_pause=value;
	if(_pause){
		if(isStopOpengl)CCDirector::sharedDirector()->stopAnimation();
		if(isStopSound){
			SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->stopAllEffects();
		}
	}else{
		if(isStopOpengl)CCDirector::sharedDirector()->startAnimation();
		if(isStopSound){
			SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
			SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		}
	}
}
bool MyGame::getPause(){
	return _pause;
}

void MyGame::setIsCreateMysteryPrize(bool value){
	_isCreateMysteryPrize=value;
}

void MyGame::setIsReceiveNoviceBaged(){
	_isReceiveNoviceBag=true;
	CCUserDefault::sharedUserDefault()->setBoolForKey("isReceiveNoviceBag",_isReceiveNoviceBag);
}
void MyGame::setMute(bool value){
	_mute = value;
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(_mute?0:0.5f);
}
void MyGame::setIsGameOver(bool value){_isGameOver=value;}
void MyGame::setIsPopOneing(bool value){_isPopOneing = value;}
void MyGame::setIsSelectColoring(bool value){_isSelectColoring=value;}
void MyGame::setScoreMul(int value){_scoreMul = value;}
//get
bool MyGame::getIsReceiveNoviceBag(){return _isReceiveNoviceBag;}
bool MyGame::getIsGameOver(){return _isGameOver;}
bool MyGame::isSelectColoring(){return _isSelectColoring;}
bool MyGame::isPopOneing(){return _isPopOneing;}
int MyGame::getLevel(){return _level;}
int MyGame::getTargetScore(){return _targetScore;}
int MyGame::getScore(){return _score;}
int MyGame::getMaxRecord(){return _maxRecord;}
int MyGame::getDiamondCount(){return _diamondCount;}
int MyGame::getScoreMul(){return _scoreMul;}
bool MyGame::getMute(){ return _mute;}

/**创建神秘大奖*/
void MyGame::createMysteryPrizeBag(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	MysteryPrizeBag* mysteryPrizeBag = MysteryPrizeBag::create();
	mysteryPrizeBag->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(mysteryPrizeBag);
}

void MyGame::createPauseUI(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	PauseUI* pauseUI = PauseUI::create();
	pauseUI->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(pauseUI);
}

void MyGame::createTitle(bool isClearSaveData, bool isDestroyLevel){
	if(isClearSaveData) clearSaveData();
	if(isDestroyLevel){
		if(_gameLevel!=NULL){
			_gameLevel->removeAllChildrenWithCleanup(true);
			_gameLevel->removeFromParentAndCleanup(true);
			_gameLevel=NULL;
		}
        hideBannerAds();
	}
	_title = Title::create();
	this->addChild(_title);
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/bg.ogg",true);
}

void MyGame::createShop(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	Shop* shop = Shop::create();
	shop->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(shop);
}

void MyGame::createGameEndMessageUI(){
	GameEndMessageUI* gameEndMessageUI = GameEndMessageUI::create();
	addChild(gameEndMessageUI);
}

/**创建领取大礼包*/
void MyGame::createReceiveBag(bool isContinueGame){
	int tag = 10;
	if(getChildByTag(tag)!=NULL)return;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	ReceiveBag* receiveBag = ReceiveBag::create();
	receiveBag->setIsContinueGame(isContinueGame);
	receiveBag->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	receiveBag->setTag(tag);
	addChild(receiveBag);
}

void MyGame::createWantContinueUI(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	WantContinueUI* wantContinueUI = WantContinueUI::create();
	wantContinueUI->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(wantContinueUI);
}

/**创建活动大礼包*/
void MyGame::createActivityBag(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	ActivityBag* activityBag = ActivityBag::create();
	activityBag->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(activityBag);
}

void MyGame::createFailureUI(){
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	FailureUI* failureUI = FailureUI::create();
	failureUI->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(failureUI);
}

/**创建新手大礼包*/
void MyGame::createNoviceBag(){
#if GAME_IS_CREATE_SHOP
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	NoviceBag* noviceBag = NoviceBag::create();
	noviceBag->setPosition(ccp(visibleSize.width*0.5f,visibleSize.height*0.5f));
	addChild(noviceBag);
#endif/*end GAME_IS_CREATE_SHOP*/
}

void MyGame::createGameOverAnim(){
}

const char* MyGame::getIntCString(const int n, const char* fntFile) const{
	CCString* ccStr_n=NULL;
	if(n>=10000){
		float nn = n*0.0001;
		
		std::string ccStr_wan=LocalUtil::getInstance()->getKeyString("wan");
		ccStr_n=CCString::createWithFormat("%.2f",nn);
		string str = ccStr_n->getCString();
		str+=ccStr_wan;
		ccStr_n = CCString::create(str);
	}else{
		ccStr_n = CCString::createWithFormat("%d",n);
	}
	return ccStr_n->getCString();
}

/*void MyGame::gamePay(const int money, const char* product, const char* extData,CCObject*payCB_this,PayCB cb,int buyCount){
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	_payCB_this = payCB_this;
	_payCB=cb;
	_buyCount = buyCount;
	ccPay(money*100,product,extData);
#endif
	
}*/

void MyGame::payCallback(const char* result){
	//(_payCB_this->*_payCB)(result=="yes",_buyCount);
}
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)

void MyGame::refreshIAP(const std::string &purchaseName/*=""*/){
	if(_isRefreshIAP)return;
	_refreshFinishPurchaseName=purchaseName;
	sdkbox::IAP::refresh();
	//onProductRequestSuccess 成功获取会收到这个事件.
	//onProductRequestFailure 获取失败的话,会收到这个事件.
	print("sdkbox::IAP::refresh();");
}

void MyGame::purchaseIAP(const std::string &name){
	if(_isRefreshIAP){
		sdkbox::IAP::purchase(name);
		//onSuccess 购买成功会收到这个事件.
		//onFailure 购买失败事件.
		//onCanceled 用户取消了购买.

		std::string str="===purchaseIAP();====";
		str+=name;
		print(str);
	}else{
		refreshIAP(name);
	}
}

void MyGame::onInitialized(bool ok){
    
}

void MyGame::onSuccess(sdkbox::Product const& p){
	int countDiamonds=0;
	if (p.name=="shopBtn0")countDiamonds=38;
	else if(p.name=="shopBtn1")countDiamonds=90;
	else if(p.name=="shopBtn2")countDiamonds=136;
	else if(p.name=="bag1")countDiamonds=50;
	setDiamondCount(countDiamonds,true);
	std::string str="===onSuccess();===:";
	str+=p.name;
	str+=":";
	str+=Value(countDiamonds).asString();
	print(str);
}
void MyGame::onFailure(sdkbox::Product const& p, const std::string &msg){
	print("===onFailure();===");
}
void MyGame::onCanceled(sdkbox::Product const& p){
	print("===onCanceled();===");
}
void MyGame::onRestored(sdkbox::Product const& p){
	print("===onRestored();===");
}
void MyGame::onProductRequestSuccess(std::vector<sdkbox::Product> const &products){
	_isRefreshIAP=true;
	if(_refreshFinishPurchaseName!="") purchaseIAP(_refreshFinishPurchaseName);
	print("onProductRequestSuccess()");
}
void MyGame::onProductRequestFailure(const std::string &msg){
	print("onProductRequestFailure()");
}
void MyGame::onRestoreComplete(bool ok, const std::string &msg){
    
}

/**用户登录*/
void MyGame::authenticateLocalUser(bool isSubmit/*=false*/,bool isShowLeaderboard/*=false*/){
	_authenticatedIsSubmit=isSubmit;
	_authenticatedIsShow=isShowLeaderboard;
    Leaderboard::getInstance()->authenticateLocalUser(LEADERBOARD_CALLBACK_1(MyGame::authenticateLocalUserCallback,this));
}
void MyGame::authenticateLocalUserCallback(bool succeed){
	std::string str="=========authenticateLocalUserCallback== ";
	str+="\n  isSucceed:"; str+=Value(succeed).asString();
	print(str);
	if(succeed){
		_isAuthenticated=true;
		if(_authenticatedIsSubmit){
			_authenticatedIsSubmit=false;
            int maxRecord = CCUserDefault::sharedUserDefault()->getIntegerForKey("maxRecord",0);
			submitScore(maxRecord);
		}
		if(_authenticatedIsShow){
			_authenticatedIsShow=false;
			showLeaderboard();
		}
	}
}

/**显示排行榜*/
void MyGame::showLeaderboard(){
	if(_isAuthenticated){
		Leaderboard::getInstance()->showLeaderboard();
	}else{
		authenticateLocalUser(false,true);
	}
}

/**提交分数*/
void MyGame::submitScore(int score,bool isShowLeaderboard/*=false*/){
	if(_isAuthenticated){
		Leaderboard::getInstance()->submitScore(score,LEADERBOARD_CALLBACK_1(MyGame::submitScoreCallback,this));
		_submitIsShow=isShowLeaderboard;
	}else{
		authenticateLocalUser(true);
	}
}

void MyGame::submitScoreCallback(bool succeed){
	std::string str="=========submitScoreCallback== ";
	str+="\n  isSucceed:"; str+=Value(succeed).asString();
	print(str);
	if(succeed){
		if(_submitIsShow){
			_submitIsShow=false;
			showLeaderboard();
		}
	}
	
}

void MyGame::print(const std::string& text){
    if(GameData::isDebug){
		if(_label==NULL){
            Size visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
			_label = Label::createWithSystemFont(text+"\n","Arial.ttf",15);
			_label->setPosition(Vec2(10, origin.y+visibleSize.height-_label->getContentSize().height));
			_label->setAlignment(TextHAlignment::LEFT);
			_label->setAnchorPoint(Point(0,1));
			this->addChild(_label,10);
		}else{
			_label->setString(_label->getString()+text+"\n");
		}
	}
}
#endif
void MyGame::resumeAnimation(float t){
	
}

MyGame::~MyGame(){
	_instance=NULL;
	//_payCB=NULL;
	//_payCB_this=NULL;
	_title=NULL;
	_gameLevel=NULL;
}

