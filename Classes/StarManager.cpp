#include "StarManager.h"
#include "cocos2d.h"
#include "StarsBoard.h"
#include "RandomArr.h"
#include "MyGame.h"
#include "PropUI.h"
#include "ChangeColorBar.h"
#include "GameEndMessageUI.h"
#include "PropUI.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool StarManager::init(){
	if(!cocos2d::CCLayer::init())return false;
	_instance = this;
	for(int i=0;i<102;i++){_mvs[i]=0;}
	_offset = Point(0,48+30);
	for(int i=0; i<10; i++){
		Vector<Star*> vec(10);
		_stars.push_back(vec);
	}
	EventListenerTouchOneByOne* listener=EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	listener->onTouchBegan=CC_CALLBACK_2(StarManager::touchBeginHandler,this);
	listener->onTouchEnded=CC_CALLBACK_2(StarManager::touchEndedHandler,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	return true;
}

void StarManager::newStarsPosition(int cnts[]){
	//for(int i=0;i<5;i++){CCLOG("%d",cnts[i]);}
	//����
	_selectTotal=0;
	int i,j;
	for(i=0; i<10; i++){
		Vector<Star*> list=_stars.at(i);
		list.clear();
		for(j=0;j<10;j++)list.pushBack(Star::createEmpty());
		_stars[i]=list;//ȡ�����Ǹ������ı��Ҫ���¸�ֵ
	}
	//�½�
	StarsBoard* starsBoards=new StarsBoard[5];
	///for(i=0;i<5;i++){
	///	StarsBoard starsBoard = starsBoards[i];
	///}
	int id;
	for(i=0;i<5;i++){
		starsBoards[i].setAll(false);
		for(j=0;j<cnts[i];j++){
			id = RandomArr::getNextRandomElement();
			starsBoards[i].setTrue(id);
			pushStar(i,id,true);
		}
	}
	/*for(i=0;i<5;i++){
		starsBoards[i].logMy();
	}
	CCLOG("%d","--------------");*/
	_starsPosition=new StarsPosition(starsBoards);
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/starShow.mp3");
}

void StarManager::pop(int posId){
	_starsPosition->getBlackByPoint(posId,_mvs);
	//CCLOG("out %d",_mvs[101]);
	if(_mvs[101]>=2){//��ͬ��ɫ�ķ���>=2
		_selectTotal=_mvs[101];
		_starsPosition->doPop(_mvs);//�Ӿ����е���
		//��������
		int x,y;
		Star* star;
		vector<Star*> popStars;
		vector<Star*> moveStars;
		for(int i = 0; i < _selectTotal; i++) {
			x = _mvs[i] >> 4;
			y = 9 - (_mvs[i] & 0xf);
			Vector<Star*> list_x=_stars.at(x);
			star = list_x.at(y);
			popStars.push_back(star);//��ӵ�Ҫɾ�������б�������ɾ��
			list_x.erase(y);
			_stars[x]=list_x;
			for(int j = y; j < list_x.size(); j++){
				star=list_x.at(j);
				star->addMoveDown(_offset);
				star->setIsStopMove(true);//��true��ֹUpdate�ƶ����ȴ����ɾ�����
				moveStars.push_back(star);
			}
		}
		//��������
		checkMoveLeft(moveStars);
		///for(int i=0;i<(int)moveStars.size();i++){
		///	star =moveStars[i];
		///	CCLOG("2. moveStars added posId:%d, x_id:%d",star->getPosId(),(star->getPosId())>>4);
		///}
		int scoreMul = MyGame::getInstance()->getScoreMul();
        if(scoreMul>1)MyGame::getInstance()->setScoreMul(1);
        //һ����ɾ��
		deleteOneByOne(popStars,moveStars,true,scoreMul);
        //������ﵽ�սᣬ���㽱����ֵ��������ǰ
        checkGameOver();
	}
}

void StarManager::checkGameOver(){
	if(_starsPosition->nextGenerateMove()==0){
		destroyRemainStars();
		MyGame::getInstance()->setIsGameOver(true);
		PropUI::getInstance()->setEnabled(false);
		CCLOG("%s","gameOver~~!");
	}
}

void StarManager::destroyRemainStars(){
	vector<Star*> stars;
	int i,j;
	for(i=0;i<10;i++){
		Vector<Star*> list_i=_stars.at(i);
		for(j=0;j<list_i.size();j++){
			Star* star = list_i.at(j);
			stars.push_back(star);
		}
		list_i.clear();
		_stars[i]=list_i;
	}
	////��ʾ����������ʣ�µ������ı�
	MyGame::getInstance()->createGameEndMessageUI();
	log("stars.size:%d",stars.size());
	GameEndMessageUI::getInstance()->setRemainStars((int)stars.size());
	//����Ҫ�����ķ���
	int rewardScore = 0;
    if (stars.size() < 10) rewardScore = 2000 - stars.size() * stars.size() * 20;
	GameEndMessageUI::getInstance()->setRewardScore(rewardScore);
	//
	deleteOneByOne(stars,false,1);
}

void StarManager::deleteOneByOne(vector<Star*> popStars, bool isAddScore, int scoreMul){
	int total = popStars.size();
	float interval = 0.07f;
	float time = 0;
	//���ÿ��Ҫ�ӵķ�ֵ
	int* scoreArr = new int[total];
	int tempScore=0;
	int i;
	for(i=0;i<total;i++){
		tempScore=(i*10+5)*scoreMul;
		scoreArr[i]=tempScore;
	}
	/*  0 �����ϣ�6��7
        1 �ǳ�����8��9
        2 ˧������10~
    */
	int effectTypeId=-1;
	if(isAddScore){
		if(total>10)effectTypeId=2;
        else if(total>=8&&total<=9)effectTypeId=1;
        else if(total>=6&&total<=7)effectTypeId=0;
	}
	//
	int addScore;
	for(i=0; i<total; i++){
        time+=min(0.2f,interval*i);
        if(!isAddScore){
            if(i>=10){//����Ϸ����ʱ������>10��һ��������
                for (int j = i; j < total; j++){
					popStars[j]->delayPop(time,0,(bool)(j==total-1),-1,true);//���һ��ʱ��������ʾҪ�����ķ�ֵ
                }
                break; 
            }
        }
        addScore = isAddScore?scoreArr[i]:0;
        if(i==total-1) popStars[i]->delayPop(time,addScore,!isAddScore,effectTypeId);//���������һ���������������ƶ�,����������
        else popStars[i]->delayPop(time, addScore,false,-1);
    }
	//CCLOG("%s","deleteOneByOne a");
}

void StarManager::deleteOneByOne(vector<Star*> popStars, vector<Star*> moveStars, bool isAddScore, int scoreMul){
	//CCLOG("%s","deleteOneByOne b");
	int total = popStars.size();
	float interval = 0.07f;
	float time = 0;
	//���ÿ��Ҫ�ӵķ�ֵ
	int* scoreArr = new int[total];
	int tempScore=0;
	int i;
	for(i=0;i<total;i++){
		tempScore=(i*10+5)*scoreMul;
		scoreArr[i]=tempScore;
	}
	//  0 �����ϣ�6��7
    //  1 �ǳ�����8��9
    //  2 ˧������10~
    
	int effectTypeId=-1;
	if(isAddScore){
		if(total>10)effectTypeId=2;
        else if(total>=8&&total<=9)effectTypeId=1;
        else if(total>=6&&total<=7)effectTypeId=0;
	}
	//
	int addScore;
	for(i=0; i<total; i++){
        time+=MIN(0.1f,interval*i);
        if(!isAddScore){
            if(i>=10){//����Ϸ����ʱ������>10��һ��������
                for (int j = i; j < total; j++){
					popStars[j]->delayPop(time,0,(bool)(j==total-1),-1);//���һ��ʱ��������ʾҪ�����ķ�ֵ
                }
                break; 
            }
        }
        addScore = isAddScore?scoreArr[i]:0;
        if(i==total-1) popStars[i]->delayPop(moveStars,time,addScore,!isAddScore,effectTypeId);//���������һ���������������ƶ�,����������
        else popStars[i]->delayPop(time, addScore,false,-1);
    }
}

void StarManager::checkMoveLeft(vector<Star*> &moveStars){
	int* tmp = _starsPosition->doMoveToLeft();
	Star* star;
	for(int i=0;i<tmp[10];i++){
		if(tmp[i]!=i){
			//������Ӧ�ô洢�Ĵ洢��LIST
			_stars[i].pushBack(_stars[tmp[i]]);
			 //�����ƶ�
			for(int j=0;j<_stars[i].size();j++){
				star = _stars[i].at(j);
				star->addMoveLeft(tmp[i]-i,_offset);
				star->setIsStopMove(true);
				//CCLOG("push moveStars posId:%d, x_id:%d",star->getPosId(),(star->getPosId())>>4);
				moveStars.push_back(star);
			}
			_stars[tmp[i]].clear();
		}
	}
	///for(int i=0;i<(int)moveStars.size();i++){
		///star =moveStars[i];
		//CCLOG("1. moveStars added posId:%d, x_id:%d",star->getPosId(),(star->getPosId())>>4);
	///}
}

void StarManager::pushStar(int color,int idx,bool isTweenShow/*=false*/){
	int x_id = idx >> 4;//0-9
    int y_id = 9 - (idx & 0xf);//0-9
	CCPoint starPos = ccp(48.0f*x_id+_offset.x+24.0f,48.0f * y_id + _offset.y + 24.0f);
	Star* star=Star::create();
	star->initInstance(color,idx);
	star->setPosition(starPos);
	if(isTweenShow)star->tweenShow(_offset);
	this->addChild(star);
	Vector<Star*> list=_stars.at(x_id);
	list.replace(y_id,star);
	_stars[x_id]=list;
}

void StarManager::popOne(int posId){
	int scoreMul = MyGame::getInstance()->getScoreMul();
    if(scoreMul>1) MyGame::getInstance()->setScoreMul(1);
	_starsPosition->doPopOne(posId);
	vector<Star*> popStars;
	vector<Star*> moveStars;
	int x_id = posId>>4;
	int y_id = 9-(posId&0xf);
	Vector<Star*> list_x=_stars.at(x_id);
	Star* star=list_x.at(y_id);
	popStars.push_back(star);
	list_x.erase(y_id);
	_stars[x_id]=list_x;
	for(int j=y_id;j<list_x.size();j++){
		star=list_x.at(j);
		star->addMoveDown(_offset);
		star->setIsStopMove(true);
		moveStars.push_back(star);
	}
	checkMoveLeft(moveStars);
	deleteOneByOne(popStars, moveStars,true,scoreMul);

	checkGameOver();
}

void StarManager::upset(){
	vector<int> cors,posIds;
	Star* star;
	Vector<Star*> list_i;
	int i,j;
	for(i=0;i<10;i++){
		list_i=_stars.at(i);
		for(j=0;j<list_i.size();j++){
			star=list_i.at(j);
			cors.push_back(star->getColorId());
			posIds.push_back(star->getPosId());
			star->dispose();
		}
		list_i.clear();
		for(j=0;j<10;j++)list_i.pushBack(Star::createEmpty());
		_stars[i]=list_i;
	}
	star=NULL;
	//list_i=NULL;
	int* corArr = new int[cors.size()];
	int* posIdArr = new int[posIds.size()];
	for(i=0;i<(int)cors.size();i++)corArr[i]=cors.at(i);
	for(i=0;i<(int)posIds.size();i++)posIdArr[i]=posIds.at(i);
	/*for(i=0;i<cors.size();i++){
		CCLOG("a: %d",corArr[i]);
	}*/
	RandomArr::randomize(corArr,cors.size());
	/*for(i=0;i<cors.size();i++){
		CCLOG("b: %d",corArr[i]);
	}*/
	 //�ؽ�
	StarsBoard* starsBoards = new StarsBoard[5];
	for(i=0;i<5;i++)starsBoards[i].setAll(false);
	int cor, posId;
	for(i=0;i<(int)cors.size();i++){
		cor=corArr[i];
		posId=posIdArr[i];
		starsBoards[cor].setTrue(posId);
		pushStar(cor,posId);
	}
	_starsPosition->dispose();
	delete _starsPosition;
	_starsPosition=new StarsPosition(starsBoards);
	//�Ƴ�û�����ǵ�Ԫ��
	i=10;
	while(--i>=0){
		list_i=_stars.at(i);
		j=list_i.size();
		while(--j>=0){
			star=list_i.at(j);
			if(star->IsEmpty())list_i.erase(j);
		}
		_stars[i]=list_i;
	}
}

/**�ı�һ�����ǵ���ɫ*/
void StarManager::changeOneStarColor(int curCor, int targetCor, int curPosId){
	//////////1.�ı�starsBoards
	StarsBoard* starsBoard = _starsPosition->getStarsBoards();
	starsBoard[curCor].setFalse(curPosId);//��ǰ��ɫ�б����Ƴ�
	starsBoard[targetCor].setTrue(curPosId);//�ӵ��µ��б�
	//////////2.�ı�stars
    int x = curPosId >> 4;
    int y = 9 - (curPosId & 0xf);

	Vector<Star*> list_x=_stars.at(x);
	Star* star=list_x.at(y);
	star->changeColor(targetCor);
	PropUI::getInstance()->setEnabled(true);//�ָ�����������
	setTouchEnabled(true);//�ָ����ǿɵ�
	MyGame::getInstance()->setIsSelectColoring(false);
}

bool StarManager::touchBeginHandler(Touch* touch, Event* event){
	return true;
}

void StarManager::touchEndedHandler(Touch* touch, Event* event){
	if(MyGame::getInstance()->getPause())return;
	CCPoint pos = touch->getLocation();
	Star* star=getStarAtMousePos(pos);
	if(star!=NULL){
		if(MyGame::getInstance()->isPopOneing()){
			popOne(star->getPosId());
			MyGame::getInstance()->setIsPopOneing(false);
			PropUI::getInstance()->setEnabled(true);
        }else if(MyGame::getInstance()->isSelectColoring()){
            if(!MyGame::getInstance()->getIsHasColorBar()){
                createChangeColorBar(star);
                setTouchEnabled(false);
            }
		}else{
			pop(star->getPosId());
		}
	}
}

void StarManager::createChangeColorBar(Star* star){
	ChangeColorBar* changeColorBar = ChangeColorBar::create();
	changeColorBar->initInstance(star->getColorId(),star->getPosId());
	changeColorBar->setPosition(star->getPosition());
	addChild(changeColorBar);
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/coin.ogg");
}

Star* StarManager::getStarAtMousePos(const CCPoint &pos){
	int i,j,len;
	for(i=0;i<10;i++){
		Vector<Star*> list_i=_stars.at(i);
		len=list_i.size();
		for(j=0;j<len;j++){
			Star* star = list_i.at(j);
			CCRect r = star->boundingBox();
			if(r.containsPoint(pos)){
				/*list_i.erase(j);
				star->removeFromParent();
				break;*/
				return star;
			}
		}
	}
	return NULL;
}

StarManager* StarManager::_instance=NULL;
StarManager* StarManager::getInstance(){
	return _instance;
}

StarManager::~StarManager(){
	_instance=NULL;
}
